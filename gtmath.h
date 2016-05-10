/**
 *
 * @brief G&T Math Header
 * @author Toni Marquez
 * @fixes - use operators,
 *        ? overloaded methods
 *
 **/

#ifndef __GTMATH_H__
#define __GTMATH_H__ 1

#include <stdio.h>
#include <math.h>

const double kPid = 3.141592653589793238626433832795028841971;
const float kPi = 3.14159265f;

namespace gtmath {

  /// Axis enumeration
  enum Axis {
    kAxis_X = 1,
    kAxis_Y,
    kAxis_Z
  };

  /// Point 2D with 2 coords
  struct Point {
  	float x;
  	float y;
  };

  /// Vector 2D with 2 components and 1 homogeneous
  struct Vec3 {
  	float x;
  	float y;
  	float z;
  };

  /// Vector 3D with 3 components and 1 homogeneous
  struct Vec4 {
  	float x;
  	float y;
  	float z;
  	float w;
  };

  /// 3x3 Matrix
  struct Mat3 {
  	float mat3[9];
  };

  /// 4x4 Matrix
  struct Mat4 {
  	float mat4[16];
  };

  /* ------------------------------ METHODS 2D ----------------------------- */

  /***************************************************************************
  *                                    VEC3                                  *
  ****************************************************************************/

  /**
   * @brief radians to degrees
   * @param float rad
   * @return const float
   **/
  float Rad2Deg(const float rad);
  /**
   *  converts radians to degrees
   *
   *   rad * 180
   *  -----------
   *      pi
   *
   **/

  /**
   * @brief degrees to radians
   * @param float deg
   * @return const float
   **/
  float Deg2Rad(const float deg);
  /**
   *  converts degrees to radians
   *
   *   deg * pi
   *  -----------
   *      180
   *
   **/

  /**
   * @brief dot product of 2 vectors (2D)
   * @param const Vec3 v1, const Vec3 v2
   * @return float
   **/
  float DotProductVec3(const Vec3 v1, const Vec3 v2);
  /**
   *  multiply components x and y from one vector to the other:
   *
   *     | 2 | *    | 2 | =    | 4 |
   *  v1 | 2 | * v2 | 2 | = v3 | 4 |
   *     | 0 |      | 0 | =    | 0 |
   *
   *  then adds the components of the resultant vector:
   *
   *  4 + 4 = 8;
   *
   **/

  /**
   * @brief magnitude of a vector (2D)
   * @param const Vec3 v
   * @return Vec3
   **/
  float MagnitudeVec3(const Vec3 v);
  /**
   *  this method calculate the magnitude using pithagoras:
   *    __________
   *  \/ 2^2 + 2^2 = 2.8
   *
   *  the magnitude is the length of a vector
   *
   **/

  /**
   * @brief angle between 2 vectors (2D)
   * @param const Vec3 v1, const Vec3 v2
   * @return float
   **/
  float AngleBetweenVec3(const Vec3 v1, const Vec3 v2);
  /**
   *  this method make uses of 'DotProductVec3()' and 'MagnitudeVec3()'
   *
   *  needs to calculate the dot product to find the angle between
   *  2 vectors and divide this with the multiply of the 2 vectors
   *  magnitudes:
   *
   *                 DotProductVec3(v1, v2)
   *  acos ( --------------------------------------- )
   *          MagnitudeVec3(v1) * MagnitudeVec3(v2)
   *
   **/

  /**
   * @brief converts angle to vector
   * @param const float rad
   * @return Vec3
   **/
  Vec3 Angle2Vector(const float rad);
  /**
   *  this method converts an angle in radians to a vector doing this:
   *
   *  vector.x = cos(radians)
   *  vector.y = sin(radians)
   *
   **/

  /**
  * @brief convert converts vector to angle
  * @param const float rad
  * @return float
  **/
  float Vector2Angle(const Vec3 v);
  /**
  *  this method converts a vector in to an angle in radians:
  *
  *  radians = atan2(vector.y, vector.x)
  *
  **/

  /**
   * @brief creates a vector / point (2D)
   * @param float x, float y, float z
   * @return Vec3
   **/
  Vec3 CreateVec3(const float x, const float y, const float z);
  /**
   *  this is an example of a vector:
   *
   *    | 1 |   |
   *  v | 1 |   |  /
   *    | 0 |   |_______
   *
   *  this is an example of a point:
   *
   *    | 1 |   |
   *  p | 1 |   |  .
   *    | 1 |   |_______
   *
   *  the difference between a point and a vector is that the homogeneous
   *  (z) component is 1 in a point and this is locatable in space and in
   *  a vector the homogeneous component is 0 and this is not locatable
   *  in space
   *
   **/

