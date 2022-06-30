#include "global.h"
#include "stb_image.h"
TextureData::TextureData(string Path,bool isFilp)
{
	stbi_set_flip_vertically_on_load(isFilp);
	data = stbi_load(Path.c_str(), &w, &h, &c, 4);
	if (!data)
		cout << "Load" + Path + "falure" << endl;
}

TextureData::~TextureData()
{
	if(data)
		stbi_image_free(data);
}
