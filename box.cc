/**
 *
 * @brief Box Class
 * @author Toni Marquez
 *
 **/

#include "box.h"

/// constructor
Box::Box() {

  transform_ = gtmath::IdentityMat3();
  position_ = { 0.0f, 0.0f, 0.0f };
  scale_ = { 0.0f, 0.0f, 0.0f };
  vertex_[0] = { 0.0f, 0.0f, 0.0f };
  vertex_[1] = { 0.0f, 0.0f, 0.0f };
  vertex_[2] = { 0.0f, 0.0f, 0.0f };
  vertex_[3] = { 0.0f, 0.0f, 0.0f };
  points_[0] = 0.0f;
  points_[1] = 0.0f;
  points_[2] = 0.0f;
  points_[3] = 0.0f;
  points_[4] = 0.0f;
  points_[5] = 0.0f;
  points_[6] = 0.0f;
  points_[7] = 0.0f;
  width_ = 0.0f;
  height_ = 0.0f;
  rotation_ = 0.0f;
  color_[1] = 0;
  color_[0] = 0;
  color_[2] = 0;
  alpha_ = 0;
  draw_lines_ = false;
  filled_ = false;
}

/// init values
void Box::init(const float width,
               const float height,
               const gtmath::Vec3 position,
               const gtmath::Vec3 scale,
               const float rotation,
               const gtmath::Vec3 color,
               const unsigned char alpha,
               bool filled) {

  width_ = width;
  height_ = height;
  position_ = position;
  scale_ = scale;
  rotation_ = rotation;
  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
  alpha_ = alpha;
  filled_ = filled;

  vertex_[0] = { -width_ / 2, -height_ / 2, 1.0f };
  vertex_[1] = { width_ / 2, -height_ / 2, 1.0f };
  vertex_[2] = { width_ / 2, height_ / 2, 1.0f };
  vertex_[3] = { -width_ / 2, height_ / 2, 1.0f };

  calculateTransform();
}

/// calculate transform
void Box::calculateTransform() {

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
void Box::render() {

  gtmath::Vec3 temp_point;

  for (unsigned short int i = 0; i < kNumSides; i++){
    temp_point = gtmath::MultiMat3XVec3(transform_, vertex_[i]);
    points_[i * 2] = temp_point.x;
    points_[i * 2 + 1] = temp_point.y;
  }

  points_[8] = points_[0];
  points_[9] = points_[1];

  if (draw_lines_){
    ESAT::DrawSetStrokeColor(color_[0], color_[1], color_[2], alpha_);
  }
  else { ESAT::DrawSetStrokeColor(color_[0], color_[1], color_[2], 0); }
  if (filled_){
    ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], alpha_);
  }
  else { ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], 0); }
  ESAT::DrawSolidPath(points_, kNumSides + 1);
}

/** functions **/
void Box::translate(const gtmath::Vec3 translation) {

  position_ += translation;
  calculateTransform();
}

void Box::scale(const gtmath::Vec3 scalation) {

  scale_ += scalation;
  calculateTransform();
}

void Box::rotate(const float rotation) {

  rotation_ += rotation;
  calculateTransform();
}

/** setters **/
void Box::set_position(const gtmath::Vec3 position) {

  position_ = position;
  calculateTransform();
}

void Box::set_scale(const gtmath::Vec3 scale) {

  scale_ = scale;
  calculateTransform();
}

void Box::set_rotation(const float rotation) {

  rotation_ = rotation;
  calculateTransform();
}

void Box::set_color(const gtmath::Vec3 color) {

  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
}

void Box::set_alpha(const unsigned char alpha) {

  alpha_ = alpha;
}

/** getters **/
const gtmath::Vec3 Box::position() {

  return position_;
}

const gtmath::Vec3 Box::scale() {

  return scale_;
}

const float Box::rotation() {

  return rotation_;
}

const float Box::width() {

  return width_;
}

const float Box::height() {

  return height_;
}

/// draw lines
void Box::drawLines(const bool enabled) {

  draw_lines_ = enabled;
}

/// destructor
Box::~Box() {}
