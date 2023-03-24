#pragma once
#include <iostream>
#include <cmath>

const float M_PI = (float)acos(-1.0f);

class Vector2D {
public :
	float x, y;
public :
	Vector2D():x(0.0f), y(0.0f) {}
	Vector2D(const Vector2D& vec) :x(vec.x), y(vec.y) {}
	Vector2D(const float* val) :x(val[0]), y(val[1]) {}
	Vector2D(const float newX, const float newY) :x(newX), y(newY) {}
	~Vector2D() = default;

	void set(const Vector2D& vec) { x = vec.x, y = vec.y; }
	void set(const float* val) { x = val[0], y = val[1]; }
	void set(const float newX, const float newY) { x = newX, y = newY; }
	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	float getX() const { return x; }
	float getY() const { return y; }
	
	float magnitude() const { return static_cast<float>(sqrt(x * x + y * y)); }
	float squaredMagnitude() const { return static_cast<float>(x * x + y * y); }

	void normalize() { float tmp = this->magnitude(); x /= tmp, y /= tmp; }
	Vector2D getNormalize() const { float tmp = this->magnitude(); return Vector2D(x / tmp, y / tmp); }
	
	float dotProduct(const Vector2D& vec) const { return x * vec.x + y * vec.y; }
	float crossProduct(const Vector2D& vec) const { return x * vec.y - y * vec.x; }

	const float& operator[](const int position) const {
		if (position == 0) return x;
		else if (position == 1) return y;
		else {
			std::cerr << "out of bound in Vector2D";
			return x;
		}
	}
	float& operator[](const int position) {
		if (position == 0) return x;
		else if (position == 1) return y;
		else {
			std::cerr << "out of bound in Vector2D";
			return x;
		}
	}
	Vector2D operator+(const Vector2D& vec) const { return Vector2D(x + vec.x, y + vec.y); }
	Vector2D operator-(const Vector2D& vec) const { return Vector2D(x - vec.x, y - vec.y); }
	Vector2D operator*(const float k) const { return Vector2D(x * k, y * k); }
	Vector2D operator/(const float k) const { return (k == 0.0f) ? Vector2D(0.0f, 0.0f) : Vector2D(x / k, y / k); }

	bool operator==(const Vector2D& vec) const { return (x == vec.x) && (y == vec.y); }
	bool operator!=(const Vector2D& vec) const { return !((*this) == vec); }

	void operator+=(const Vector2D& vec) { x += vec.x, y += vec.y; }
	void operator-=(const Vector2D& vec) { x -= vec.x, y -= vec.y; }
	void operator*=(const float k) { x *= k, y *= k; }
	void operator/=(const float k) { if (k != 0.0f) x /= k, y /= k; }

	Vector2D operator+() const { return *this; }
	Vector2D operator-() const { return Vector2D(-x, -y); }
};

class Vector3D {
public :
	float x, y, z;
public :
	Vector3D() :x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(const Vector3D& vec) :x(vec.x), y(vec.y), z(vec.z) {}
	Vector3D(const float* val) :x(val[0]), y(val[1]), z(val[2]) {}
	Vector3D(const float newX, const float newY, const float newZ) :x(newX), y(newY), z(newZ) {}
	~Vector3D() = default;

	void set(const Vector3D& vec) { x = vec.x, y = vec.y, z = vec.z; }
	void set(const float* val) { x = val[0], y = val[1], z = val[2]; }
	void set(const float newX, const float newY, const float newZ) { x = newX, y = newY, z = newZ; }
	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setZ(const float newZ) { z = newZ; }
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	float magnitude() const { return static_cast<float>(sqrt(x * x + y * y + z * z)); }
	float squaredMagnitude() const { return static_cast<float>(x * x + y * y + z * z); }

	void normalize() { float tmp = this->magnitude(); x /= tmp, y /= tmp, z/= tmp; }
	Vector3D getNormalize() const { float tmp = this->magnitude(); return Vector3D(x / tmp, y / tmp, z / tmp); }

