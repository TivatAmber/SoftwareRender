#pragma once

#include "PipeLine.h"

PipeLine::~PipeLine() {
	if (m_shader) delete m_shader;
	if (m_buffer) delete m_buffer;
	if (m_texture) delete m_texture;
	m_shader = nullptr;
	m_buffer = nullptr;
	m_texture = nullptr;
}

void PipeLine::initialize() {
	if (m_shader) delete m_shader;
	if (m_buffer) delete m_buffer;
	if (m_texture) delete m_texture;
	viewPortMatrix.setViewPort(0, 0, m_width, m_height);
	m_buffer = new FrameBuffer(m_width, m_height);
	m_shader = new SimpleShader();
	m_texture = new Texture2D();
}

void PipeLine::setTransform(const Matrix4x4 world, const Matrix4x4 view, const Matrix4x4 project) {
	m_shader->setModelMatrix(world);
	m_shader->setViewMatrix(view);
	m_shader->setProjectMatrix(project);
}

void PipeLine::setTransform(const Matrix4x4 world) {
	m_shader->setModelMatrix(world);
}

void PipeLine::drawIndex(Vector4D* color) {
	if (m_indices.empty()) return;
	m_vertices_out.resize(m_vertices.size());
	//std::cerr << "drawIndex\n\n";
	// 转换图元
	for (int i = 0; i < m_vertices.size(); i++) {
		//变换顶点
		m_vertices_out[i] = m_shader->vertexShader(m_vertices[i]);
		//视口变换，透视除法
		m_vertices_out[i].positionH = viewPortMatrix * m_vertices_out[i].positionH;
		m_vertices_out[i].positionH /= m_vertices_out[i].positionH.getW();
		//for (int k = 0; k < 4; k++) std::cerr << m_vertices_out[i].positionH[k] << " "; std::cerr << "\n";
	}
	//std::cerr << "drawIndex\n\n";
	for (unsigned i = 0; i < m_indices.size() / 3; i++) {
		VertexOut nowV[4];
		for (int j = 0; j < 3; j++) nowV[j] = m_vertices_out[m_indices[3 * i + j]];
		if (m_render_mode & RenderMode::WIRE) {
			nowV[3] = VertexOut(nowV[0]);
			if (color != nullptr) for (int j = 0; j < 3; j++) drawLine(nowV + j, *color);
			else for (int j = 0; j < 3; j++) drawLine(nowV + j);
		}
		if (m_render_mode & RenderMode::FILL) {
			if (color != nullptr && m_render_mode != RenderMode::WIREANDFILL) drawTriangle(nowV, *color);
			else drawTriangle(nowV);
		}
	}
}

void PipeLine::clearBuffer(const Vector4D& color, bool depth) {
	m_buffer->clearColorAndDepthBuffer(color);
}

void PipeLine::setShaderMode(ShadingMode mode) {
	if (m_shader) delete m_shader;
	if (mode == ShadingMode::SIMPLE) m_shader = new SimpleShader();
}

void PipeLine::setRenderMode(RenderMode mode) {
	m_render_mode = mode;
}

void PipeLine::setTexture(const int tWidth, const int tHeight, const int tChannel, const std::string path) {
	if (m_texture) delete m_texture;
	m_texture = new Texture2D(tWidth, tHeight, tChannel, path);
}

Vector3D PipeLine::barycentricCoordinates(VertexOut* triangle, Vector3D point) {
	// tri[0] A, tri[1] B, tri[2] C;
	Vector3D CB(triangle[2].positionH.toVec3() - triangle[1].positionH.toVec3());
	Vector3D AB(triangle[0].positionH.toVec3() - triangle[1].positionH.toVec3());
	Vector3D PB(point - triangle[1].positionH.toVec3());
	Vector3D AC(triangle[0].positionH.toVec3() - triangle[2].positionH.toVec3());
	Vector3D PC(point - triangle[2].positionH.toVec3());
	Vector3D BC = -CB;
	float i = CB.crossProductNum(PB) / CB.crossProductNum(AB);
	float j = AC.crossProductNum(PC) / AC.crossProductNum(BC);
	return Vector3D(i, j, 1.0f - i - j);
}

