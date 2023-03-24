#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include "Mesh.h"

class ObjModel : public Mesh
{
public :
	ObjModel(const std::string& path) { loadObjFile(path); }
	~ObjModel() = default;
private :
	void loadObjFile(const std::string& path);
};