	float dotProduct(const Vector3D& vec) const { return x * vec.x + y * vec.y + z * vec.z; }
	Vector3D crossProduct(const Vector3D& vec) const { return Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x); }
	float crossProductNum(const Vector3D& vec) const { return y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x; }

	const float& operator[](const int position) const {
		if (position == 0) return x;
		else if (position == 1) return y;
		else if (position == 2) return z;
		else {
			std::cerr << "out of bound in Vector3D";
			return x;
		}
	}
	float& operator[](const int position) {
		if (position == 0) return x;
		else if (position == 1) return y;
		else if (position == 2) return z;
		else {
			std::cerr << "out of bound in Vector3D";
			return x;
		}
	}
	Vector3D operator+(const Vector3D& vec) const { return Vector3D(x + vec.x, y + vec.y, z + vec.z); }
	Vector3D operator-(const Vector3D& vec) const { return Vector3D(x - vec.x, y - vec.y, z - vec.z); }
	Vector3D operator*(const float k) const { return Vector3D(x * k, y * k, z * k); }
	Vector3D operator/(const float k) const { return (k == 0.0f) ? Vector3D(0.0f, 0.0f, 0.0f) : Vector3D(x / k, y / k, z / k); }

	bool operator==(const Vector3D& vec) const { return (x == vec.x) && (y == vec.y) && (z == vec.z); }
	bool operator!=(const Vector3D& vec) const { return !((*this) == vec); }

	void operator+=(const Vector3D& vec) { x += vec.x, y += vec.y, z += vec.z; }
	void operator-=(const Vector3D& vec) { x -= vec.x, y -= vec.y, z -= vec.z; }
	void operator*=(const float k) { x *= k, y *= k, z *= k; }
	void operator/=(const float k) { if (k != 0.0f) x /= k, y /= k, z /= k; }

	Vector3D operator+() const { return *this; }
	Vector3D operator-() const { return Vector3D(-x, -y, -z); }
};

class Vector4D {
public:
	float x, y, z, w;
public:
	Vector4D() :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4D(const Vector4D& vec) :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	Vector4D(const Vector3D& vec) :x(vec.x), y(vec.y), z(vec.z), w(1.0f) {}
	Vector4D(const float* val) :x(val[0]), y(val[1]), z(val[2]), w(val[3]) {}
	Vector4D(const float newX, const float newY, const float newZ) :x(newX), y(newY), z(newZ), w(1.0f) {}
	Vector4D(const float newX, const float newY, const float newZ, const float newW) :x(newX), y(newY), z(newZ), w(newW) {}

	void set(const Vector4D& vec) { x = vec.x, y = vec.y, z = vec.z, w = vec.w; }
	void set(const float* val) { x = val[0], y = val[1], z = val[2], w = val[3]; }
	void set(const float newX, const float newY, const float newZ, const float newW) { x = newX, y = newY, z = newZ, w = newW; }
	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setZ(const float newZ) { z = newZ; }
	void setW(const float newW) { w = newW; }
	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getW() const { return w; }
	Vector3D toVec3() const { return Vector3D(x, y, z); }

	float magnitude() const { return static_cast<float>(sqrt(x * x + y * y + z * z + w * w)); }
	float squaredMagnitude() const { return static_cast<float>(x * x + y * y + z * z + w * w); }

	float dotProduct(const Vector4D& vec) const { return x * vec.x + y * vec.y + z * vec.z + w * vec.w; }

	const float& operator[](const int position) const {
		if (position == 0) return x;
		else if (position == 1) return y;
		else if (position == 2) return z;
		else if (position == 3) return w;
		else {
			std::cerr << "out of bound in Vector4D";
			return x;
		}
	}
	float& operator[](const int position) {
		if (position == 0) return x;
		else if (position == 1) return y;
		else if (position == 2) return z;
		else if (position == 3) return w;
		else {
			std::cerr << "out of bound in Vector4D";
			return x;
		}
	}
	Vector4D operator+(const Vector4D& vec) const { return Vector4D(x + vec.x, y + vec.y, z + vec.z, w + vec.w); }
	Vector4D operator-(const Vector4D& vec) const { return Vector4D(x - vec.x, y - vec.y, z - vec.z, w - vec.w); }
	Vector4D operator*(const float k) const { return Vector4D(x * k, y * k, z * k, w * k); }
	Vector4D operator/(const float k) const { return (k == 0.0f) ? Vector4D(0.0f, 0.0f, 0.0f, 0.0f) : Vector4D(x / k, y / k, z / k, w / k); }

	bool operator==(const Vector4D& vec) const { return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w); }
	bool operator!=(const Vector4D& vec) const { return !((*this) == vec); }

	void operator+=(const Vector4D& vec) { x += vec.x, y += vec.y, z += vec.z, w += vec.w; }
	void operator-=(const Vector4D& vec) { x -= vec.x, y -= vec.y, z -= vec.z, w -= vec.w; }
	void operator*=(const float k) { x *= k, y *= k, z *= k, w *= k; }
	void operator/=(const float k) { if (k != 0.0f) x /= k, y /= k, z /= k, w /= k; }

	Vector4D operator+() const { return *this; }
	Vector4D operator-() const { return Vector4D(-x, -y, -z, -w); }
};

