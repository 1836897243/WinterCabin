#include "Material.h"

Material::Material(vec3 ka, vec3 kd, vec3 ks, float ns, string Name)
	:Ka(ka), Kd(kd), Ks(ks), Ns(ns), MtlName(Name) {
	MtlKind = 0;
}

Material::Material(const Material& mtl)
{
	Ka = mtl.Ka;
	Kd = mtl.Kd;
	Ks = mtl.Ks;
	MapKaPath = mtl.MapKaPath;
	MapKdPath = mtl.MapKdPath;
	MapKsPath = mtl.MapKsPath;
	MapBumpPath = mtl.MapBumpPath;
	Ns = mtl.Ns;
	MtlKind = mtl.MtlKind;
	MtlName = mtl.MtlName;
}

vector<Material> Material::loadMate(string Path, string Name)
{
	ifstream infile;
	infile.open(Path + "\\" + Name, ios::in);
	vector<Material>res;
	if (!infile.is_open())
	{
		cout << Path << ":´ò¿ª²ÄÖÊÊ§°Ü" << endl;
		return res;
	}
	function<string(string)> EraseHeadSpace = [](string tmp)
	{
		reverse(tmp.begin(), tmp.end());
		while (tmp.back() == ' '|| tmp.back() =='\t')
			tmp.pop_back();
		reverse(tmp.begin(), tmp.end());
		return tmp;
	};
	while (!infile.eof())
	{
		string tmp;
		infile >> tmp;
		if (tmp == "#")
		{
			getline(infile, tmp);
		}
		else if (tmp == "newmtl")
		{
			Material Mtl;
			res.push_back(Mtl);
			infile >> tmp;
			res.back() = Material();
			res.back().MtlName = tmp;
		}
		else if (tmp == "Ka")
		{
			float x, y, z;
			infile >> x;
			infile >> y;
			infile >> z;
			res.back().Ka = vec3(x, y, z);
		}
		else if (tmp == "Kd")
		{
			float x, y, z;
			infile >> x;
			infile >> y;
			infile >> z;
			res.back().Kd = vec3(x, y, z);
		}
		else if (tmp == "Ks")
		{
			float x, y, z;
			infile >> x;
			infile >> y;
			infile >> z;
			res.back().Ks = vec3(x, y, z);
		}
		else if (tmp == "map_Ka")
		{
			getline(infile, tmp);
			tmp = EraseHeadSpace(tmp);
			res.back().setMapKa(Path + "\\" + tmp);
		}
		else if (tmp == "map_Kd")
		{
			getline(infile, tmp);
			tmp = EraseHeadSpace(tmp);
			res.back().setMapKd(Path + "\\" + tmp);
		}
		else if (tmp == "map_Ks")
		{
			getline(infile, tmp);
			tmp = EraseHeadSpace(tmp);
			res.back().setMapKs(Path + "\\" + tmp);
		}
		else if (tmp == "map_Bump")
		{
			getline(infile, tmp);
			tmp = EraseHeadSpace(tmp);
			res.back().setMapBump(Path + "\\" + tmp);
		}
		else if (tmp == "map_Ns")
		{
			getline(infile, tmp);
			tmp = EraseHeadSpace(tmp);
			res.back().setMapNs(Path + "\\" + tmp);
		}
		else if (tmp == "Ns")
		{
			float Ns;
			infile >> Ns;
			res.back().Ns = Ns;
		}
		else
			getline(infile, tmp);
	}
	infile.close();
	return res;
}

void Material::setMapKa(string Path)
{
	MapKaPath = Path;
	MtlKind = MtlKind | MapKa;
}

void Material::setMapKd(string Path)
{
	MapKdPath = Path;
	MtlKind = MtlKind | MapKd;
}

void Material::setMapKs(string Path)
{
	MapKsPath = Path;
	MtlKind = MtlKind | MapKs;
}

string Material::getMapKa()
{
	return MapKaPath;
}

string Material::getMapKd()
{
	return MapKdPath;
}

string Material::getMapKs()
{
	return MapKsPath;
}

void Material::setMapBump(string Path)
{
	MapBumpPath = Path;
	MtlKind = MtlKind | MapBump;
}

string Material::getMapBump()
{
	return MapBumpPath;
}

void Material::setMapNs(string Path)
{
	MapNsPath = Path;
	MtlKind = MtlKind | MapNs;
}

string Material::getMapNs()
{
	return MapNsPath;
}

int Material::getMtlKind()
{
	return MtlKind;
}
