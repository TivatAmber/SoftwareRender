#pragma once
#include "BaseShader.h"
class SimpleShader : public BaseShader
{
private:
    Matrix4x4 m_modelMatrix;
    Matrix4x4 m_viewMatrix;
    Matrix4x4 m_projectMatrix;
public:
    SimpleShader() = default;
    virtual ~SimpleShader() = default;

    virtual VertexOut vertexShader(const Vertex& in);
    virtual void setModelMatrix(const Matrix4x4& world);
    virtual void setViewMatrix(const Matrix4x4& view);
    virtual void setProjectMatrix(const Matrix4x4& project);
};
