/**
 *
 * @brief Sprite Class
 * @author Toni Marquez
 *
 **/

#include "sprite.h"

/// constructor
Sprite::Sprite() {

  handle_ = NULL;
  ESAT::SpriteTransformInit(&transform_);
  memset(handle_path_, 0, 128);
  centered_pivot_ = false;
}

/// copy constructor
Sprite::Sprite(const Sprite& copy) {

  handle_ = copy.handle_;
  transform_ = copy.transform_;
  sprintf(handle_path_, "%s", copy.handle_path_);
  centered_pivot_ = copy.centered_pivot_;
}

/// init values
void Sprite::init(const char* handle_path,
                  const gtmath::Vec3 position,
                  const bool centered_pivot) {

  handle_ = ESAT::SpriteFromFile(handle_path);
  sprintf(handle_path_, "%s", handle_path);
  centered_pivot_ = centered_pivot;
  transform_.x = position.x;
  transform_.y = position.y;

  if (centered_pivot_){
    transform_.sprite_origin_x = width() / 2;
    transform_.sprite_origin_y = height() / 2;
  }
}

/// render on screen
void Sprite::render() {

  ESAT::DrawSprite(handle_, transform_);
}

/** setters **/
void Sprite::set_sprite(const char* handle_path) {

  handle_ = ESAT::SpriteFromFile(handle_path);
}

void Sprite::set_pivot(const gtmath::Vec3 pivot) {

  transform_.sprite_origin_x = pivot.x;
  transform_.sprite_origin_y = pivot.y;
}

void Sprite::set_position(const gtmath::Vec3 position) {

  transform_.x = position.x;
  transform_.y = position.y;
}

void Sprite::set_scale(const gtmath::Vec3 scale) {

  transform_.scale_x = scale.x;
  transform_.scale_y = scale.y;
}

void Sprite::set_rotation(const float rotation) {

  transform_.angle = rotation;
}

/** getters **/
const float Sprite::width() {

  return (ESAT::SpriteWidth(handle_) * transform_.scale_x);
}

const float Sprite::height() {

  return (ESAT::SpriteHeight(handle_) * transform_.scale_y);
}

const gtmath::Vec3 Sprite::position() {
  gtmath::Vec3 position;

  position.x = transform_.x;
  position.y = transform_.y;

  return position;
}

/// destructor
Sprite::~Sprite() {

  ESAT::SpriteRelease(handle_);
}
