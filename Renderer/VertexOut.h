#pragma once

#include "Rmath.h"

class VertexOut
{
public:
    Vector4D positionTrans;  //����任�������
    Vector4D positionH;      //ͶӰ�任�������
    Vector2D texcoord;  //����
    Vector3D normal;	//����
    Vector4D color;	    //��ɫ

    VertexOut() = default;
    VertexOut(Vector4D tPositionTrans, Vector4D tPositionH, Vector2D tTexcoord, Vector3D tNormal, Vector4D tColor) :positionTrans(tPositionTrans), positionH(tPositionH), texcoord(tTexcoord), normal(tNormal), color(tColor){}
    VertexOut(const VertexOut& verO) :positionTrans(verO.positionTrans), positionH(verO.positionH), texcoord(verO.texcoord), normal(verO.normal), color(verO.color) {}
};

