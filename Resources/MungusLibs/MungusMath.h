#pragma once
#ifndef MUNGUS_MATH
#define MUNGUS_MATH

#define _USE_MATH_DEFINES
#include <math.h>

namespace MungusMath {

	inline float abs(float number) {
		return number < 0 ? -number : number;
	}

	inline float degToRads(float degrees) {
		return degrees * (float)(3.1415926535908032384626433 / 180.0);
	}

	inline float radsToDeg(float rad) {
		return rad * (float)(180.0 / 3.1415926535897932384626433);
	}

	struct MVec3 {
		float x;
		float y;
		float z;

		MVec3() {}
		MVec3(float x, float y, float z) : x(x), y(y), z(z) {}

		friend inline std::ostream & operator<<(std::ostream& stream, const MVec3& vec) {
			stream << "x: " << vec.x << " y: " << vec.y << " z: " << vec.z << "\n";
			return stream;
		}

		inline float size(void) const {
			return sqrtf(x * x + y * y + z * z);
		}

		inline MVec3 operator+(const MVec3& other) const {
			return MVec3{ x + other.x, y + other.y, z + other.z };
		}

		inline MVec3 operator+(const MVec3& other) {
			return MVec3{ x + other.x, y + other.y, z + other.z };
		}

		inline MVec3 operator-(const MVec3& other) const {
			return MVec3{ x - other.x, y - other.y, z - other.z };
		}

		inline MVec3 operator-(const MVec3& other) {
			return MVec3{ x - other.x, y - other.y, z - other.z };
		}

		inline MVec3 operator*(const MVec3& other) const {
			return MVec3{x * other.x, y * other.y, z * other.z};
		}

		inline MVec3 operator*(const float other) const {
			return MVec3{x * other, y * other, z * other};
		}

		inline float dot(const MVec3& other) const {
			return x * other.x + y * other.y + z * other.z;
		}

		inline MVec3 cross(const MVec3& other) const {
			return MVec3{
				(y * other.z - z * other.y),
				(z * other.x - x * other.z),
				(x * other.y - y * other.x)
			};
		}

		inline MVec3 projectOnto(const MVec3& projection) {
			return projection * (this->dot(projection) / projection.dot(projection));
		}

		inline static MVec3 normalize(const MVec3& vector) {
			float size = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

			return MVec3{
				vector.x / size, vector.y / size, vector.z / size
			};
		}
	};

	struct MVec4 {
		float x;
		float y;
		float z;
		float w;

		inline float operator[](int index) {
			return ((float*)this)[index];
		}
	};

	struct MMat3 {
		float data[3][3];

		MMat3(void) {
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					data[i][j] = 0;
		}

		MMat3(const MVec3& row1, const MVec3& row2, const MVec3& row3) : data{row1.x, row1.y, row1.z, row2.x, row2.y, row2.z, row3.x, row3.y, row3.z} {}

		inline const float* operator[](int index) const {
			return data[index];
		}

		inline float* operator[](int index) {
			return data[index];
		}
	};

	struct MMat4 {
		float data[4][4];

		inline const float* operator[](int index) const {
			return data[index];
		}

		inline float* operator[](int index) {
			return data[index];
		}