class Matrix4x4 {
public :
	float entries[16];
public :
	Matrix4x4() { loadZero(); }
	Matrix4x4(bool flag) { flag ? loadIdentity() : loadZero(); }
	Matrix4x4(const Matrix4x4& mat) { for (int i = 0; i < 16; i++) entries[i] = mat[i]; }
	Matrix4x4(const float* val) { for (int i = 0; i < 16; i++) entries[i] = val[i]; }
	Matrix4x4(const float  e0, float  e1, float  e2, float  e3,
		float  e4, float  e5, float  e6, float  e7,
		float  e8, float  e9, float e10, float e11,
		float e12, float e13, float e14, float e15) {
		entries[0] = e0, entries[1] = e1, entries[2] = e2, entries[3] = e3;
		entries[4] = e4, entries[5] = e5, entries[6] = e6, entries[7] = e7;
		entries[8] = e8, entries[9] = e9, entries[10] = e10, entries[11] = e11;
		entries[12] = e12, entries[13] = e13, entries[14] = e14, entries[15] = e15;
	}

	void setEntry(const int position, const float val) { entries[position] = val; }
	float getEntry(const int position) const { return entries[position]; }
	Vector4D getRow(const int row) const { return Vector4D(entries[row * 4], entries[row * 4 + 1], entries[row * 4 + 2], entries[row * 4 + 3]); }
	Vector4D getCol(const int col) const { return Vector4D(entries[col], entries[4 + col], entries[8 + col], entries[12 + col]); }
	void loadIdentity() { loadZero(); for (int i = 0; i < 4; i++) entries[i * 4 + i] = 1; }
	void loadZero() { for (int i = 0; i < 16; i++) entries[i] = 0; }

	const float& operator[](const int position) const { return entries[position]; }
	float& operator[](const int position) { return entries[position]; }
	Matrix4x4 operator+(const Matrix4x4& mat) const { Matrix4x4 ret(false); for (int i = 0; i < 16; i++) ret[i] = entries[i] + mat[i]; return ret; }
	Matrix4x4 operator-(const Matrix4x4& mat) const { Matrix4x4 ret(false); for (int i = 0; i < 16; i++) ret[i] = entries[i] - mat[i]; return ret; }
	Matrix4x4 operator*(const Matrix4x4& mat) const {
		Matrix4x4 ret(false);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				for (int k = 0; k < 4; k++)
					ret[i * 4 + j] += entries[4 * i + k] * mat[4 * k + j];
		return ret;
	}
	Matrix4x4 operator*(const float k) const { Matrix4x4 ret(false); for (int i = 0; i < 16; i++) ret[i] = entries[i] * k; return ret; }
	Matrix4x4 operator/(const float k) const { Matrix4x4 ret(false); if (k != 0) for (int i = 0; i < 16; i++) ret[i] = entries[i] / k; return ret; }

	void operator+=(const Matrix4x4& mat) { for (int i = 0; i < 16; i++) entries[i] += mat[i]; }
	void operator-=(const Matrix4x4& mat) { for (int i = 0; i < 16; i++) entries[i] -= mat[i]; }
	void operator*=(const float k) { for (int i = 0; i < 16; i++) entries[i] *= k; }
	void operator/=(const float k) { if (k != 0) for (int i = 0; i < 16; i++) entries[i] /= k; }