  /**
  * @brief creates a zero vector / point (2D)
  * @return Vec3
  **/
  Vec3 Vec3Zero();
  /**
  *  this calls 'CreateVec3()' with zeros into 3 parameters and return
  *  return them:
  *
  *    | 0 |
  *  v | 0 |
  *    | 0 |
  *
  **/

  /**
  * @brief creates a vector up (2D)
  * @return Vec3
  **/
  Vec3 Vec3Up();
  /**
  *  this calls 'CreateVec3()' to create a vector up
  *
  *    | 0 |
  *  v | 1 |
  *    | 0 |
  *
  **/

  /**
  * @brief creates a vector right (2D)
  * @return Vec3
  **/
  Vec3 Vec3Right();
  /**
  *  this calls 'CreateVec3()' to create a vector right
  *
  *    | 1 |
  *  v | 0 |
  *    | 0 |
  *
  **/

  /**
   * @brief add 2 vectors / points (2D)
   * @param const Vec3 v1, const Vec3 v2
   * @return Vec3
   **/
  Vec3 AddVec3(const Vec3 v1, const Vec3 v2);
  /**
   *  this is an example of a vectors add:
   *
   *     | 1 | +    | 1 | =    | 2 |    |             |             |   /
   *  v1 | 1 | + v2 | 1 | = v3 | 2 |    |  /      +   |  /      =   |  /
   *     | 0 | +    | 0 | =    | 0 |    |_______      |_______      |_______
   *
   *  if you add 2 vectors you obtain a bigger vector
   *
   *  this is an example of a points add:
   *
   *     | 1 | +    | 2 | =    | 3 |    |             |   .         |
   *  p1 | 1 | + p2 | 2 | = p3 | 3 |    |  .      +   |         =   |  ?
   *     | 1 | +    | 1 | =    | 2 |    |_______      |_______      |_______
   *
   *  if you add 2 points you obtain another point but not homogenized and
   *  can not locate in space. use 'HomogenizeVec3()' to homogenize it
   *
   **/

  /**
   * @brief subtract 2 vectors / points (2D)
   * @param const Vec3 v1, const Vec3 v2
   * @return Vec3
   **/
  Vec3 SubstractVec3(const Vec3 v1, const Vec3 v2);
  /**
   *  this is an example of a vectors subtract:
   *
   *     | 2 | -    | 1 | =    | 1 |    |   /         |             |
   *  v1 | 2 | - v2 | 1 | = v3 | 1 |    |  /      +   |  /      =   |  /
   *     | 0 | -    | 0 | =    | 0 |    |_______      |_______      |_______
   *
   *  if you subtract to vectors you obtain a smaller vector
   *
   *  this is an example of a points subtract:
   *
   *     | 2 | -    | 1 | =    | 1 |    |             |   .         |
   *  p1 | 2 | - p2 | 1 | = p3 | 1 |    |  .      +   |         =   |  /
   *     | 1 | -    | 1 | =    | 0 |    |_______      |_______      |_______
   *
   *  if you subtract 2 points you obtain a vector that its size is the
   *  formed magnitude between the 2 points
   *
   **/

  /**
   * @brief homogenize a point (2D)
   * @param Vec3 v
   * @return Vec3
   **/
  Vec3 HomogenizeVec3(Vec3 v);
  /**
   *  this is a not homogenized point:
   *
   *    | 4 |
   *  p | 4 |
   *    | 2 |
   *
   *  to homogenize a point must divide all its components with the
   *  homogeneous component
   *
   *    | 4 | / 2 = | 2 |   |
   *  p | 4 | / 2 = | 2 |   |   ·
   *    | 2 | / 2 = | 1 |   |_______
   *
   *  the result is a homogenized point that can located in space
   *
   **/

