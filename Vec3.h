#pragma once

#include <cmath>
const double PI = 3.14159265358979323846;
template<typename T>
class Vec3
{
public:
	Vec3() : x(T(0)), y(T(0)), z(T(0)) {};
	Vec3(const T& xx) : x(xx), y(xx), z(xx) {};
	Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {};
	
	Vec3<T> operator+(const Vec3<T>& other) const {
		return Vec3<T>(x + other.x, y + other.y, z + other.z);
	}

	Vec3<T> operator-(const Vec3<T>& other) const {
		return Vec3<T>(x - other.x, y - other.y, z - other.z);
	}


	Vec3<T> operator*(T factor) const {
		return Vec3<T>(x * factor, y * factor, z * factor);
	}

	Vec3<T> operator/(T factor) const {
		return Vec3<T>(x / factor, y / factor, z / factor);
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec3& v)
	{
		return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	}

	Vec3<T> cross(const Vec3<T>& other) const {
		return Vec3<T>(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
	}

	// Calculates two vectors dot product
	T dot(const Vec3<T>& other) const{
		return x * other.x + y * other.y + z * other.z;
	}

	// Calculate vectors magnitude
	T magnitude() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	// converts the vector into a unit vector, i.e. a vector of length 1.
	Vec3<T> normalize() const 
	{
		T len = magnitude();
		if(len > T(0))
		{
			T invLength = T(1) / len;
			return Vec3<T>(x * invLength, y * invLength, z * invLength);
		}
		throw std::runtime_error("Length is zero cannot normalize.");
	}
	// Calculates the angle between two vectors in radians and converts it to degrees.
	static T angle(const Vec3<T>& v1, const Vec3<T> v2)
	{
		T dotProduct = v1.dot(v2);
		T lengths = v1.magnitude() * v2.magnitude();

		if(lengths > 0){
			T cosAngle = dotProduct / lengths;
			return std::acos(cosAngle) * (180 / PI);
		}
		throw std::runtime_error("One of the vectors has zero length");
	}

	// Calculates the vector resulting from the refraction of a ray hitting a surface, the eta refractive index should be (n2 / n1).
	static Vec3<T> refract(const Vec3<T>& incident, const Vec3<T>& normal, T eta) {
		T k = T(1) - eta * eta * (T(1) - std::pow(incident.dot(normal), 2));

		if (k < T(0)) {
			return Vec3<T>(); // Total internal reflection
		}
		else {
			return eta * incident - (eta * incident.dot(normal) + std::sqrt(k)) * normal;
		}
	}

	// Calculates the vector resulting from the reflection of a ray hitting a surface.
	static Vec3<T> reflect(const Vec3<T>& incident, const Vec3<T>& normal) {
		// I - 2.0 * N * dot(N, I)
		return incident - normal * (T(2) * incident.dot(normal));
	}


	Vec3<T> project2D(int width, int height, T fov, T viewer_distance) const {
		T factor = fov / (viewer_distance + z);
		T x2d = x * factor + width / 2.0;
		T y2d = -y * factor + height / 2.0;
		return Vec3<T>(x2d, y2d, z);
	}


	T x, y, z;
};
