/**
 *
 * @brief Box Header
 * @author Toni Marquez
 *
 **/

#ifndef __BOX_H__
#define __BOX_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ESAT/draw.h>

#include "gtmath.h"

class Box {

  public:

    /// constructor
    Box();

    /// copy constructor
    Box(const Box& copy);

    /// destructor
    ~Box();

    /// init values
    void init(const float width = 50.0f,
              const float height = 50.0f,
              const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
              const gtmath::Vec3 scale = { 1.0f, 1.0f, 1.0f },
              const float rotation = 0.0f,
              const gtmath::Vec3 color = { 255.0f, 255.0f, 255.0f },
              const unsigned char alpha = 255,
              bool filled = false);

    /// calculate transform
    void calculateTransform();

    /// draw on screen
    void render();

    /** functions **/
    void translate(const gtmath::Vec3 translation);
    void scale(const gtmath::Vec3 scalation);
    void rotate(const float rotation);

    /** setters **/
    void set_position(const gtmath::Vec3 position);
    void set_scale(const gtmath::Vec3 scale);
    void set_rotation(const float rotation);
    void set_color(const gtmath::Vec3 color);
    void set_alpha(const unsigned char alpha);

    /** getters **/
    const gtmath::Vec3 position();
    const gtmath::Vec3 scale();
    const float rotation();
    const float width();
    const float height();

    /// public consts
    static const unsigned short int kNumSides = 4;

  private:

    /// private vars
    gtmath::Mat3 transform_;
    gtmath::Vec3 position_;
    gtmath::Vec3 scale_;
    gtmath::Vec3 vertex_[kNumSides];
    float points_[kNumSides * 2];
    float width_;
    float height_;
    float rotation_;
    unsigned char color_[3];
    unsigned char alpha_;
    bool filled_;
};

#endif