  /**
   * @brief middle point between 2 points (2D)
   * @param const Vec3 v1, const Vec3 v2
   * @return Vec3
   **/
  Vec3 MidPointVec3(const Vec3 v1, const Vec3 v2);
  /**
   *  this method comprises 'AddVec3()' & 'HomogenizeVec3()'
   *
   *  first add 2 points with 'AddVec3()':
   *
   *     | 1 | +    | 3 | =    | 4 |    |             |     .       |
   *  p1 | 1 | + p2 | 3 | = p3 | 4 |    |  .      +   |         =   |  ?
   *     | 1 | +    | 1 | =    | 2 |    |_______      |_______      |_______
   *
   *  then homogenize the result point with 'HomogenizeVec3()':
   *
   *     | 4 | / 2 = | 2 |    |
   *  p3 | 4 | / 2 = | 2 |    |   ·
   *     | 2 | / 2 = | 1 |    |_______
   *
   *  the result is a point in the middle between the added points
   *
   **/

  /**
   * @brief normalize a vector (2D)
   * @param Vec3 v
   * @return Vec3
   **/
  Vec3 NormalizeVec3(Vec3 v);
  /**
   *  this method includes 'MagnitudeVec3()'
   *
   *  this is a not normalized vector (not unit):
   *
   *    | 2 |
   *  v | 2 |
   *    | 0 |
   *
   *  first obtain the magnitude of the vector by doing pithagoras
   *  with 'MagnitudeVec3()':
   *    __________
   *  \/ 2^2 + 2^2 = 2.8
   *
   *  then divide components x and y with the obtained magnitude:
   *
   *    | 2 | / 2.8 = | 0.7 |    |
   *  v | 2 | / 2.8 = | 0.7 |    |   ·
   *    | 0 |       = | 0   |    |_______
   *
   **/

  /**
   * @brief scale a vector (2D)
   * @param Vec3 v, float scalex, float scaley
   * @return Vec3
   **/
  Vec3 ScaleVec3(Vec3 v, float scalex, float scaley);
  /**
   *  this method scales a vector, it means that its length will be
   *  multiplied by a number:
   *
   *    | 1 | * 2 = | 2 |    |              |   /
   *  v | 1 | * 2 = | 2 |    |  /      ->   |  /
   *    | 0 |     = | 0 |    |_______       |_______
   *
   **/

  /**
   * @brief perpendicular of a vector (2D)
   * @param Vec3 v, Axis axis
   * @return Vec3
   **/
  Vec3 PerpendicularVec3(Vec3 v, Axis axis);
  /**
   *  this method finds the perpendicular of a vector by turning to
   *  negative one of its components:
   *
   *    | 1 | * -1 = | -1 |    |              |
   *  v | 1 |        | 1  |    |  /      ->   |  \
   *    | 0 |        | 0  |    |_______       |_______
   *
   *  can choose the axis by enum 'Axis'
   *
   **/

  /**
   * @brief opposite of a vector (2D)
   * @param Vec3 v
   * @return Vec3
   **/
  Vec3 OppositeVec3(Vec3 v);
  /**
   *  this method finds the opposite of a vector by turning to negative
   *  components x and y:
   *
   *    | 1 | * -1 = | -1 |    |              |
   *  v | 1 | * -1 = | -1 |    |  /      ->   |  /      (opposite direction)
   *    | 0 |        | 0  |    |_______       |_______
   *
   **/

  //-------------------------------------------------------------------------//
  //                                OPERATORS                                //
  //-------------------------------------------------------------------------//

  /// operator+
  Vec3 operator+(const Vec3 v1, const Vec3 v2);

  /// operator-
  Vec3 operator-(const Vec3 v1, const Vec3 v2);

  /// operator*
  Vec3 operator*(const Vec3 v, const float scale);

  /// operator-
  Vec3 operator-(Vec3& v);

  /// operator+=
  void operator+=(Vec3& v1, const Vec3 v2);

  /// operator-=
  void operator-=(Vec3& v1, const Vec3 v2);

  /// operator==
  bool operator==(const Vec3 v1, const Vec3 v2);

  //-------------------------------------------------------------------------//
  //                                  DEBUG                                  //
  //-------------------------------------------------------------------------//

  /**
  * @brief print a vector / point (2D) on prompt
  * @param Vec3 v
  **/
  void PrintVec3(Vec3 v);

  /***************************************************************************
  *                                    MAT3                                  *
  ****************************************************************************/

  /**
   * @brief creates a matrix (3x3)
   * @param const Vec3 v1, const Vec3 v2, const Vec3, v3
   * @return Mat3
   **/
  Mat3 CreateMat3(const Vec3 v1, const Vec3 v2, const Vec3 v3);
  /**
   *  this is an example of a 3x3 matrix:
   *
   *    |  1   2   3  |
   *  m |  4   5   6  |
   *    |  7   8   9  |
   *
   **/

