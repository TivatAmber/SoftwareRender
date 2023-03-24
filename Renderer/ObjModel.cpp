#include "ObjModel.h"

/*
void ObjModel::loadObjFile(const std::string& path) {
	std::ifstream in;
	in.open(path, std::ifstream::in);
	if (in.fail()) std::cerr << "No such File";
	std::string line;
	std::cerr << path << "\n";
	std::vector<Vector3D> nowVertices;
	std::vector<Vector3D> normals;
	std::vector<Vector2D> texcoords;
	while (!in.eof()) {
		char trash;
		getline(in, line);
		std::istringstream iss(line.c_str());
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			Vector3D vertex;
			for (int i = 0; i < 3; i++) {
				iss >> vertex[i];
			} nowVertices.push_back(vertex);
		}
		else if (!line.compare(0, 3, "vn ")) {
			iss >> trash >> trash;
			Vector3D normal;
			for (int i = 0; i < 3; i++) iss >> normal[i];
			normals.push_back(normal);
		}
		else if (!line.compare(0, 3, "vt ")) {
			iss >> trash >> trash;
			Vector2D texcoord;
			for (int i = 0; i < 2; i++) iss >> texcoord[i];
			texcoords.push_back(texcoord);
		}
		else if (!line.compare(0, 2, "f ")) {
			iss >> trash;
			int idx[3];
			while (iss >> idx[0] >> trash >> idx[1] >> trash >> idx[2]) {
				Vertex data;
				data.position = nowVertices[idx[0] - 1];
				data.texcoord = texcoords[idx[1] - 1];
				data.normal = normals[idx[2] - 1];
				data.color = Vector4D(0.0f, 0.0f, 0.0f, 1.0f);
				indices.push_back(vertices.size());
				vertices.push_back(data);
			}
		}
	} in.close();
}
*/

void ObjModel::loadObjFile(const std::string& path) {
	std::ifstream in;
	in.open(path, std::ifstream::in);
	if (in.fail()) std::cerr << "No such File";
	std::string line;
	std::cerr << path << "\n";
	std::vector<Vector3D> nowVertices;
	std::vector<Vector3D> normals;
	std::vector<Vector2D> texcoords;
	while (!in.eof()) {
		char trash;
		getline(in, line);
		std::istringstream iss(line.c_str());
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			Vector3D vertex;
			for (int i = 0; i < 3; i++) {
				iss >> vertex[i];
			} nowVertices.push_back(vertex);
		}
		else if (!line.compare(0, 3, "vn ")) {
			iss >> trash >> trash;
			Vector3D normal;
			for (int i = 0; i < 3; i++) iss >> normal[i];
			normals.push_back(normal);
		}
		else if (!line.compare(0, 3, "vt ")) {
			iss >> trash >> trash;
			Vector2D texcoord;
			for (int i = 0; i < 2; i++) iss >> texcoord[i];
			texcoords.push_back(texcoord);
		}
		else if (!line.compare(0, 2, "f ")) {
			iss >> trash;
			int idx[3], i = 0;
			Vertex data[4];
			while (iss >> idx[0] >> trash >> idx[1] >> trash >> idx[2]) {
				data[i].position = nowVertices[idx[0] - 1];
				data[i].texcoord = texcoords[idx[1] - 1];
				data[i].normal = normals[idx[2] - 1];
				data[i].color = Vector4D(0.0f, 0.0f, 0.0f, 1.0f);
				vertices.push_back(data[i]);
				i++;
			}
			if (i == 3) {
				indices.push_back(vertices.size() - 2);
				indices.push_back(vertices.size() - 1);
				indices.push_back(vertices.size() - 0);
			}
			else if (i == 4) {
				indices.push_back(vertices.size() - 3);
				indices.push_back(vertices.size() - 2);
				indices.push_back(vertices.size() - 1);

				indices.push_back(vertices.size() - 3);
				indices.push_back(vertices.size() - 1);
				indices.push_back(vertices.size() - 0);
			}
		}
	} in.close();
}
