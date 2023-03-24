#pragma once

#include "Rmath.h"

class Vertex {
public :
	Vector4D position;
	Vector4D color;
    Vector2D texcoord;
	Vector3D normal; // ·¨Ïß

    Vertex() = default;
    Vertex(Vector4D tPosition, Vector4D tColor, Vector2D tTexcoord, Vector3D tNormal) :position(tPosition), color(tColor), texcoord(tTexcoord), normal(tNormal) {}
    Vertex(const Vertex& ver) :position(ver.position), color(ver.color), texcoord(ver.texcoord), normal(ver.normal) {}
    ~Vertex() = default;
};

