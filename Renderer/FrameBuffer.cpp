#pragma once

#include "FrameBuffer.h"

void FrameBuffer::clearColorAndDepthBuffer(const Vector4D& color)
{
    // ��䲻͸����ɫ
    unsigned char red = static_cast<unsigned char>(255 * color.x);
    unsigned char green = static_cast<unsigned char>(255 * color.y);
    unsigned char blue = static_cast<unsigned char>(255 * color.z);
    unsigned char alpha = static_cast<unsigned char>(255 * color.w);

    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            m_depthBuffer[row * m_width + col] = 1.0f;
            m_colorBuffer[row * m_width * m_channel + col * m_channel + 0] = red;
            m_colorBuffer[row * m_width * m_channel + col * m_channel + 1] = green;
            m_colorBuffer[row * m_width * m_channel + col * m_channel + 2] = blue;
            m_colorBuffer[row * m_width * m_channel + col * m_channel + 3] = alpha;
        }
    }
}

double FrameBuffer::getDepth(const unsigned int& x, const unsigned int& y) const
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return 0.0f;
    return m_depthBuffer[y * m_width + x];
}

void FrameBuffer::drawDepth(const unsigned int& x, const unsigned int& y, const double& value)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;
    unsigned int index = y * m_width + x;
    m_depthBuffer[index] = value;
}

void FrameBuffer::drawPixel(unsigned int x, unsigned int y, const Vector4D& color)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;
    unsigned char red = static_cast<unsigned char>(255 * color.x);
    unsigned char green = static_cast<unsigned char>(255 * color.y);
    unsigned char blue = static_cast<unsigned char>(255 * color.z);
    unsigned char alpha = static_cast<unsigned char>(255 * color.w);
    unsigned int index = y * m_width * m_channel + x * m_channel;
    m_colorBuffer[index + 0] = red;
    m_colorBuffer[index + 1] = green;
    m_colorBuffer[index + 2] = blue;
    m_colorBuffer[index + 3] = alpha;
}

void FrameBuffer::outPut() const {
    for (unsigned int row = 0; row < m_height; row++) {
        for (unsigned int col = 0; col < m_width; col++) {
            unsigned int index = row * m_width * m_channel + col * m_channel;
            // std::cout << (unsigned char)m_colorBuffer[index + 0] << " " << (unsigned char)m_colorBuffer[index + 1] << " " << (unsigned char)m_colorBuffer[index + 2] << "\n";
            for (int k = 0; k < 3; k++) {
                unsigned char now = m_colorBuffer[index + k];
                std::cout << (unsigned int)now << (k == 2 ? "\n" : " ");
            }
        }
    }
}