#pragma once

#include "VertexOut.h"
#include "Vertex.h"
#include "Rmath.h"

class BaseShader
{
public:
    BaseShader() = default;
    virtual ~BaseShader() = default;

    virtual VertexOut vertexShader(const Vertex& in) = 0;
    virtual void setModelMatrix(const Matrix4x4& world) = 0;
    virtual void setViewMatrix(const Matrix4x4& view) = 0;
    virtual void setProjectMatrix(const Matrix4x4& project) = 0;
};

