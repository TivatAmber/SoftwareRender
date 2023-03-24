#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture2D.h"

const float INV_SCALE = 1.0f / 255.0f;

bool Texture2D::loadImage(const std::string& path) {
	if (m_pixelBuffer) delete m_pixelBuffer;
	m_pixelBuffer = nullptr;
	m_pixelBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_channel, 0);
	return m_pixelBuffer != nullptr;
}

Vector4D Texture2D::simple(const Vector2D& texcoord) {
	Vector4D ret(0.0f, 0.0f, 0.0f, 1.0f);
	if (m_pixelBuffer == nullptr) return ret;
	unsigned int x = 0, y = 0;
	float factorX = 0.0f, factorY = 0.0f;

	if (0.0f <= texcoord.x && texcoord.x <= 1.0f && 0.0f <= texcoord.y && texcoord.y <= 1.0f) {
		float trueX = texcoord.x * (m_width - 1);
		float trueY = texcoord.y * (m_height - 1);
		x = static_cast<unsigned int>(trueX);
		y = static_cast<unsigned int>(trueY);
		factorX = trueX - x;
		factorY = trueY - y;
	}
	else {
		float trueX = texcoord.x, trueY = texcoord.y;

		if (texcoord.x < 0.0f) trueX = static_cast<int>(texcoord.x) - texcoord.x;
		else if (texcoord.x > 1.0f) trueX = 1.0f - (texcoord.x - static_cast<int>(texcoord.x));
		if (texcoord.y < 0.0f) trueY = static_cast<int>(texcoord.y) - texcoord.y;
		else if (texcoord.y > 1.0f) trueY = 1.0f - (texcoord.y - static_cast<int>(texcoord.y));

		trueX = texcoord.x * (m_width - 1);
		trueY = texcoord.y * (m_height - 1);
		x = static_cast<unsigned int>(trueX);
		y = static_cast<unsigned int>(trueY);
		factorX = trueX - x;
		factorY = trueY - y;
	}

    // texel fetching.
    Vector3D texels[4];
    int index[4];
    index[0] = (x * m_width + y) * m_channel;
    index[1] = (x * m_width + y + 1) * m_channel;
    index[2] = ((x + 1) * m_width + y + 1) * m_channel;
    index[3] = ((x + 1) * m_width + y) * m_channel;

    // left bottom
    texels[0].x = static_cast<float>(m_pixelBuffer[index[0] + 0]) * INV_SCALE;
    texels[0].y = static_cast<float>(m_pixelBuffer[index[0] + 1]) * INV_SCALE;
    texels[0].z = static_cast<float>(m_pixelBuffer[index[0] + 2]) * INV_SCALE;
    //return texels[0];

    // left top
    texels[1].x = static_cast<float>(m_pixelBuffer[index[1] + 0]) * INV_SCALE;
    texels[1].y = static_cast<float>(m_pixelBuffer[index[1] + 1]) * INV_SCALE;
    texels[1].z = static_cast<float>(m_pixelBuffer[index[1] + 2]) * INV_SCALE;

    // right top
    texels[2].x = static_cast<float>(m_pixelBuffer[index[2] + 0]) * INV_SCALE;
    texels[2].y = static_cast<float>(m_pixelBuffer[index[2] + 1]) * INV_SCALE;
    texels[2].z = static_cast<float>(m_pixelBuffer[index[2] + 2]) * INV_SCALE;

    // right bottom
    texels[3].x = static_cast<float>(m_pixelBuffer[index[3] + 0]) * INV_SCALE;
    texels[3].y = static_cast<float>(m_pixelBuffer[index[3] + 1]) * INV_SCALE;
    texels[3].z = static_cast<float>(m_pixelBuffer[index[3] + 2]) * INV_SCALE;

    // bilinear interpolation.
    // horizational
    texels[0] = texels[0] * (1.0 - factorX) + texels[3] * factorX;
    texels[1] = texels[1] * (1.0 - factorX) + texels[2] * factorX;
    //vertical
    ret = texels[0] * (1.0 - factorY) + texels[1] * factorY;

    return ret;
}