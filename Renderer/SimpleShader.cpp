#pragma once

#include "SimpleShader.h"

VertexOut SimpleShader::vertexShader(const Vertex & in)
{
    VertexOut result;
    result.positionTrans = m_modelMatrix * in.position;
    //std::cerr << "positionTrans: ";
    //for (int i = 0; i < 3; i++) std::cerr << result.positionTrans[i] << (i == 2 ? "\n" : " ");
    result.positionH = m_viewMatrix * result.positionTrans;
    //std::cerr << "positionH: ";
    //for (int i = 0; i < 3; i++) std::cerr << result.positionH[i] << (i == 2 ? "\n" : " ");
    result.positionH = m_projectMatrix * result.positionH;
    result.color = in.color;
    result.normal = in.normal;
    result.texcoord = in.texcoord;
    return result;
}

void SimpleShader::setModelMatrix(const Matrix4x4& world)
{
    m_modelMatrix = world;
}

void SimpleShader::setViewMatrix(const Matrix4x4& view)
{
    m_viewMatrix = view;
    std::cerr << "ViewMatrix: \n";
    for (int i = 0; i < 16; i++) std::cerr << view[i] << (i % 4 == 3 ? "\n" : " ");
}

void SimpleShader::setProjectMatrix(const Matrix4x4& project)
{
    m_projectMatrix = project;
}