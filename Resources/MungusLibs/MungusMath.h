#pragma once
#ifndef MUNGUS_MATH
#define MUNGUS_MATH

#define _USE_MATH_DEFINES
#include <math.h>

namespace MungusMath {

	struct MVec4 {
		float x;
		float y;
		float z;
		float w;

		inline float operator[](int index) {
			return ((float*)this)[index];
		}
	};

	struct MVec3 {
		float x;
		float y;
		float z;
	};

	struct MMat4 {
		float data[4][4];

		inline float* operator[](int index) {
			return data[index];
		}

		inline MMat4 operator*(MMat4 other) {
			MMat4 returnVal;

			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
					returnVal[i][j] = 0;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {
						returnVal[i][j] += data[i][k] * other[k][j];
					}
				}
			}

			return returnVal;
		}

		inline MMat4 identity() {
			return MMat4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
		}

		inline MMat4 rotation(float x, float y, float z, float theta) {
			float rTheta =  (M_PI / 180.0f) * theta;
			float sinTheta = sin(rTheta);
			float cosTheta = cos(rTheta);
			float cosThetaFromOne = 1 - cosTheta;

			return MMat4{
				cosTheta + (x * x * cosThetaFromOne),	(x * y * cosThetaFromOne) - z * sinTheta,	(x * z * cosThetaFromOne) + (y * sinTheta),	0,
				(y * x * cosThetaFromOne) + (z * sinTheta),	cosTheta + (y * y * cosThetaFromOne),	(y * z * cosThetaFromOne) - (x * sinTheta),	0,
				(z * x * cosThetaFromOne) - (y * sinTheta),	(z * y * cosThetaFromOne) + (x * sinTheta),	cosTheta + (z * z * cosThetaFromOne),	0,
				0, 0, 0, 1
			};
		}

		inline MMat4 scale(float x, float y, float z) {
			return MMat4{
				x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1
			};
		}

		inline MMat4 translate(float x, float y, float z) {
			return MMat4{
				1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1
			};
		}



	};

}

#endif // MUNGUS_MATH