void PipeLine::drawLine(VertexOut* line) {
	bool steep = abs(line[1].positionH.getY() - line[0].positionH.getY()) > abs(line[1].positionH.getX() - line[0].positionH.getX());
	if (steep) std::swap(line[0].positionH.x, line[0].positionH.y), std::swap(line[1].positionH.x, line[1].positionH.y);
	bool flag = line[0].positionH.getX() > line[1].positionH.getX();
	if (flag) std::swap(line[0], line[1]);
	int deltaX = line[1].positionH.getX() - line[0].positionH.getX();
	int deltaY = abs(line[1].positionH.getY() - line[0].positionH.getY());
	float error = 0.0f;
	float deltaError = 1.0f * deltaY / deltaX;
	int stepY = line[0].positionH.getY() < line[1].positionH.getY() ? 1 : -1;
	int y = line[0].positionH.getY();
	for (int x = line[0].positionH.getX(); x <= line[1].positionH.getX(); x++) {
		float t = (1.0f * x - line[0].positionH.getX()) / deltaX;
		float z = (1.0f - t) * line[0].positionH.getZ() + t * line[1].positionH.getZ();
		z = (z + 1.0f) / 2.0f;
		if (steep) {
			float depth = m_buffer->getDepth(y, x);
			if (z < depth && z > 0.0f) {
				m_buffer->drawDepth(y, x, z);
				m_buffer->drawPixel(y, x, Vector4D(1.0f * x / m_width, 1.0f * y / m_height, z));
			}
		}
		else {
			float depth = m_buffer->getDepth(x, y);
			if (z < depth && z > 0.0f) {
				m_buffer->drawDepth(x, y, z);
				m_buffer->drawPixel(x, y, Vector4D(1.0f * x / m_width, 1.0f * y / m_height, z));
			}
		}
		error = error + deltaError;
		while (error >= 0.5f) error -= 1.0f, y += stepY;
	}
	if (flag) std::swap(line[0], line[1]);
	if (steep) std::swap(line[0].positionH.x, line[0].positionH.y), std::swap(line[1].positionH.x, line[1].positionH.y);
}

void PipeLine::drawLine(VertexOut* line, const Vector4D& color) {
	bool steep = abs(line[1].positionH.getY() - line[0].positionH.getY()) > abs(line[1].positionH.getX() - line[0].positionH.getX());
	if (steep) std::swap(line[0].positionH.x, line[0].positionH.y), std::swap(line[1].positionH.x, line[1].positionH.y);
	bool flag = line[0].positionH.getX() > line[1].positionH.getX();
	if (flag) std::swap(line[0], line[1]);
	int deltaX = line[1].positionH.getX() - line[0].positionH.getX();
	int deltaY = abs(line[1].positionH.getY() - line[0].positionH.getY());
	float error = 0.0f;
	float deltaError = 1.0f * deltaY / deltaX;
	int stepY = line[0].positionH.getY() < line[1].positionH.getY() ? 1 : -1;
	int y = line[0].positionH.getY();
	for (int x = line[0].positionH.getX(); x <= line[1].positionH.getX(); x++) {
		float t = (1.0f * x - line[0].positionH.getX()) / deltaX;
		float z = (1.0f - t) * line[0].positionH.getZ() + t * line[1].positionH.getZ();
		z = (z + 1.0f) / 2.0f;
		if (steep) {
			float depth = m_buffer->getDepth(y, x);
			if (z < depth && z > 0.0f) {
				m_buffer->drawDepth(y, x, z);
				m_buffer->drawPixel(y, x, color);
			}
		}
		else {
			float depth = m_buffer->getDepth(x, y);
			if (z < depth && z > 0.0f) {
				m_buffer->drawDepth(x, y, z);
				m_buffer->drawPixel(x, y, color);
			}
		}
		error = error + deltaError;
		while (error >= 0.5f) error -= 1.0f, y += stepY;
	}
	if (flag) std::swap(line[0], line[1]);
	if (steep) std::swap(line[0].positionH.x, line[0].positionH.y), std::swap(line[1].positionH.x, line[1].positionH.y);
}

