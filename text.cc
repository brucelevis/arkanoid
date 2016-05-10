/**
 *
 * @brief Text Class
 * @author Toni Marquez
 *
 **/

#include "text.h"

/// constructor
Text::Text() {

  position_ = { 0.0f, 0.0f };
  memset(text_, 0, 512);
  memset(font_, 0, 128);
  color_[0] = 0;
  color_[1] = 0;
  color_[2] = 0;
  alpha_ = 0;
  size_ = 0;
}

/// copy constructor
Text::Text(const Text& copy) {

  position_ = copy.position_;
  sprintf(text_, "%s", copy.text_);
  sprintf(font_, "%s", copy.font_);
  color_[0] = copy.color_[0];
  color_[1] = copy.color_[1];
  color_[2] = copy.color_[2];
  alpha_ = copy.alpha_;
  size_ = copy.size_;
}

/// init values
void Text::init(char* text,
                gtmath::Point position,
                unsigned short int size,
                gtmath::Vec3 color,
                char* font) {

  sprintf(text_, "%s", text);
  position_ = position;
  size_ = size;
  color_[0] = color.x;
  color_[1] = color.y;
  color_[2] = color.z;
  alpha_ = 255;
  sprintf(font_, "%s", font);
}

/// draw on screen
void Text::render() {

  ESAT::DrawSetTextFont(font_);
  ESAT::DrawSetStrokeColor(color_[0], color_[1], color_[2], alpha_);
  ESAT::DrawSetFillColor(color_[0], color_[1], color_[2], alpha_);
  ESAT::DrawSetTextSize(size_);
  ESAT::DrawText(position_.x, position_.y, text_);
}

/** setters **/
void Text::set_text(const char* string) {

  sprintf(text_, "%s", string);
}

void Text::set_position(const gtmath::Point position) {

  position_.x = position.x;
  position_.y = position.y;
}

void Text::set_color(const gtmath::Vec3 color) {

  color_[0] = (unsigned char)color.x;
  color_[1] = (unsigned char)color.y;
  color_[2] = (unsigned char)color.z;
}

void Text::set_alpha(const unsigned char alpha) {

  alpha_ = alpha;
}

/** getters **/
const char* Text::text() {

  return text_;
}

const gtmath::Point Text::position() {

  return position_;
}

/// destructor
Text::~Text() {}
