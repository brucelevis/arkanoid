/**
 *
 * @brief Polygon Class
 * @author Toni Marquez
 *
 **/

#include "polygon.h"

/// constructor
Polygon::Polygon() {

  num_verts_ = 0;
  transform_ = gtmath::IdentityMat3();
  verts_ = nullptr;
  position_ = { 0.0f, 0.0f, 0.0f };
  scale_ = { 0.0f, 0.0f, 0.0f };
  rotation_ = 0.0f;
  radius_ = 0.0f;
  points_ = nullptr;
  color_[0] = 0;
  color_[1] = 0;
  color_[2] = 0;
  alpha_ = 0;
  filled_ = false;
}

/// copy constructor
Polygon::Polygon(const Polygon& copy) {

  num_verts_ = copy.num_verts_;
  transform_ = copy.transform_;
  verts_ = copy.verts_;
  position_ = copy.position_;
  scale_ = copy.scale_;
  rotation_ = copy.rotation_;
  radius_ = copy.radius_;
  points_ = copy.points_;
  color_[0] = copy.color_[0];
  color_[1] = copy.color_[1];
  color_[2] = copy.color_[2];
  alpha_ = copy.alpha_;
  filled_ = copy.filled_;
}

/** init values (overloaded) **/
/// regular polygon
void Polygon::init(const unsigned short int num_verts,
                   const float radius,
                   const gtmath::Vec3 position,
                   const gtmath::Vec3 scale,
                   const float rotation,
                   const gtmath::Vec3 color,
                   const unsigned char alpha,
                   bool filled) {

  num_verts_ = num_verts;
  radius_ = radius;
  position_ = position;
  scale_ = scale;
  rotation_ = rotation;
  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
  alpha_ = alpha;
  filled_ = filled;

  verts_ = (gtmath::Vec3*)malloc(sizeof(gtmath::Vec3) * num_verts_);
  points_ = (float*)malloc(sizeof(float) * (num_verts_ * 2) + 2);

  for (unsigned short int i = 0; i < num_verts_; i++){

    verts_[i].x = radius_ * cos(2 * kPid * i / num_verts_);
    verts_[i].y = radius_ * sin(2 * kPid * i / num_verts_);
    verts_[i].z = 1.0f;
  }

  calculateTransform();
}

/// free polygon
void Polygon::init(const unsigned short int num_verts,
                   const gtmath::Vec3* verts,
                   const gtmath::Vec3 position,
                   const gtmath::Vec3 scale,
                   const float rotation,
                   const gtmath::Vec3 color,
                   const unsigned char alpha) {

  num_verts_ = num_verts;
  position_ = position;
  scale_ = scale;
  rotation_ = rotation;
  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
  alpha_ = alpha;

  verts_ = (gtmath::Vec3*)malloc(sizeof(gtmath::Vec3) * num_verts_);
  points_ = (float*)malloc(sizeof(float) * (num_verts_ * 2) + 2);

  for (unsigned short int i = 0; i < num_verts_; i++){ verts_[i] = verts[i]; }

  calculateTransform();
}

/// calculate transform
void Polygon::calculateTransform() {

  transform_ = gtmath::IdentityMat3();
  transform_ = gtmath::MultiMat3XMat3(transform_,
                                      gtmath::ScaleMat3(scale_.x, scale_.y));
  transform_ = gtmath::MultiMat3XMat3(transform_,
                                      gtmath::RotateMat3(rotation_));
  transform_ = gtmath::MultiMat3XMat3(transform_,
                                      gtmath::TranslateMat3(position_.x,
                                                            position_.y));
}

/// draw on screen
void Polygon::render() {

  gtmath::Vec3 temp_point;

  for (unsigned short int i = 0; i < num_verts_; i++){

    temp_point = gtmath::MultiMat3XVec3(transform_, verts_[i]);
    points_[i * 2] = temp_point.x;
    points_[i * 2 + 1] = temp_point.y;
  }

  points_[(num_verts_ * 2 + 2) - 2] = points_[0];
  points_[(num_verts_ * 2 + 2) - 1] = points_[1];

  ESAT::DrawSetStrokeColor(color_[0], color_[1], color_[2], alpha_);
  if (filled_){
    ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], alpha_);
  }
  else { ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], 0); }
  ESAT::DrawSolidPath(points_, num_verts_ + 1);
}

/** functions **/
void Polygon::translate(const gtmath::Vec3 translation) {

  position_ += translation;
  calculateTransform();
}

void Polygon::scale(const gtmath::Vec3 scalation) {

  scale_ += scalation;
  calculateTransform();
}

void Polygon::rotate(const float rotation) {

  rotation_ += rotation;
  calculateTransform();
}

/** setters **/
void Polygon::set_position(const gtmath::Vec3 position) {

  position_ = position;
  calculateTransform();
}
void Polygon::set_scale(const gtmath::Vec3 scale) {

  scale_ = scale;
  calculateTransform();
}

void Polygon::set_rotation(const float rotation) {

  rotation_ = rotation;
  calculateTransform();
}

void Polygon::set_color(const gtmath::Vec3 color) {

  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
}

void Polygon::set_alpha(const unsigned char alpha) {

  alpha_ = alpha;
}

/** getters **/
const gtmath::Vec3 Polygon::position() {

  return position_;
}

const gtmath::Vec3 Polygon::scale() {

  return scale_;
}

const float Polygon::rotation() {

  return rotation_;
}

const float Polygon::radius() {

  return radius_;
}

/// destructor
Polygon::~Polygon() {

  free(verts_);
  free(points_);
  verts_ = nullptr;
  points_ = nullptr;
}
