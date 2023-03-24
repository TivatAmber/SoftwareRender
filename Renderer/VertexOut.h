#pragma once

#include "Rmath.h"

class VertexOut
{
public:
    Vector4D positionTrans;  //世界变换后的坐标
    Vector4D positionH;      //投影变换后的坐标
    Vector2D texcoord;  //纹理
    Vector3D normal;	//法线
    Vector4D color;	    //颜色

    VertexOut() = default;
    VertexOut(Vector4D tPositionTrans, Vector4D tPositionH, Vector2D tTexcoord, Vector3D tNormal, Vector4D tColor) :positionTrans(tPositionTrans), positionH(tPositionH), texcoord(tTexcoord), normal(tNormal), color(tColor){}
    VertexOut(const VertexOut& verO) :positionTrans(verO.positionTrans), positionH(verO.positionH), texcoord(verO.texcoord), normal(verO.normal), color(verO.color) {}
};

