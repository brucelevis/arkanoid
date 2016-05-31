/**
 *
 * @brief Poly Class
 * @author Toni Marquez
 *
 **/

#include "poly.h"

/// constructor
Poly::Poly() {

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
  draw_lines_ = false;
  filled_ = false;
}

/** init values  **/
/// regular polygon
void Poly::init(const unsigned short int num_verts,
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
void Poly::init(const unsigned short int num_verts,
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
void Poly::calculateTransform() {

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
void Poly::render() {

  gtmath::Vec3 temp_point;

  for (unsigned short int i = 0; i < num_verts_; i++){
    temp_point = gtmath::MultiMat3XVec3(transform_, verts_[i]);
    points_[i * 2] = temp_point.x;
    points_[i * 2 + 1] = temp_point.y;
  }

  points_[(num_verts_ * 2 + 2) - 2] = points_[0];
  points_[(num_verts_ * 2 + 2) - 1] = points_[1];

  if (draw_lines_){
    ESAT::DrawSetStrokeColor(color_[0], color_[1], color_[2], alpha_);
  }
  else { ESAT::DrawSetStrokeColor(color_[0], color_[1], color_[2], 0); }
  if (filled_){
    ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], alpha_);
  }
  else { ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], 0); }
  ESAT::DrawSolidPath(points_, num_verts_ + 1);
}

/** functions **/
void Poly::translate(const gtmath::Vec3 translation) {

  position_ += translation;
  calculateTransform();
}

void Poly::scale(const gtmath::Vec3 scalation) {

  scale_ += scalation;
  calculateTransform();
}

void Poly::rotate(const float rotation) {

  rotation_ += rotation;
  calculateTransform();
}

/** setters **/
void Poly::set_position(const gtmath::Vec3 position) {

  position_ = position;
  calculateTransform();
}

void Poly::set_scale(const gtmath::Vec3 scale) {

  scale_ = scale;
  calculateTransform();
}

void Poly::set_rotation(const float rotation) {

  rotation_ = rotation;
  calculateTransform();
}

void Poly::set_color(const gtmath::Vec3 color) {

  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
}

void Poly::set_alpha(const unsigned char alpha) {

  alpha_ = alpha;
}

/** getters **/
const gtmath::Vec3 Poly::position() {

  return position_;
}

const gtmath::Vec3 Poly::scale() {

  return scale_;
}

const float Poly::rotation() {

  return rotation_;
}

const float Poly::radius() {

  return radius_;
}

/// draw lines
void Poly::drawLines(const bool enabled) {

  draw_lines_ = enabled;
}

/// destructor
Poly::~Poly() {

  free(verts_);
  free(points_);
  verts_ = nullptr;
  points_ = nullptr;
}
