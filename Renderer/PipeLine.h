#pragma once

#include "Base.h"

class PipeLine {
private :
	int m_width, m_height;
	BaseShader* m_shader;
	FrameBuffer* m_buffer;
	Texture2D* m_texture;
	Matrix4x4 viewPortMatrix;
	RenderMode m_render_mode;
	std::vector<Vertex> m_vertices;
	std::vector<VertexOut> m_vertices_out;
	std::vector<unsigned int> m_indices;

public :
	PipeLine(int width, int height) :m_width(width), m_height(height), m_shader(nullptr), m_buffer(nullptr), m_texture(nullptr) {}
	~PipeLine();

	void initialize();
	void setTransform(const Matrix4x4 world, const Matrix4x4 view, const Matrix4x4 project);
	void setTransform(const Matrix4x4 world);
	void clearBuffer(const Vector4D& color, bool depth = false);
	void setVertexBuffer(const std::vector<Vertex>& vertices) { m_vertices = vertices; }
	void setIndexBuffer(const std::vector<unsigned int>& indices) { m_indices = indices; }
	void setShaderMode(ShadingMode mode);
	void setRenderMode(RenderMode mode);
	void setTexture(const int tWidth, const int tHeight, const int tChannel, const std::string path);
	void drawIndex(Vector4D* color = nullptr);
	
	Vector3D barycentricCoordinates(VertexOut* triangle, Vector3D point);
	void drawLine(VertexOut* line);
	void drawLine(VertexOut* line, const Vector4D& color);
	void drawTriangle(VertexOut* triangle);
	void drawTriangle(VertexOut* triangle, const Vector4D& color);

	unsigned char* output() { return m_buffer->getColorBuffer(); }
	void printFrame() const { m_buffer->outPut(); }
}; 

