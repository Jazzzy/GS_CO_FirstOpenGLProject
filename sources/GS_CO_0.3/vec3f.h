#pragma once

#ifndef VEC3F_H_INCLUDED
#define VEC3F_H_INCLUDED

#include <iostream>
#include <math.h>

class Vec3f {
public:
	float v[3];
	Vec3f();
	Vec3f(float x, float y, float z);

	float &operator[](int index);
	float operator[](int index) const;

	Vec3f operator*(float scale) const;
	Vec3f operator/(float scale) const;
	Vec3f operator+(const Vec3f &other) const;
	Vec3f operator-(const Vec3f &other) const;
	Vec3f operator-() const;

	const Vec3f &operator*=(float scale);
	const Vec3f &operator/=(float scale);
	const Vec3f &operator+=(const Vec3f &other);
	const Vec3f &operator-=(const Vec3f &other);

	float magnitude() const;
	float magnitudeSquared() const;
	float Vec3f::distanceToPoint(const Vec3f &origin, const Vec3f &externalPoint) const;
	Vec3f normalize() const;
	float dot(const Vec3f &other) const;
	Vec3f cross(const Vec3f &other) const;
	Vec3f sub(Vec3f v, float scale);
	void Vec3f::print() const;
};

Vec3f operator*(float scale, const Vec3f &v);
std::ostream &operator<<(std::ostream &output, const Vec3f &v);










#endif