  /**
  * @brief creates a zero matrix (3x3)
  * @return Mat3
  **/
  Mat3 Mat3Zero();
  /**
  *  this calls 'CreateMat3()' with 3 zero vectors into 3 parameters and
  *  return them:
  *
  *    |  0   0   0  |
  *  m |  0   0   0  |
  *    |  0   0   0  |
  *
  **/

  /**
   * @brief create an identity matrix (3x3)
   * @return Mat3
   **/
  Mat3 IdentityMat3();
  /**
   *  this is an example of a 3x3 identity matrix:
   *
   *    |  1   0   0  |
   *  m |  0   1   0  |
   *    |  0   0   1  |
   *
   **/

  /**
   * @brief multiply 2 matrix (3x3)
   * @param const Mat3 m1, const Mat3 m2
   * @return Mat3
   **/
  Mat3 MultiMat3XMat3(const Mat3 m1, const Mat3 m2);
  /**
   *  to multiply 2 matrix, first multiply first row from the first matrix
   *  with first column from the second matrix and add the results:
   *
   *                     |      1            2            3      |
   *                     |      4            5            6      |
   *                     |      7            8            9      |
   *
   *  |   1   2   3   |  | 1*1+2*4+3*7  1*2+2*5+3*8  1*3+2*6+3*9 |
   *  |   4   5   6   |  | 4*1+5*4+6*7  4*2+5*5+6*8  4*3+5*6+6*9 |
   *  |   7   8   9   |  | 7*1+8*4+9*7  7*2+8*5+9*8  7*3+8*6+9*9 |
   *
   **/

  /**
   * @brief multiply a matrix (3x3) with a vector
   * @param const Mat3 m, const Vec3 v
   * @return Vec3
   **/
  Vec3 MultiMat3XVec3(const Mat3 m, const Vec3 v);
  /**
   *  to multiply a matrix with a vector, first multiply first row from
   *  the matrix with the vector and add the results:
   *
   *                     |      1      |
   *                     |      2      |
   *                     |      3      |
   *
   *  |   1   2   3   |  | 1*1+2*2+3*3 |
   *  |   4   5   6   |  | 4*1+5*2+6*3 |
   *  |   7   8   9   |  | 7*1+8*2+9*3 |
   *
   *  the result is a vector
   *
   **/

  /**
   * @brief create a translation matrix (2D)
   * @param float tx, float ty
   * @return Mat3
   **/
  Mat3 TranslateMat3(float tx, float ty);
  /**
   *  this is a translation matrix:
   *
   *  |   1   0   tx  |
   *  |   0   1   ty  |
   *  |   0   0   1   |
   *
   *  mulitply a point with this matrix to translate in space
   *
   **/

  /**
   * @brief create a scalation matrix (2D)
   * @param float sx, float sy
   * @return Mat3
   **/
  Mat3 ScaleMat3(float sx, float sy);
  /**
   *  this is a scalation matrix:
   *
   *  |   sx  0   0   |
   *  |   0   sy  0   |
   *  |   0   0   1   |
   *
   *  mulitply a point with this matrix to scale in space
   *
   **/

  /**
   * @brief create a rotation matrix (2D)
   * @param float rad
   * @return Mat3
   **/
  Mat3 RotateMat3(float rad);
  /**
   *  this is a rotation matrix:
   *
   *  |   cos  -sin  0   |
   *  |   sin  cos   0   |
   *  |    0    0    1   |
   *
   *  mulitply a point with this matrix to rotate in space
   *
   **/

  /**
  * @brief print a matrix on prompt
  * @param Mat3 m
  **/
  void PrintMat3(Mat3 m);

  /* ------------------------------ METHODS 3D ----------------------------- */

  /***************************************************************************
  *                                    VEC4                                  *
  ****************************************************************************/

  /**
   * @brief dot product of 2 vectors (3D)
   * @param const Vec4 v1, const Vec4 v2
   * @return float
   **/
  float DotProductVec4(const Vec4 v1, const Vec4 v2);
  /**
   *  multiply components x, y and z from one vector to the other:
   *
   *     | 2 | *    | 2 | =    | 4 |
   *  v1 | 2 | * v2 | 2 | = v3 | 4 |
   *     | 2 | *    | 2 | =    | 4 |
   *     | 0 |      | 0 |      | 0 |
   *
   *  then adds the components of the resultant vector:
   *
   *  4 + 4 + 4 = 12;
   *
   **/