void PipeLine::drawTriangle(VertexOut* triangle) {
	Vector2D LD(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vector2D RU(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	for (int i = 0; i < 3; i++) {
		LD.x = std::max(0.0f, std::min(LD.x, triangle[i].positionH.x));
		LD.y = std::max(0.0f, std::min(LD.y, triangle[i].positionH.y));

		RU.x = std::min(1.0f * m_width - 1.0f, std::max(RU.x, triangle[i].positionH.x));
		RU.y = std::min(1.0f * m_height - 1.0f, std::max(RU.y, triangle[i].positionH.y));
	}
	for (unsigned int x = LD.x; x <= RU.x; x++) {
		for (unsigned int y = LD.y; y <= RU.y; y++) {
			Vector3D now = barycentricCoordinates(triangle, Vector3D(x, y, 0));
			if (now.x < 0 || now.y < 0 || now.z < 0) continue;
			float depth = m_buffer->getDepth(x, y);
			float z = now.x * triangle[0].positionH.getZ() + now.y * triangle[1].positionH.getZ() + now.z * triangle[2].positionH.getZ();
			z = (z + 1.0f) / 2.0f;
			if (z > depth || z < 0.0f) continue;
			m_buffer->drawDepth(x, y, z);
			/*
			Vector2D texcoord = triangle[0].texcoord * now.x + triangle[1].texcoord * now.y + triangle[2].texcoord * now.z;
			Vector4D color = m_texture->simple(texcoord);
			*/
			// Vector4D(1.0f * x / m_width, 1.0f * y / m_height, abs(z), 1.0f)
			Vector4D color = Vector4D(now.x, now.y, now.z, 1.0f);
			m_buffer->drawPixel(x, y, color);
		}
	}
}

void PipeLine::drawTriangle(VertexOut* triangle, const Vector4D& color) {
	Vector2D LD(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vector2D RU(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	for (int i = 0; i < 3; i++) {
		LD.x = std::max(0.0f, std::min(LD.x, triangle[i].positionH.x));
		LD.y = std::max(0.0f, std::min(LD.y, triangle[i].positionH.y));

		RU.x = std::min(1.0f * m_width - 1.0f, std::max(RU.x, triangle[i].positionH.x));
		RU.y = std::min(1.0f * m_height - 1.0f, std::max(RU.y, triangle[i].positionH.y));
	}
	for (unsigned int x = LD.x; x <= RU.x; x++) {
		for (unsigned int y = LD.y; y <= RU.y; y++) {
			Vector3D now = barycentricCoordinates(triangle, Vector3D(x, y, 0));
			if (now.x < 0 || now.y < 0 || now.z < 0) continue;
			float depth = m_buffer->getDepth(x, y);
			float z = now.x * triangle[0].positionH.getZ() + now.y * triangle[1].positionH.getZ() + now.z * triangle[2].positionH.getZ();
			z = (z + 1.0f) / 2.0f;
			if (z > depth || z < 0) continue;
			m_buffer->drawDepth(x, y, z);
			//m_buffer->drawPixel(x, y, Vector4D(1.0f * x / m_width, 1.0f * y / m_height, abs(z), 1.0f));
			//if (similar(now.x, 1.0f, 0.1f) || similar(now.y, 1.0f, 0.1f) || similar(now.z, 1.0f, 0.1f)) m_buffer->drawPixel(x, y, Vector4D(0.0f, 0.0f, 0.0f));
			m_buffer->drawPixel(x, y, color);
		}
	}
}