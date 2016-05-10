/**
 *
 * @brief G&T Math Namespace
 * @author Toni Marquez
 *
 **/

#include "gtmath.h"

namespace gtmath {

	float Rad2Deg(const float rad){

		return rad * 180 / kPid;
	}

	float Deg2Rad(const float deg){

		return deg * kPid / 180;
	}

	/* ------------------------------ METHODS 2D ----------------------------- */

  /***************************************************************************
  *                                    VEC3                                  *
  ****************************************************************************/

	float DotProductVec3(const Vec3 v1, const Vec3 v2) {

		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	float MagnitudeVec3(const Vec3 v) {

		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	float AngleBetweenVec3(const Vec3 v1, const Vec3 v2) {

		return acos(DotProductVec3(v1, v2) /
								(MagnitudeVec3(v1) * MagnitudeVec3(v2)));
	}

  Vec3 Angle2Vector(const float rad) {

    Vec3 vec;

    vec.x = cos(rad);
    vec.y = sin(rad);

    return vec;
  }

  float Vector2Angle(const Vec3 v) {

    return atan2(v.y, v.x);
  }

	Vec3 CreateVec3(const float x, const float y, const float z) {
		Vec3 vec;

		vec.x = x;
		vec.y = y;
		vec.z = z;

		return vec;
	}

  Vec3 Vec3Zero() {

    return CreateVec3(0.0f, 0.0f, 0.0f);
  }

	Vec3 Vec3Up() {

    return CreateVec3(0.0f, 1.0f, 0.0f);
  }

	Vec3 Vec3Right() {

    return CreateVec3(1.0f, 0.0f, 0.0f);
  }

	Vec3 AddVec3(const Vec3 v1, const Vec3 v2) {
		Vec3 vec;

		vec.x = v1.x + v2.x;
		vec.y = v1.y + v2.y;
		vec.z = v1.z + v2.z;

		return vec;
	}

	Vec3 SubstractVec3(const Vec3 v1, const Vec3 v2) {
		Vec3 vec;

		vec.x = v1.x - v2.x;
		vec.y = v1.y - v2.y;
		vec.z = v1.z - v2.z;

		return vec;
	}

	Vec3 HomogenizeVec3(Vec3 v) {

		v.x /= v.z;
		v.y /= v.z;
		v.z /= v.z;

		return v;
	}

	Vec3 MidPointVec3(const Vec3 v1, const Vec3 v2) {
		Vec3 vec;

		vec = AddVec3(v1, v2);
		vec = HomogenizeVec3(vec);

		return vec;
	}

	Vec3 NormalizeVec3(Vec3 v) {
		float mod = MagnitudeVec3(v);

		v.x /= mod;
		v.y /= mod;

		return v;
	}

	Vec3 ScaleVec3(Vec3 v, float scalex, float scaley) {

		v.x *= scalex;
		v.y *= scaley;

		return v;
	}

	Vec3 PerpendicularVec3(Vec3 v, Axis axis) {

		switch (axis){
			case kAxis_X: { v.x *= -1; } break;
			case kAxis_Y: { v.y *= -1; } break;
		}

		return v;
	}

	Vec3 OppositeVec3(Vec3 v) {

		v.x *= -1;
		v.y *= -1;

		return v;
	}

  //-------------------------------------------------------------------------//
  //                                OPERATORS                                //
  //-------------------------------------------------------------------------//

  Vec3 operator+(const Vec3 v1, const Vec3 v2) {

    return AddVec3(v1, v2);
  }

  Vec3 operator-(const Vec3 v1, const Vec3 v2) {

    return SubstractVec3(v1, v2);
  }

	Vec3 operator*(const Vec3 v, const float scale) {

		return ScaleVec3(v, scale, scale);
	}

	Vec3 operator-(Vec3& v) {

		v.x *= -1.0f;
		v.y *= -1.0f;
		v.z *= -1.0f;

		return v;
	}

  void operator+=(Vec3& v1, const Vec3 v2) {

    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
  }

  void operator-=(Vec3& v1, const Vec3 v2) {

    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
  }

  bool operator==(const Vec3 v1, const Vec3 v2) {

    if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z){ return true; }
    else { return false; }
  }

  //-------------------------------------------------------------------------//
  //                                  DEBUG                                  //
  //-------------------------------------------------------------------------//

  void PrintVec3(Vec3 v) {

    printf("%f, %f, %f\n", v.x, v.y, v.z);
  }

  /***************************************************************************
  *                                    MAT3                                  *
  ****************************************************************************/

	Mat3 CreateMat3(const Vec3 v1, const Vec3 v2, const Vec3 v3) {
		Mat3 mat;

		mat.mat3[0] = v1.x; mat.mat3[1] = v2.x; mat.mat3[2] = v3.x;
		mat.mat3[3] = v1.y; mat.mat3[4] = v2.y; mat.mat3[5] = v3.y;
		mat.mat3[6] = v1.z; mat.mat3[7] = v2.z; mat.mat3[8] = v3.z;

		return mat;
	}

  Mat3 Mat3Zero() {

    return CreateMat3(Vec3Zero(), Vec3Zero(), Vec3Zero());
  }

	Mat3 IdentityMat3() {
		Mat3 mat;

		mat.mat3[0] = 1; mat.mat3[1] = 0; mat.mat3[2] = 0;
		mat.mat3[3] = 0; mat.mat3[4] = 1; mat.mat3[5] = 0;
		mat.mat3[6] = 0; mat.mat3[7] = 0; mat.mat3[8] = 1;

		return mat;
	}

	Mat3 MultiMat3XMat3(const Mat3 m1, const Mat3 m2) {
		Mat3 mat;

		mat.mat3[0] = m2.mat3[0] * m1.mat3[0] + m2.mat3[1] * m1.mat3[3] + m2.mat3[2] * m1.mat3[6];
		mat.mat3[1] = m2.mat3[0] * m1.mat3[1] + m2.mat3[1] * m1.mat3[4] + m2.mat3[2] * m1.mat3[7];
		mat.mat3[2] = m2.mat3[0] * m1.mat3[2] + m2.mat3[1] * m1.mat3[5] + m2.mat3[2] * m1.mat3[8];

		mat.mat3[3] = m2.mat3[3] * m1.mat3[0] + m2.mat3[4] * m1.mat3[3] + m2.mat3[5] * m1.mat3[6];
		mat.mat3[4] = m2.mat3[3] * m1.mat3[1] + m2.mat3[4] * m1.mat3[4] + m2.mat3[5] * m1.mat3[7];
		mat.mat3[5] = m2.mat3[3] * m1.mat3[2] + m2.mat3[4] * m1.mat3[5] + m2.mat3[5] * m1.mat3[8];

		mat.mat3[6] = m2.mat3[6] * m1.mat3[0] + m2.mat3[7] * m1.mat3[3] + m2.mat3[8] * m1.mat3[6];
		mat.mat3[7] = m2.mat3[6] * m1.mat3[1] + m2.mat3[7] * m1.mat3[4] + m2.mat3[8] * m1.mat3[7];
		mat.mat3[8] = m2.mat3[6] * m1.mat3[2] + m2.mat3[7] * m1.mat3[5] + m2.mat3[8] * m1.mat3[8];

		return mat;
	}

	Vec3 MultiMat3XVec3(const Mat3 m, const Vec3 v) {
		Vec3 vec;

		vec.x = m.mat3[0] * v.x + m.mat3[1] * v.y + m.mat3[2] * v.z;
		vec.y = m.mat3[3] * v.x + m.mat3[4] * v.y + m.mat3[5] * v.z;
		vec.z = m.mat3[6] * v.x + m.mat3[7] * v.y + m.mat3[8] * v.z;

		return vec;
	}

	Mat3 TranslateMat3(float tx, float ty) {
		Mat3 mat;

		mat.mat3[0] = 1; mat.mat3[1] = 0; mat.mat3[2] = tx;
		mat.mat3[3] = 0; mat.mat3[4] = 1; mat.mat3[5] = ty;
		mat.mat3[6] = 0; mat.mat3[7] = 0; mat.mat3[8] = 1;

		return mat;
	}

	Mat3 ScaleMat3(float sx, float sy) {
		Mat3 mat;

		mat.mat3[0] = sx; mat.mat3[1] = 0;  mat.mat3[2] = 0;
		mat.mat3[3] = 0;  mat.mat3[4] = sy; mat.mat3[5] = 0;
		mat.mat3[6] = 0;  mat.mat3[7] = 0;  mat.mat3[8] = 1;

		return mat;
	}

	Mat3 RotateMat3(float rad) {
		Mat3 mat;

		mat.mat3[0] = cos(rad); mat.mat3[1] = -sin(rad); mat.mat3[2] = 0;
		mat.mat3[3] = sin(rad); mat.mat3[4] = cos(rad);  mat.mat3[5] = 0;
		mat.mat3[6] = 0;        mat.mat3[7] = 0;         mat.mat3[8] = 1;

		return mat;
	}

  void PrintMat3(Mat3 m) {

    printf("%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n",
           m.mat3[0], m.mat3[1], m.mat3[2],
           m.mat3[3], m.mat3[4], m.mat3[5],
           m.mat3[6], m.mat3[7], m.mat3[8]);
  }

	/* ------------------------------ METHODS 3D ----------------------------- */

  /***************************************************************************
  *                                    VEC4                                  *
  ****************************************************************************/

	float DotProductVec4(const Vec4 v1, const Vec4 v2) {

		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	float MagnitudeVec4(const Vec4 v) {

		return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	}

	float AngleBetweenVec4(const Vec4 v1, const Vec4 v2) {

		return acos(DotProductVec4(v1, v2) / (MagnitudeVec4(v1) * MagnitudeVec4(v2)));
	}

	Vec4 CreateVec4(const float x, const float y, const float z, const float w) {
		Vec4 vec;

		vec.x = x;
		vec.y = y;
		vec.z = z;
		vec.w = w;

		return vec;
	}

  Vec4 Vec4Zero() {

    return CreateVec4(0.0f, 0.0f, 0.0f, 0.0f);
  }

	Vec4 Vec4Forward() {

    return CreateVec4(0.0f, 0.0f, 1.0f, 0.0f);
  }

	Vec4 Vec4Up() {

    return CreateVec4(0.0f, 1.0f, 0.0f, 0.0f);
  }

	Vec4 Vec4Right() {

    return CreateVec4(1.0f, 0.0f, 0.0f, 0.0f);
  }

	Vec4 AddVec4(const Vec4 v1, const Vec4 v2) {
		Vec4 vec;

		vec.x = v1.x + v2.x;
		vec.y = v1.y + v2.y;
		vec.z = v1.z + v2.z;
		vec.w = v1.w + v2.w;

		return vec;
	}

	Vec4 SubstractVec4(const Vec4 v1, const Vec4 v2) {
		Vec4 vec;

		vec.x = v1.x - v2.x;
		vec.y = v1.y - v2.y;
		vec.z = v1.z - v2.z;
		vec.w = v1.w - v2.w;

		return vec;
	}

	Vec4 HomogenizeVec4(Vec4 v) {

		v.x /= v.z;
		v.y /= v.z;
		v.z /= v.z;
		v.w /= v.w;

		return v;
	}

	Vec4 MidPointVec4(const Vec4 v1, const Vec4 v2) {
		Vec4 vec;

		vec = AddVec4(v1, v2);
		vec = HomogenizeVec4(vec);

		return vec;
	}

	Vec4 NormalizeVec4(Vec4 v) {
		float mod = MagnitudeVec4(v);

		v.x /= mod;
		v.y /= mod;
		v.z /= mod;

		return v;
	}

	Vec4 ScaleVec4(Vec4 v, float scalex, float scaley, float scalez) {

		v.x *= scalex;
		v.y *= scaley;
		v.z *= scalez;

		return v;
	}

	Vec4 OppositeVec4(Vec4 v) {

		v.x *= -1;
		v.y *= -1;
		v.z *= -1;

		return v;
	}

  //-------------------------------------------------------------------------//
  //                                OPERATORS                                //
  //-------------------------------------------------------------------------//

  Vec4 operator+(const Vec4 v1, const Vec4 v2) {

    return AddVec4(v1, v2);
  }

  Vec4 operator-(const Vec4 v1, const Vec4 v2) {

    return SubstractVec4(v1, v2);
  }

	Vec4 operator*(const Vec4 v, const float scale) {

		return ScaleVec4(v, scale, scale, scale);
	}

  void operator+=(Vec4& v1, const Vec4 v2) {

    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    v1.w += v2.w;
  }

  void operator-=(Vec4& v1, const Vec4 v2) {

    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    v1.w -= v2.w;
  }

  bool operator==(const Vec4 v1, const Vec4 v2) {

    if (v1.x == v2.x &&
        v1.y == v2.y &&
        v1.z == v2.z &&
        v1.w == v2.w){

      return true;
    }
    else { return false; }
  }

  //-------------------------------------------------------------------------//
  //                                  DEBUG                                  //
  //-------------------------------------------------------------------------//

  void PrintVec4(Vec4 v) {

    printf("%f, %f, %f, %f\n", v.x, v.y, v.z, v.w);
  }

  /***************************************************************************
  *                                    MAT4                                  *
  ****************************************************************************/

	Mat4 CreateMat4(const Vec4 v1, const Vec4 v2, const Vec4 v3, const Vec4 v4) {
		Mat4 mat;

		mat.mat4[0]  = v1.x; mat.mat4[1]  = v2.x; mat.mat4[2]  = v3.x; mat.mat4[3]  = v4.x;
		mat.mat4[4]  = v1.y; mat.mat4[5]  = v2.y; mat.mat4[6]  = v3.y; mat.mat4[7]  = v4.y;
		mat.mat4[8]  = v1.z; mat.mat4[9]  = v2.z; mat.mat4[10] = v3.z; mat.mat4[11] = v4.z;
		mat.mat4[12] = v1.w; mat.mat4[13] = v2.w; mat.mat4[14] = v3.w; mat.mat4[15] = v4.w;

		return mat;
	}

  Mat4 Mat4Zero() {

    return CreateMat4(Vec4Zero(), Vec4Zero(), Vec4Zero(), Vec4Zero());
  }

	Mat4 IdentityMat4() {
		Mat4 mat;

		mat.mat4[0]  = 1; mat.mat4[1]  = 0; mat.mat4[2]  = 0; mat.mat4[3]  = 0;
		mat.mat4[4]  = 0; mat.mat4[5]  = 1; mat.mat4[6]  = 0; mat.mat4[7]  = 0;
		mat.mat4[8]  = 0; mat.mat4[9]  = 0; mat.mat4[10] = 1; mat.mat4[11] = 0;
		mat.mat4[12] = 0; mat.mat4[13] = 0; mat.mat4[14] = 0; mat.mat4[15] = 1;

		return mat;
	}

	Mat4 MultiMat4XMat4(const Mat4 m1, const Mat4 m2) {
		Mat4 mat;

		mat.mat4[0]  = m2.mat4[0] * m1.mat4[0] + m2.mat4[1] * m1.mat4[4] + m2.mat4[2] * m1.mat4[8]  + m2.mat4[3] * m1.mat4[12];
		mat.mat4[1]  = m2.mat4[0] * m1.mat4[1] + m2.mat4[1] * m1.mat4[5] + m2.mat4[2] * m1.mat4[9]  + m2.mat4[3] * m1.mat4[13];
		mat.mat4[2]  = m2.mat4[0] * m1.mat4[2] + m2.mat4[1] * m1.mat4[6] + m2.mat4[2] * m1.mat4[10] + m2.mat4[3] * m1.mat4[14];
		mat.mat4[3]  = m2.mat4[0] * m1.mat4[3] + m2.mat4[1] * m1.mat4[7] + m2.mat4[2] * m1.mat4[11] + m2.mat4[3] * m1.mat4[15];

		mat.mat4[4]  = m2.mat4[4] * m1.mat4[0] + m2.mat4[5] * m1.mat4[4] + m2.mat4[6] * m1.mat4[8]  + m2.mat4[7] * m1.mat4[12];
		mat.mat4[5]  = m2.mat4[4] * m1.mat4[1] + m2.mat4[5] * m1.mat4[5] + m2.mat4[6] * m1.mat4[9]  + m2.mat4[7] * m1.mat4[13];
		mat.mat4[6]  = m2.mat4[4] * m1.mat4[2] + m2.mat4[5] * m1.mat4[6] + m2.mat4[6] * m1.mat4[10] + m2.mat4[7] * m1.mat4[14];
		mat.mat4[7]  = m2.mat4[4] * m1.mat4[3] + m2.mat4[5] * m1.mat4[7] + m2.mat4[6] * m1.mat4[11] + m2.mat4[7] * m1.mat4[15];

		mat.mat4[8]  = m2.mat4[8] * m1.mat4[0] + m2.mat4[9] * m1.mat4[4] + m2.mat4[10] * m1.mat4[8]  + m2.mat4[11] * m1.mat4[12];
		mat.mat4[9]  = m2.mat4[8] * m1.mat4[1] + m2.mat4[9] * m1.mat4[5] + m2.mat4[10] * m1.mat4[9]  + m2.mat4[11] * m1.mat4[13];
		mat.mat4[10] = m2.mat4[8] * m1.mat4[2] + m2.mat4[9] * m1.mat4[6] + m2.mat4[10] * m1.mat4[10] + m2.mat4[11] * m1.mat4[14];
		mat.mat4[11] = m2.mat4[8] * m1.mat4[3] + m2.mat4[9] * m1.mat4[7] + m2.mat4[10] * m1.mat4[11] + m2.mat4[11] * m1.mat4[15];

		mat.mat4[12] = m2.mat4[12] * m1.mat4[0] + m2.mat4[13] * m1.mat4[4] + m2.mat4[14] * m1.mat4[8]  + m2.mat4[15] * m1.mat4[12];
		mat.mat4[13] = m2.mat4[12] * m1.mat4[1] + m2.mat4[13] * m1.mat4[5] + m2.mat4[14] * m1.mat4[9]  + m2.mat4[15] * m1.mat4[13];
		mat.mat4[14] = m2.mat4[12] * m1.mat4[2] + m2.mat4[13] * m1.mat4[6] + m2.mat4[14] * m1.mat4[10] + m2.mat4[15] * m1.mat4[14];
		mat.mat4[15] = m2.mat4[12] * m1.mat4[3] + m2.mat4[13] * m1.mat4[7] + m2.mat4[14] * m1.mat4[11] + m2.mat4[15] * m1.mat4[15];

		return mat;
	}

	Vec4 MultiMat4XVec4(const Mat4 m, const Vec4 v) {
		Vec4 vec;

		vec.x = m.mat4[0]  * v.x + m.mat4[1]  * v.y + m.mat4[2]  * v.z + m.mat4[3]  * v.w;
		vec.y = m.mat4[4]  * v.x + m.mat4[5]  * v.y + m.mat4[6]  * v.z + m.mat4[7]  * v.w;
		vec.z = m.mat4[8]  * v.x + m.mat4[9]  * v.y + m.mat4[10] * v.z + m.mat4[11] * v.w;
		vec.w = m.mat4[12] * v.x + m.mat4[13] * v.y + m.mat4[14] * v.z + m.mat4[15] * v.w;

		return vec;
	}

	Mat4 TranslateMat4(float tx, float ty, float tz) {
		Mat4 mat;

		mat.mat4[0]  = 1; mat.mat4[1]  = 0; mat.mat4[2]  = 0; mat.mat4[3]  = tx;
		mat.mat4[4]  = 0; mat.mat4[5]  = 1; mat.mat4[6]  = 0; mat.mat4[7]  = ty;
		mat.mat4[8]  = 0; mat.mat4[9]  = 0; mat.mat4[10] = 1; mat.mat4[11] = tz;
		mat.mat4[12] = 0; mat.mat4[13] = 0; mat.mat4[14] = 0; mat.mat4[15] = 1;

		return mat;
	}

	Mat4 ScaleMat4(float sx, float sy, float sz) {
		Mat4 mat;

		mat.mat4[0]  = sx; mat.mat4[1]  = 0;  mat.mat4[2]  = 0;  mat.mat4[3]  = 0;
		mat.mat4[4]  = 0;  mat.mat4[5]  = sy; mat.mat4[6]  = 0;  mat.mat4[7]  = 0;
		mat.mat4[8]  = 0;  mat.mat4[9]  = 0;  mat.mat4[10] = sz; mat.mat4[11] = 0;
		mat.mat4[12] = 0;  mat.mat4[13] = 0;  mat.mat4[14] = 0;  mat.mat4[15] = 1;

		return mat;
	}

	Mat4 RotateMat4X(float rad) {
		Mat4 mat;

		mat.mat4[0]  = 1; mat.mat4[1]  = 0;         mat.mat4[2]  = 0;        mat.mat4[3]  = 0;
		mat.mat4[4]  = 0; mat.mat4[5]  = cos(rad);  mat.mat4[6]  = sin(rad); mat.mat4[7]  = 0;
		mat.mat4[8]  = 0; mat.mat4[9]  = -sin(rad); mat.mat4[10] = cos(rad); mat.mat4[11] = 0;
		mat.mat4[12] = 0; mat.mat4[13] = 0;         mat.mat4[14] = 0;        mat.mat4[15] = 1;

		return mat;
	}

	Mat4 RotateMat4Y(float rad) {
		Mat4 mat;

		mat.mat4[0]  = cos(rad); mat.mat4[1]  = 0; mat.mat4[2]  = -sin(rad); mat.mat4[3]  = 0;
		mat.mat4[4]  = 0;        mat.mat4[5]  = 1; mat.mat4[6]  = 0;         mat.mat4[7]  = 0;
		mat.mat4[8]  = sin(rad); mat.mat4[9]  = 0; mat.mat4[10] = cos(rad);  mat.mat4[11] = 0;
		mat.mat4[12] = 0;        mat.mat4[13] = 0; mat.mat4[14] = 0;         mat.mat4[15] = 1;

		return mat;
	}

	Mat4 RotateMat4Z(float rad) {
		Mat4 mat;

		mat.mat4[0]  = cos(rad);  mat.mat4[1]  = sin(rad); mat.mat4[2]  = 0; mat.mat4[3]  = 0;
		mat.mat4[4]  = -sin(rad); mat.mat4[5]  = cos(rad); mat.mat4[6]  = 0; mat.mat4[7]  = 0;
		mat.mat4[8]  = 0;         mat.mat4[9]  = 0;        mat.mat4[10] = 1; mat.mat4[11] = 0;
		mat.mat4[12] = 0;         mat.mat4[13] = 0;        mat.mat4[14] = 0; mat.mat4[15] = 1;

		return mat;
	}

	Vec4 RotateVec4X(Vec4 v, const float rad) {

		Mat4 transform = IdentityMat4();

		transform = MultiMat4XMat4(RotateMat4X(rad), transform);
		v = MultiMat4XVec4(transform, v);

		return v;
	}

	Vec4 RotateVec4Y(Vec4 v, const float rad) {

		Mat4 transform = IdentityMat4();

		transform = MultiMat4XMat4(RotateMat4Y(rad), transform);
		v = MultiMat4XVec4(transform, v);

		return v;
	}

	Vec4 RotateVec4Z(Vec4 v, const float rad) {

		Mat4 transform = IdentityMat4();

		transform = MultiMat4XMat4(RotateMat4Z(rad), transform);
		v = MultiMat4XVec4(transform, v);

		return v;
	}

	Vec4 RotateVec4XYZ(Vec4 v, Vec3 rot) {

		Mat4 transform = IdentityMat4();

		transform = MultiMat4XMat4(RotateMat4X(rot.x), transform);
		transform = MultiMat4XMat4(RotateMat4Y(rot.y), transform);
		transform = MultiMat4XMat4(RotateMat4Z(rot.z), transform);
		v = MultiMat4XVec4(transform, v);

		return v;
	}

	Mat4 ProjectionMat4() {
		Mat4 mat;

		mat.mat4[0]  = 1; mat.mat4[1]  = 0; mat.mat4[2]  = 0; mat.mat4[3]  = 0;
		mat.mat4[4]  = 0; mat.mat4[5]  = 1; mat.mat4[6]  = 0; mat.mat4[7]  = 0;
		mat.mat4[8]  = 0; mat.mat4[9]  = 0; mat.mat4[10] = 1; mat.mat4[11] = 0;
		mat.mat4[12] = 0; mat.mat4[13] = 0; mat.mat4[14] = 1; mat.mat4[15] = 0;

		return mat;
	}

  void PrintMat4(Mat4 m) {

    printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
           m.mat4[0], m.mat4[1], m.mat4[2],  m.mat4[3],
           m.mat4[4], m.mat4[5], m.mat4[6],  m.mat4[7],
           m.mat4[8], m.mat4[9], m.mat4[10], m.mat4[11]);
  }
}