  /**
   * @brief magnitude of a vector (3D)
   * @param const Vec4 v
   * @return Vec4
   **/
  float MagnitudeVec4(const Vec4 v);
  /**
   *  this method calculate the magnitude using pithagoras:
   *    ________________
   *  \/ 2^2 + 2^2 + 2^2 = 3.4
   *
   *  the magnitude is the length of a vector
   *
   **/

  /**
   * @brief angle between 2 vectors (3D)
   * @param const Vec4 v1, const Vec4 v2
   * @return float
   **/
  float AngleBetweenVec4(const Vec4 v1, const Vec4 v2);
  /**
   *  this method make uses of 'DotProductVec4()' and 'MagnitudeVec4()'
   *
   *  needs to calculate the dot product to find the angle between
   *  2 vectors and divide this with the multiply of the 2 vectors
   *  magnitudes:
   *
   *                 DotProductVec4(v1, v2)
   *  acos ( --------------------------------------- )
   *          MagnitudeVec4(v1) * MagnitudeVec4(v2)
   *
   **/


  /**
   * @brief creates a vector / point (3D)
   * @param const float x, const float y, const float z, const float w
   * @return Vec4
   **/
  Vec4 CreateVec4(const float x, const float y, const float z, const float w);
  /**
   *  this is an example of a vector:
   *
   *    | 1 |   |
   *  v | 1 |   |  /
   *    | 1 |   |_______
   *    | 0 |
   *
   *  this is an example of a point:
   *
   *    | 1 |   |
   *  p | 1 |   |  .
   *    | 1 |   |_______
   *    | 1 |
   *
   *  the difference between a point and a vector is that the homogeneous
   *  (w) component is 1 in a point and this is locatable in space and in
   *  a vector the homogeneous component is 0 and this is not locatable
   *  in space
   *
   **/

  /**
  * @brief creates a zero vector / point (3D)
  * @return Vec3
  **/
  Vec4 Vec4Zero();
  /**
  *  this calls 'CreateVec4()' with zeros into 4 parameters and return
  *  return them:
  *
  *    | 0 |
  *  v | 0 |
  *    | 0 |
  *    | 0 |
  *
  **/

  /**
  * @brief creates a vector forward (3D)
  * @return Vec4
  **/
  Vec4 Vec4Forward();
  /**
  *  this calls 'CreateVec4()' to create a vector forward
  *
  *    | 0 |
  *  v | 0 |
  *    | 1 |
  *    | 0 |
  *
  **/

  /**
  * @brief creates a vector up (3D)
  * @return Vec4
  **/
  Vec4 Vec4Up();
  /**
  *  this calls 'CreateVec4()' to create a vector up
  *
  *    | 0 |
  *  v | 1 |
  *    | 0 |
  *    | 0 |
  *
  **/

  /**
  * @brief creates a vector right (3D)
  * @return Vec4
  **/
  Vec4 Vec4Right();
  /**
  *  this calls 'CreateVec4()' to create a vector right
  *
  *    | 1 |
  *  v | 0 |
  *    | 0 |
  *    | 0 |
  *
  **/

  /**
   * @brief add 2 vectors / points (3D)
   * @param const Vec4 v1, const Vec4 v2
   * @return Vec4
   **/
  Vec4 AddVec4(const Vec4 v1, const Vec4 v2);
  /**
   *  this is an example of a vectors add:
   *
   *     | 1 | +    | 1 | =    | 2 |    |             |             |   /
   *  v1 | 1 | + v2 | 1 | = v3 | 2 |    |  /      +   |  /      =   |  /
   *     | 1 | +    | 1 | =    | 2 |    |_______      |_______      |_______
   *     | 0 | +    | 0 | =    | 0 |
   *
   *  if you add 2 vectors you obtain a bigger vector
   *
   *  this is an example of a points add:
   *
   *     | 1 | +    | 2 | =    | 3 |    |             |   .         |
   *  p1 | 1 | + p2 | 2 | = p3 | 3 |    |  .      +   |         =   |  ?
   *     | 1 | +    | 2 | =    | 3 |    |_______      |_______      |_______
   *     | 1 | +    | 1 | =    | 2 |
   *
   *  if you add 2 points you obtain another point but not homogenized and
   *  can not locate in space. use 'HomogenizeVec4()' to homogenize it
   *
   **/

