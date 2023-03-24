#pragma once

#include <cmath>
#include <vector>
#include "Rmath.h"

class FrameBuffer
{
private:
    int m_width, m_height, m_channel;
    std::vector<unsigned char> m_colorBuffer;
    std::vector<double> m_depthBuffer;

public:
    FrameBuffer(int width, int height) :m_channel(4), m_width(width), m_height(height) { m_colorBuffer.resize(m_width * m_height * m_channel, 255), m_depthBuffer.resize(m_width * m_height); }
    ~FrameBuffer() = default;

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }

    unsigned char* getColorBuffer() { return m_colorBuffer.data(); }
    void clearColorAndDepthBuffer(const Vector4D& color);
    double getDepth(const unsigned int& x, const unsigned int& y)const;
    void drawDepth(const unsigned int& x, const unsigned int& y, const double& value);
    void drawPixel(unsigned int x, unsigned int y, const Vector4D& color);
    void outPut() const;
};
