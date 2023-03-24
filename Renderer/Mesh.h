#pragma once

#include <vector>
#include "Vertex.h"

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh() = default;
    ~Mesh() = default;

    Mesh(const Mesh& mesh) :vertices(mesh.vertices), indices(mesh.indices) {}

    Mesh& operator=(const Mesh& mesh)
    {
        if (&mesh == this)
            return *this;
        vertices = mesh.vertices;
        indices = mesh.indices;
        return *this;
    }

    void setVertices(Vertex* _vs, int count)
    {
        vertices.resize(count);
        new(&vertices[0])std::vector<Vertex>(_vs, _vs + count);
    }

    void setIndices(int* _es, int count)
    {
        indices.resize(count);
        new(&indices)std::vector<unsigned int>(_es, _es + count);
    }

    void asTriangle(const Vector3D p1, const Vector3D p2, const Vector3D p3);
    void asBox(double width, double height, double depth);
};