  /**
   * @brief subtract 2 vectors / points (3D)
   * @param const Vec4 v1, const Vec4 v2
   * @return Vec4
   **/
  Vec4 SubstractVec4(const Vec4 v1, const Vec4 v2);
  /**
   *  this is an example of a vectors subtract:
   *
   *     | 2 | -    | 1 | =    | 1 |    |   /         |             |
   *  v1 | 2 | - v2 | 1 | = v3 | 1 |    |  /      +   |  /      =   |  /
   *     | 2 | -    | 1 | =    | 1 |    |_______      |_______      |_______
   *     | 0 | -    | 0 | =    | 0 |
   *
   *  if you subtract to vectors you obtain a smaller vector
   *
   *  this is an example of a points subtract:
   *
   *     | 2 | -    | 1 | =    | 1 |    |             |   .         |
   *  p1 | 2 | - p2 | 1 | = p3 | 1 |    |  .      +   |         =   |  /
   *     | 2 | -    | 1 | =    | 1 |    |_______      |_______      |_______
   *     | 1 | -    | 1 | =    | 0 |
   *
   *  if you subtract 2 points you obtain a vector that its size is the
   *  formed magnitude between the 2 points
   *
   **/

  /**
   * @brief homogenize a point (3D)
   * @param Vec4 v
   * @return Vec4
   **/
  Vec4 HomogenizeVec4(Vec4 v);
  /**
   *  this is a not homogenized point:
   *
   *    | 4 |
   *  p | 4 |
   *    | 4 |
   *    | 2 |
   *
   *  to homogenize a point must divide all its components with the
   *  homogeneous component
   *
   *    | 4 | / 2 = | 2 |   |
   *  p | 4 | / 2 = | 2 |   |   ·
   *    | 4 | / 2 = | 2 |   |_______
   *    | 2 | / 2 = | 1 |
   *
   *  the result is a homogenized point that can located in space
   *
   **/

  /**
   * @brief middle point between 2 points (3D)
   * @param const Vec4 v1, const Vec4 v2
   * @return Vec4
   **/
  Vec4 MidPointVec4(const Vec4 v1, const Vec4 v2);
  /**
   *  this method comprises 'AddVec4()' & 'HomogenizeVec4()'
   *
   *  first add 2 points with 'AddVec4()':
   *
   *     | 1 | +    | 3 | =    | 4 |    |             |     .       |
   *  p1 | 1 | + p2 | 3 | = p3 | 4 |    |  .      +   |         =   |  ?
   *     | 1 | +    | 3 | =    | 4 |    |_______      |_______      |_______
   *     | 1 | +    | 1 | =    | 2 |
   *
   *  then homogenize the result point with 'HomogenizeVec4()':
   *
   *     | 4 | / 2 = | 2 |    |
   *  p3 | 4 | / 2 = | 2 |    |   ·
   *     | 4 | / 2 = | 2 |    |_______
   *     | 2 | / 2 = | 1 |
   *
   *  the result is a point in the middle between the added points
   *
   **/

  /**
   * @brief normalize a vector (3D)
   * @param Vec4 v
   * @return Vec4
   **/
  Vec4 NormalizeVec4(Vec4 v);
  /**
   *  this method includes 'MagnitudeVec4()'
   *
   *  this is a not normalized vector (not unit):
   *
   *    | 2 |
   *  v | 2 |
   *    | 2 |
   *    | 0 |
   *
   *  first obtain the magnitude of the vector by doing pithagoras
   *  with 'MagnitudeVec4()':
   *    ________________
   *  \/ 2^2 + 2^2 + 2^2 = 3.4
   *
   *  then divide components x, y and z with the obtained magnitude:
   *
   *    | 2 | / 3.4 = | 0.5 |    |
   *  v | 2 | / 3.4 = | 0.5 |    |   ·
   *    | 2 | / 3.4 = | 0.5 |    |_______
   *    | 0 |       = | 0   |
   *
   **/

