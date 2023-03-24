#pragma once
#include "Rmath.h"
#include <string>
class Texture2D
{
private :
	int m_width, m_height, m_channel;
	unsigned char* m_pixelBuffer;
public :
	Texture2D() : m_width(0), m_height(0), m_pixelBuffer(nullptr) {}
	Texture2D(std::string path) : m_width(0), m_height(0), m_pixelBuffer(nullptr) { loadImage(path); }
	Texture2D(int tWidth, int tHeight, int tChannel, std::string path) : m_width(tWidth), m_height(tHeight), m_channel(tChannel), m_pixelBuffer(nullptr) { loadImage(path); }
	~Texture2D() = default;
	Vector4D simple(const Vector2D& texcoord);
private :
	bool loadImage(const std::string& path);
};

