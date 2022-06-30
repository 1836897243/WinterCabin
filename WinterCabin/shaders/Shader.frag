#version 430 core
//光照
uniform sampler2D shadowMap;
uniform vec3 LightPos;
uniform float IntensityAmbient;
uniform float Intensity;
uniform vec3 LightKa;
uniform vec3 LightKd;
uniform vec3 LightKs;
uniform vec3 CameroPos;
//材质,以下宏定义应与cpp文件宏定义相同
#define MapKa 1
#define MapKd 2
#define MapKs 4
#define MapBump 8
#define MapNs 16
uniform int MtlKind;
uniform sampler2D map_Ka;
uniform sampler2D map_Kd;
uniform sampler2D map_Ks;
uniform sampler2D map_Ns;
uniform sampler2D map_Bump;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;
//顶点相关数据
in vec4 FragPosition;
in vec4 FragNormal;
in vec2 FragUV;
in vec4 lightSpacePos;
in mat3 TBN;
out vec4 fragColor;
float getAvgDepth(vec2 depthCoord,float bias,float depth)
{
  
  if(length(depthCoord-vec2(0.5))>0.5)//把阴影贴图限制才以a=texelsize.x,b=texelsize.y的椭圆内，可以当作聚光灯
    return 0;
  float shadowValue=0;
  float ans=0;
  vec2 texelSize = textureSize(shadowMap, 0);
  for(int i=-1;i<2;i++)
    {
      for(int j=-1;j<2;j++)
      {
        shadowValue=texture(shadowMap,depthCoord+vec2(i,j)/texelSize).r;
        ans+=1-step(shadowValue,depth-bias);
      }
    }
    ans/=9;
    return ans;
}
//使阴影柔和
float soft(vec3 depthInfo,float bias)
{
  vec2 texelSize = textureSize(shadowMap, 0);
  vec2 st=depthInfo.xy*texelSize;
  vec2 f=fract(st);
  f=fract(f+vec2(0.5));
  st=st.xy+fract(st.xy);
  float tl=getAvgDepth((st+vec2(-1,0))/texelSize,bias,depthInfo.z).r;
  float tr=getAvgDepth(st/texelSize,bias,depthInfo.z).r;
  float bl=getAvgDepth((st+vec2(-1,-1))/texelSize,bias,depthInfo.z).r;
  float br=getAvgDepth((st+vec2(0,-1))/texelSize,bias,depthInfo.z).r;
  vec2 u = f*f*(3.0-2.0*f);
  return mix(bl, br, u.x) +
            (tl - bl)* u.y * (1.0 - u.x) +
            (tr - br) * u.x * u.y; 

}
vec4 BlinnPhone(in vec3 lightSource,in float Ia,in float I,in vec3 eyePos,in vec3 Pos,in vec3 norm)
{
    vec3 l=normalize(LightPos-FragPosition.xyz/FragPosition.w);
    vec3 v=normalize(eyePos-FragPosition.xyz/FragPosition.w);
    vec3 h=normalize(v+l);
    float r2=dot(l,l);
    vec4 La=mix(vec4(Ka,1),texture(map_Ka,FragUV),MtlKind&MapKa)*vec4(LightKa,1)*Ia;
    //如果有MapKd却没有Map_Kd,效果与3D查看器结果不一样，并且很差，也许是光照模型不同，此处就把Map_Kd的颜色作为Map_Ka的颜色
    if(!bool(MtlKind&MapKa)&&bool(MtlKind&MapKd))
      La=texture(map_Kd,FragUV)*vec4(LightKa,1)*Ia;
    vec3 depthInfo=lightSpacePos.xyz/lightSpacePos.w;
    depthInfo=depthInfo*0.5+0.5;
    float bias = max(0.0005 * (1.0 - dot(norm.xyz, l)), 0.00005);
    float ShadowValue=0;//1-step(shadowValue,depthInfo.z-bias);
    ShadowValue=soft(depthInfo,bias);
    vec4 Ld=mix(vec4(Kd,1),texture(map_Kd,FragUV),clamp(MtlKind&MapKd,0,1))*vec4(LightKd,1)*(I/r2)*max(dot(l,norm),0)*ShadowValue;
    float ns=mix(Ns,texture(map_Ns,FragUV).r*Ns,clamp(MtlKind&MapNs,0,1));
    vec4 Ls=mix(vec4(Ks,1),texture(map_Ks,FragUV),clamp(MtlKind&MapKs,0,1))*vec4(LightKs,1)*(I/r2)*pow(max(dot(h,norm),0),Ns)*ShadowValue;
    return La+Ld+Ls;
}
void main()
{
  vec3 normal;
  if(int(MtlKind&MapBump)!=0)
  {
    normal=texture(map_Bump,FragUV).rgb;
    //normalize()中的对象不能为零向量，不然会发生很多意外的错误
    normal = normalize(normal * 2.0 - 1.0);   
    normal = normalize(TBN * normal);
  }
  else
    normal=FragNormal.xyz;
  fragColor =BlinnPhone(LightPos,IntensityAmbient,Intensity,CameroPos,FragPosition.xyz/FragPosition.w,normal);
}