  /**
   * @brief scale a vector (3D)
   * @param Vec4 v, float scalex, float scaley, float scalez
   * @return Vec4
   **/
  Vec4 ScaleVec4(Vec4 v, float scalex, float scaley, float scalez);
  /**
   *  this method scales a vector, it means that its length will be
   *  multiplied by a number:
   *
   *    | 1 | * 2 = | 2 |    |              |   /
   *  v | 1 | * 2 = | 2 |    |  /      ->   |  /
   *    | 1 | * 2 = | 2 |    |_______       |_______
   *    | 0 |     = | 0 |
   *
   **/

  /**
   * @brief opposite of a vector (3D)
   * @param Vec4 v
   * @return Vec4
   **/
  Vec4 OppositeVec4(Vec4 v);
  /**
   *  this method finds the opposite of a vector by turning to negative
   *  components x, y and z:
   *
   *    | 1 | * -1 = | -1 |    |              |
   *  v | 1 | * -1 = | -1 |    |  /      ->   |  /      (opposite direction)
   *  v | 1 | * -1 = | -1 |    |_______       |_______
   *    | 0 |        | 0  |
   *
   **/

  //-------------------------------------------------------------------------//
  //                                OPERATORS                                //
  //-------------------------------------------------------------------------//

  /// operator+
  Vec4 operator+(const Vec4 v1, const Vec4 v2);

  /// operator-
  Vec4 operator-(const Vec4 v1, const Vec4 v2);

  /// operator*
  Vec4 operator*(const Vec4 v, const float scale);

  /// operator+=
  void operator+=(Vec4& v1, const Vec4 v2);

  /// operator-=
  void operator-=(Vec4& v1, const Vec4 v2);

  /// operator==
  bool operator==(const Vec4 v1, const Vec4 v2);

  //-------------------------------------------------------------------------//
  //                                  DEBUG                                  //
  //-------------------------------------------------------------------------//

  /**
  * @brief print a vector / point (3D) on prompt
  * @param Vec4 v
  **/
  void PrintVec4(Vec4 v);

  /***************************************************************************
  *                                    MAT4                                  *
  ****************************************************************************/

  /**
   * @brief creates a matrix (4x4)
   * @param const Vec4 v1, const Vec4 v2, const Vec4, v3, const Vec4 v4
   * @return Mat4
   **/
  Mat4 CreateMat4(const Vec4 v1, const Vec4 v2, const Vec4 v3, const Vec4 v4);
  /**
   *  this is an example of a 3x3 matrix:
   *
   *    |  1   2   3   4  |
   *  m |  5   6   7   8  |
   *    |  9   10  11  12 |
   *    |  13  14  15  16 |
   *
   **/

  /**
  * @brief creates a zero matrix (4x4)
  * @return Mat4
  **/
  Mat4 Mat4Zero();
  /**
  *  this calls 'CreateMat4()' with 4 zero vectors into 4 parameters and
  *  return them:
  *
  *    |  0   0   0   0  |
  *  m |  0   0   0   0  |
  *    |  0   0   0   0  |
  *    |  0   0   0   0  |
  *
  **/

  /**
   * @brief create an identity matrix (4x4)
   * @return Mat4
   **/
  Mat4 IdentityMat4();
  /**
   *  this is an example of a 4x4 identity matrix:
   *
   *    |  1   0   0   0  |
   *  m |  0   1   0   0  |
   *    |  0   0   1   0  |
   *    |  0   0   0   1  |
   *
   **/

  /**
   * @brief multiply 2 matrix (4x4)
   * @param const Mat4 m1, const Mat4 m2
   * @return Mat4
   **/
  Mat4 MultiMat4XMat4(const Mat4 m1, const Mat4 m2);
  /**
   *  to multiply 2 matrix, first multiply first row from the first matrix
   *  with first column from the second matrix and add the results:
   *
   *                    |        1                     2                      3                      4              |
   *                    |        5                     6                      7                      8              |
   *                    |        9                     10                     11                     12             |
   *                    |        13                    14                     15                     16             |
   *
   *  |  1  2  3  4  |  | 1*1+2*5+3*9+4*13      1*2+2*6+3*10+4*14      1*3+2*7+3*11+4*15      1*4+2*8+3*12+4*16     |
   *  |  5  6  7  8  |  | 5*1+6*5+7*9+8*13      5*2+6*6+7*10+8*14      5*3+6*7+7*11+8*15      5*4+6*8+7*12+8*16     |
   *  |  9  10 11 12 |  | 9*1+10*5+11*9+12*13   9*2+10*6+11*10+12*14   9*3+10*7+11*11+12*15   9*4+10*8+11*12+12*16  |
   *  |  13 14 15 16 |  | 13*1+14*5+15*9+16*13  13*2+14*6+15*10+16*14  13*3+14*7+15*11+16*15  13*4+14*8+15*12+16*16 |
   *
   **/