		inline MMat4 operator*(const MMat4& other) const {
			MMat4 returnVal;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					returnVal.data[i][j] = 0;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						returnVal.data[i][j] += data[i][k] * other.data[k][j];
					}
				}
			}

			return returnVal;
		}

		inline MVec4 operator*(const MVec4& other) const {
			float newData[4]{0, 0, 0, 0};
			float* otherData = (float*)&other;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					newData[i] += data[i][j] * otherData[j];
				}
			}

			return MVec4{newData[0], newData[1], newData[2], newData[3]};
		}

		inline MMat4 operator*(float times) const {
			MMat4 newMat;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					newMat.data[i][j] = data[i][j] * times;

			return newMat;
		}

		inline MMat4 operator+(const MMat4& other) const {
			MMat4 newMat;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					newMat.data[i][j] = data[i][j] + other.data[i][j];

			return newMat;
		}

		inline MMat4 operator-(const MMat4& other) {
			MMat4 newMat;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					newMat.data[i][j] = data[i][j] - other.data[i][j];

			return newMat;
		}

		inline static MMat4 identity() {
			return MMat4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
		}

		inline static MMat4 rotation(float x, float y, float z, float theta) {
			float dirMag = sqrtf((x * x) + (y * y) + (z * z));
			x /= dirMag;
			y /= dirMag;
			z /= dirMag;

			float rTheta =  (float)(M_PI / 180.0f) * theta;
			float sinTheta = sinf(rTheta);
			float cosTheta = cosf(rTheta);
			float cosThetaFromOne = 1.0f - cosTheta;

			return MMat4{
				cosTheta + (x * x * cosThetaFromOne),	(x * y * cosThetaFromOne) - (z * sinTheta),	(x * z * cosThetaFromOne) + (y * sinTheta),	0,
				(y * x * cosThetaFromOne) + (z * sinTheta),	cosTheta + (y * y * cosThetaFromOne),	(y * z * cosThetaFromOne) - (x * sinTheta),	0,
				(z * x * cosThetaFromOne) - (y * sinTheta),	(z * y * cosThetaFromOne) + (x * sinTheta),	cosTheta + (z * z * cosThetaFromOne),	0,
				0, 0, 0, 1
			};
		}

		inline static MMat4 scale(float x, float y, float z) {
			return MMat4{
				x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1
			};
		}

		inline static MMat4 translate(float x, float y, float z) {
			return MMat4{
				1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1
			};
		}

	};

	struct Line {
		MungusMath::MVec3 position;
		MungusMath::MVec3 direction;
	};

	struct Triangle {
		MVec3 point1;
		MVec3 point2;
		MVec3 point3;

		float area(void) const {
			MVec3 V = point2 - point1;
			MVec3 normalV = MVec3::normalize(V);
			MVec3 U = point3 - point1;
			MVec3 W = point3 - (point1 + (normalV * (normalV.dot(U))));

			return abs((V.size() / 2.0) * W.size());
		}
	};

	inline MMat4 lookatMatrix(const MVec3& position, const MVec3& direction, const MVec3& trueUp) {
		MVec3 forward = MVec3::normalize(direction);
		MVec3 right = MVec3::normalize(trueUp.cross(forward));
		MVec3 up = MVec3::normalize(right.cross(forward));

		return MMat4{
			right.x, right.y, right.z, 0,
			up.x, up.y, up.z, 0,
			forward.x, forward.y, forward.z, 0,
			position.x, position.y, position.z, 1
		} *
		MMat4{
			1, 0, 0, -(position.x),
			0, 1, 0, -(position.y),
			0, 0, 1, -(position.z),
			0, 0, 0, 1
		};
	}

	inline float determinant(const MMat3& matrix) {
		float determinant = 0;
		
		for (int i = 0; i < 3; i++) {
			determinant += (matrix[0][i] * ((matrix[1][(i + 1) % 3] * matrix[2][(i + 2) % 3]) - (matrix[1][(i + 2) % 3] * matrix[2][(i + 1) % 3])));
		}

		return determinant;
	}

	inline MMat3 inverseMatrix(const MMat3& matrix) {
		MMat3 inverseMatrix;
		float det = determinant(matrix);

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				inverseMatrix[i][j] = ((matrix[(j + 1) % 3][(i + 1) % 3] * matrix[(j + 2) % 3][(i + 2) % 3])
									 - (matrix[(j + 1) % 3][(i + 2) % 3] * matrix[(j + 2) % 3][(i + 1) % 3])) / det;

		return inverseMatrix;
	}

	inline MMat4 inverseMatrix(const MMat4& matrix) {
		MMat4 inverseMatrix;
		float* m = (float*)&matrix;
		float* inv = (float*)&inverseMatrix;
		float det;
		int i;

		inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det != 0)
			det = 1.0f / det;


		for (i = 0; i < 16; i++)
			inv[i] = inv[i] * det;

		return inverseMatrix;
	}

	inline MMat4 transposeMatrix(const MMat4& matrix) {
		MMat4 transposed;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				transposed[i][j] = matrix[j][i];

		return transposed;
	}

	inline MVec3 rotateAboutAxis(const MVec3& vec, const MVec3& axis, float angle) {
		MVec4 rotated = MMat4::rotation(axis.x, axis.y, axis.z, angle) * MVec4 {vec.x, vec.y, vec.z, 1};
		return MVec3{ rotated.x, rotated.y, rotated.z };
	}

	inline float pointDistance(const MVec3& point1, const MVec3& point2) {
		return abs((point1 - point2).size());
	}

	inline MVec3 normalFromPoints(const MVec3& point1, const MVec3& point2, const MVec3& point3) {
		return MVec3::normalize((point2 - point1).cross(point3 - point1));
	}

	inline bool intersectLineTriangle(const Triangle& triangle, const Line& line) {
		MVec3 tPointA = triangle.point1;
		MVec3 tPointB = triangle.point2;
		MVec3 tPointC = triangle.point3;
		MVec3 lineStart = line.position;
		MVec3 lineDirection = line.direction;
		MVec3 triangleNormal = (tPointB - tPointA).cross(tPointC - tPointA);

		float tCoeff = lineDirection.dot(triangleNormal);

		if (tCoeff == 0.0) {
			// line is parralel to triangle
			return false;
		}

		float constantCoeff = lineStart.dot(triangleNormal);
		float planeEqtnRHS = (triangleNormal.x * tPointA.x) + (triangleNormal.y * tPointA.y) + (triangleNormal.z * tPointA.z) - constantCoeff;
		float lineForwardsToCoplanar = planeEqtnRHS / tCoeff;

		if (lineForwardsToCoplanar < 0.0) {
			// triangle is behind the line starting point
			return false;
		}

		MVec3 coplanarPoint = lineStart + (lineDirection * lineForwardsToCoplanar);

		return Triangle{ tPointA, tPointB, coplanarPoint }.area()
			 + Triangle{ coplanarPoint, tPointB, tPointC }.area()
			 + Triangle{ tPointA, coplanarPoint, tPointC }.area()
			 < Triangle{ tPointA, tPointB, tPointC }.area() * 1.01;
	}

}

#endif // MUNGUS_MATH
