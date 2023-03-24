#pragma once

#include "FrameBuffer.h"
#include "Rmath.h"
#include "Vertex.h"
#include "VertexOut.h"
#include "Mesh.h"
#include "BaseShader.h"
#include "SimpleShader.h"
#include "ObjModel.h"
#include "Texture2D.h"

enum ShadingMode {
	SIMPLE
};

enum RenderMode {
	WIRE = 1, FILL = 2, WIREANDFILL = 3
};