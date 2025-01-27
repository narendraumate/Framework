//
//  Matrix.h
//  Camaleao
//
//  Created by Narendra Umate on 11/4/12.
//  Copyright (c) 2012 Narendra Umate. All rights reserved.
//

#ifndef __Camaleao__Matrix__
#define __Camaleao__Matrix__

#include <string.h>

#include "Mathematics.h"
#include "Vector.h"
#include "Quaternion.h"

#if defined(__APPLE__) || defined(__linux__)
//	OpenGL
#define COLUMN_MAJOR
#elif defined(_WIN32)
// DirectX
#define ROW_MAJOR
#endif // defined(_WIN32)

class Vec2;
class Vec3;
class Vec4;
class Mat3;
class Mat3;
class Mat4;
class Quat;

//  Mat2

class Mat2 {
public:
	union {
		struct {
#if defined(ROW_MAJOR)
			float d00, d01;
			float d10, d11;
#elif defined(COLUMN_MAJOR)
			float d00, d10;
			float d01, d11;
#endif // defined(COLUMN_MAJOR)
		};
		float data[4];
	};

    Mat2(void);
    Mat2(const float& m00, const float& m01,
         const float& m10, const float& m11);
	Mat2(const Mat3& m);

    Mat2 transpose();
    Mat2 inverse();
    float determinant();

    Vec2 operator*(const Vec2& v) const;
    Mat2 operator*(const Mat2& v) const;
    Mat2 operator*(const float& f) const;
    Mat2 operator/(const float& f) const;
	bool operator==(const Mat2& m) const;
	bool operator!=(const Mat2& m) const;

    static const Mat2 identity;
    static const Mat2 zero;
};

//  Mat3

class Mat3 {
public:
	union {
		struct {
#if defined(ROW_MAJOR)
			float d00, d01, d02;
			float d10, d11, d12;
			float d20, d21, d22;
#elif defined(COLUMN_MAJOR)
			float d00, d10, d20;
			float d01, d11, d21;
			float d02, d12, d22;
#endif // defined(COLUMN_MAJOR)
		};
		float data[9];
	};

    Mat3(void);
    Mat3(const float& m00, const float& m01, const float& m02,
         const float& m10, const float& m11, const float& m12,
         const float& m20, const float& m21, const float& m22);
	Mat3(const Mat4& m);

    static Mat3 translate(const float& tx, const float& ty);
    static Mat3 translate(const Vec2& v);
    static Mat3 rotate(const float& theta);
    static Mat3 scale(const float& sx, const float& sy);
    static Mat3 scale(const Vec2& s);

    Mat3 transpose();
    Mat3 inverse();
    float determinant();

	Vec2 Right() const;
	Vec2 Up() const;
	Vec2 Translation() const;

    Vec3 operator*(const Vec3& v) const;
    Mat3 operator*(const Mat3& v) const;
    Mat3 operator*(const float& f) const;
    Mat3 operator/(const float& f) const;
	bool operator==(const Mat3& m) const;
	bool operator!=(const Mat3& m) const;

    static const Mat3 identity;
    static const Mat3 zero;
};

//  Mat4

class Mat4 {
public:
	union {
		struct {
#if defined(ROW_MAJOR)
			float d00, d01, d02, d03;
			float d10, d11, d12, d13;
			float d20, d21, d22, d23;
			float d30, d31, d32, d33;
#elif defined(COLUMN_MAJOR)
			float d00, d10, d20, d30;
			float d01, d11, d21, d31;
			float d02, d12, d22, d32;
			float d03, d13, d23, d33;
#endif // defined(COLUMN_MAJOR)
		};
		float data[16];
	};

    Mat4(void);
    Mat4(const float& m00, const float& m01, const float& m02, const float& m03,
         const float& m10, const float& m11, const float& m12, const float& m13,
         const float& m20, const float& m21, const float& m22, const float& m23,
         const float& m30, const float& m31, const float& m32, const float& m33);

    static Mat4 translate(const float& tx, const float& ty, const float& tz);
    static Mat4 translate(const Vec3& v);
    static Mat4 rotate(const float& rx, const float& ry, const float& rz, const float& rw);
    static Mat4 rotate(const Quat& q);
    static Mat4 scale(const float& sx, const float& sy, const float& sz);
    static Mat4 scale(const Vec3& s);

    Mat4 transpose();
    Mat4 inverse();
    float determinant();

	Vec3 Right() const;
	Vec3 Up() const;
	Vec3 Forward() const;
	Vec3 Translation() const;

    Vec4 operator*(const Vec4& v) const;
    Mat4 operator*(const Mat4& m) const;
    Mat4 operator*(const float& f) const;
    Mat4 operator/(const float& f) const;
    bool operator==(const Mat4& m) const;
    bool operator!=(const Mat4& m) const;

    static const Mat4 identity;
    static const Mat4 zero;
};

#endif /* defined(__Camaleao__Matrix__) */