  /**
   * @brief multiply a matrix (4x4) with a vector
   * @param const Mat4 m, const Vec4 v
   * @return Vec4
   **/
  Vec4 MultiMat4XVec4(const Mat4 m, const Vec4 v);
  /**
   *  to multiply a matrix with a vector, first multiply first row from
   *  the matrix with the vector and add the results:
   *
   *                         |          1          |
   *                         |          2          |
   *                         |          3          |
   *                         |          4          |
   *
   *  |   1   2   3   4   |  | 1*1+2*2+3*3+4*4     |
   *  |   5   6   7   8   |  | 5*1+6*2+7*3+8*4     |
   *  |   9   10  11  12  |  | 9*1+10*2+11*3+12*4  |
   *  |   13  14  15  16  |  | 13*1+14*2+15*3+16*4 |
   *
   *  the result is a vector
   *
   **/

  /**
   * @brief create a translation matrix (3D)
   * @param float tx, float ty, float tz
   * @return Mat4
   **/
  Mat4 TranslateMat4(float tx, float ty, float tz);
  /**
   *  this is a translation matrix:
   *
   *  |   1   0   0   tx  |
   *  |   0   1   0   ty  |
   *  |   0   0   1   tz  |
   *  |   0   0   0   1   |
   *
   *  mulitply a point with this matrix to translate in space
   *
   **/

  /**
   * @brief create a scalation matrix (3D)
   * @param float sx, float sy, float sz
   * @return Mat4
   **/
  Mat4 ScaleMat4(float sx, float sy, float sz);
  /**
   *  this is a scalation matrix:
   *
   *  |   sx  0   0   0   |
   *  |   0   sy  0   0   |
   *  |   0   0   sz  0   |
   *  |   0   0   0   1   |
   *
   *  mulitply a point with this matrix to scale in space
   *
   **/

  /**
   * @brief create a X axis rotation matrix (3D)
   * @param float rad
   * @return Mat4
   **/
  Mat4 RotateMat4X(float rad);
  /**
   *  this is a X axis rotation matrix:
   *
   *  |   1     0     0     0   |
   *  |   0     cos   -sin  0   |
   *  |   0     sin   cos   0   |
   *  |   0     0     0     1   |
   *
   *  mulitply a point with this matrix to rotate in space
   *
   **/

  /**
   * @brief create a Y axis rotation matrix (3D)
   * @param float rad
   * @return Mat4
   **/
  Mat4 RotateMat4Y(float rad);
  /**
   *  this is a Y axis rotation matrix:
   *
   *  |   cos   0     sin   0   |
   *  |   0     1     0     0   |
   *  |   -sin  0     cos   0   |
   *  |   0     0     0     1   |
   *
   *  mulitply a point with this matrix to rotate in space
   *
   **/

  /**
   * @brief create a Z axis rotation matrix (3D)
   * @param float rad
   * @return Mat4
   **/
  Mat4 RotateMat4Z(float rad);
  /**
   *  this is a Z axis rotation matrix:
   *
   *  |   cos   -sin  0     0   |
   *  |   sin   cos   0     0   |
   *  |   0     0     1     0   |
   *  |   0     0     0     1   |
   *
   *  mulitply a point with this matrix to rotate in space
   *
   **/

   /// rotation vector methods
   Vec4 RotateVec4X(Vec4 v, const float rad);
   Vec4 RotateVec4Y(Vec4 v, const float rad);
   Vec4 RotateVec4Z(Vec4 v, const float rad);
   Vec4 RotateVec4XYZ(Vec4 v, Vec3 rot);

  /**
   * @brief create a projection matrix (3D)
   * @return Mat4
   **/
  Mat4 ProjectionMat4();
  /**
   *  this is projection matrix:
   *
   *  |   1     0     0     0   |
   *  |   0     1     0     0   |
   *  |   0     0     1     0   |
   *  |   0     0     1     0   |
   *
   *  mulitply a point with this matrix project it
   *
   **/

  /**
  * @brief print a matrix on prompt
  * @param Mat3 m
  **/
  void PrintMat4(Mat4 m);
}

#endif