	Matrix4x4 operator+() const { return  *this; }
	Matrix4x4 operator-() const { return Matrix4x4(-entries[0], -entries[1], -entries[2], -entries[3], -entries[4], -entries[5], -entries[6], -entries[7], -entries[8], -entries[9], -entries[10], -entries[11], -entries[12], -entries[13], -entries[14], -entries[15]); }
	Vector4D operator*(const Vector4D& vec) const {
		Vector4D ret = Vector4D();
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 1; j++)
				for (int k = 0; k < 4; k++)
					ret[i] += entries[4 * i + k] * vec[k];
		return ret;
	}

	void setTranslation(const Vector3D& translation) {
		loadIdentity();
		for (int i = 0; i < 3; i++) entries[i * 4 + 3] = translation[i];
	}
	void setScale(const Vector3D& scaleFactor) {
		loadIdentity();
		for (int i = 0; i < 3; i++) entries[i * 4 + i] = scaleFactor[i];
	}
	void setRotationX(const double angle) {
		loadIdentity();
		entries[5] = static_cast<float>(cos(M_PI * angle / 180.0f));
		entries[9] = static_cast<float>(sin(M_PI * angle / 180.0f));
		entries[6] = -entries[9];
		entries[10] = entries[5];
	}
	void setRotationY(const double angle) {
		loadIdentity();
		entries[0] = static_cast<float>(cos(M_PI * angle / 180.0f));
		entries[8] = -static_cast<float>(sin(M_PI * angle / 180.0f));
		entries[2] = -entries[8];
		entries[10] = entries[0];
	}
	void setRotationZ(const double angle) {
		loadIdentity();
		entries[0] = static_cast<float>(cos(M_PI * angle / 180.0f));
		entries[4] = static_cast<float>(sin(M_PI * angle / 180.0f));
		entries[1] = -entries[4];
		entries[5] = entries[0];
	}
	void setRotationAxis(const double angle, const Vector3D& axis) {
		Vector3D u = axis.getNormalize();

		float sinAngle = static_cast<float>(sin(M_PI * angle / 180));
		float cosAngle = static_cast<float>(cos(M_PI * angle / 180));
		float oneMinusCosAngle = 1.0f - cosAngle;

		loadIdentity();

		entries[0] = (u.x) * (u.x) + cosAngle * (1 - (u.x) * (u.x));
		entries[1] = (u.x) * (u.y) * (oneMinusCosAngle)-sinAngle * u.z;
		entries[2] = (u.x) * (u.z) * (oneMinusCosAngle)+sinAngle * u.y;

		entries[4] = (u.x) * (u.y) * (oneMinusCosAngle)+sinAngle * u.z;
		entries[5] = (u.y) * (u.y) + cosAngle * (1 - (u.y) * (u.y));
		entries[6] = (u.y) * (u.z) * (oneMinusCosAngle)-sinAngle * u.x;

		entries[8] = (u.x) * (u.z) * (oneMinusCosAngle)-sinAngle * u.y;
		entries[9] = (u.y) * (u.z) * (oneMinusCosAngle)+sinAngle * u.x;
		entries[10] = (u.z) * (u.z) + cosAngle * (1 - (u.z) * (u.z));
	}
	void setPerspective(float fovy, float aspect, float near, float far) {
		loadZero();
		// ½Ç¶È±ä»¡¶È
		float rFovy = fovy * M_PI / 180.0f;
		const float tanHalfFovy = tanf(static_cast<float>(rFovy * 0.5f));
		entries[0] = 1.0f / (aspect * tanHalfFovy);
		entries[5] = 1.0f / (tanHalfFovy);
		entries[10] = -(far + near) / (far - near);
		entries[14] = -1.0f;
		entries[11] = (-2.0f * near * far) / (far - near);
	}
	void setPerspective(float left, float right, float bottom, float top, float near, float far) {
		loadZero();
		entries[0] = 2.0f * near / (right - left);
		entries[5] = 2.0f * near / (top - bottom);
		entries[10] = -(far + near) / (far - near);
		entries[14] = -1.0f;
		entries[11] = (-2.0f * near *far) / (far - near);
	}
	void setOrtho(float left, float right, float bottom, float top, float near, float far) {
		loadIdentity();
		entries[0] = 2.0f / (right - left);
		entries[5] = 2.0f / (top - bottom);
		entries[10] = -2.0f / (far - near);
		/*
		entries[3] = -(right + left) / (right - left);
		entries[7] = -(top + bottom) / (top - bottom);*/
		entries[11] = -(far + near) / (far - near);
		
	}
	void setLookAt(Vector3D cameraPos, Vector3D target, Vector3D worldUp)
	{
		Vector3D zAxis = cameraPos - target;
		zAxis.normalize();
		std::cerr << "zAxis:\n";
		for (int i = 0; i < 3; i++) std::cerr << zAxis[i] << (i % 3 == 2 ? "\n" : " ");
		Vector3D xAxis = worldUp.crossProduct(zAxis);
		xAxis.normalize();
		std::cerr << "xAxis:\n";
		for (int i = 0; i < 3; i++) std::cerr << xAxis[i] << (i % 3 == 2 ? "\n" : " ");
		Vector3D yAxis = zAxis.crossProduct(xAxis);
		yAxis.normalize();
		std::cerr << "yAxis:\n";
		for (int i = 0; i < 3; i++) std::cerr << yAxis[i] << (i % 3 == 2 ? "\n" : " ");

		loadIdentity();
		entries[0] = xAxis.x;
		entries[1] = xAxis.y;
		entries[2] = xAxis.z;

		entries[4] = yAxis.x;
		entries[5] = yAxis.y;
		entries[6] = yAxis.z;

		entries[8] = zAxis.x;
		entries[9] = zAxis.y;
		entries[10] = zAxis.z;

		entries[3] = -(xAxis.dotProduct(cameraPos));
		entries[7] = -(yAxis.dotProduct(cameraPos));
		entries[11] = -(zAxis.dotProduct(cameraPos));
	}
	void setViewPort(int left, int top, int width, int height) {
		loadIdentity();
		entries[0] = width / 2.0f;
		entries[5] = -height / 2.0f;
		entries[3] = left + width / 2.0f;
		entries[7] = top + height / 2.0f;
	}
};

/*
0  1  2  3
4  5  6  7
8  9  10 11
12 13 14 15

0  4  8  12
1  5  9  13
2  6  10 14
3  7  11 15
*/