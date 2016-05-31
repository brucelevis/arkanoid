/**
 *
 * @brief Poly Header
 * @author Toni Marquez
 *
 **/

#ifndef __POLY_H__
#define __POLY_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ESAT/draw.h>

#include "gtmath.h"

class Poly {

  public:

    /// constructor & destructor
    Poly();
    ~Poly();

    /** init values **/
    /// regular polygon
    void init(const unsigned short int num_verts = 10,
              const float radius = 50.0f,
              const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
              const gtmath::Vec3 scale = { 1.0f, 1.0f, 1.0f },
              const float rotation = 0.0f,
              const gtmath::Vec3 color = { 255.0f, 255.0f, 255.0f },
              const unsigned char alpha = 255,
              bool filled = false);
    /// free polygon
    void init(const unsigned short int num_verts,
              const gtmath::Vec3* verts,
              const gtmath::Vec3 position = { 0.0f, 0.0f, 1.0f },
              const gtmath::Vec3 scale = { 1.0f, 1.0f, 1.0f },
              const float rotation = 0.0f,
              const gtmath::Vec3 color = { 100.0f, 220.0f, 125.0f },
              const unsigned char alpha = 255);

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
    const float radius();

    /// draw lines
    void drawLines(const bool enabled);

  private:

    /// copy constructor
    Poly(const Poly& copy);
    Poly operator=(const Poly& copy);

    /// private vars
    unsigned short int num_verts_;
    gtmath::Mat3 transform_;
    gtmath::Vec3* verts_;
    gtmath::Vec3 position_;
    gtmath::Vec3 scale_;
    float rotation_;
    float radius_;
    float* points_;
    unsigned char color_[3];
    unsigned char alpha_;
    bool draw_lines_;
    bool filled_;
};

#endif
