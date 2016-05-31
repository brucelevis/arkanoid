/**
 *
 * @brief Sprite Header
 * @author Toni Marquez
 *
 **/

#ifndef __SPRITE_H__
#define __SPRITE_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ESAT/draw.h>
#include <ESAT/sprite.h>
#include <ESAT/input.h>

#include "gtmath.h"

class Sprite {

  public:

    /// constructor & destructor
    Sprite();
    ~Sprite();

    /// init values
    void init(const char* handle_path = "data/assets/sprites/sample.png",
              const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
              const bool centered_pivot = true);

    /// render on screen
    void render();

    /** setters **/
    void set_sprite(const char* handle_path);
    void set_pivot(const gtmath::Vec3 pivot);
    void set_position(const gtmath::Vec3 position);
    void set_scale(const gtmath::Vec3 scale);
    void set_rotation(const float rotation);

    /** getters **/
    const float width();
    const float height();
    const gtmath::Vec3 position();

  private:

    /// copy constructor
    Sprite(const Sprite& copy);
    Sprite operator=(const Sprite& copy);

    /// private vars
    ESAT::SpriteHandle handle_;
    ESAT::SpriteTransform transform_;
    char handle_path_[128];
    bool centered_pivot_;
};

#endif
