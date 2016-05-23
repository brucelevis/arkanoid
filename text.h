/**
 *
 * @brief Text Header
 * @author Toni Marquez
 *
 **/

#ifndef __TEXT_H__
#define __TEXT_H__ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ESAT/draw.h>

#include "gtmath.h"

class Text {

  public:

    /// constructor
    Text();

    /// destructor
    ~Text();

    /// init values
    void init(const char* text = "none\0",
              const gtmath::Point position = { 0.0f, 0.0f },
              const unsigned short int size = 25,
              const gtmath::Vec3 color = { 255.0f, 255.0f, 255.0f },
              const char* font = "data/assets/fonts/04B.ttf\0");

    /// draw on screen
    void render();

    /** setters **/
    void set_text(const char* string);
    void set_position(const gtmath::Point position);
    void set_color(const gtmath::Vec3 color);
    void set_alpha(const unsigned char alpha);

    /** getters **/
    const char* text();
    const gtmath::Point position();

  private:

    /// copy constructor
    Text(const Text& copy);
    Text operator=(const Text& copy);

    /// private vars
    gtmath::Point position_;
    char text_[512];
    char font_[128];
    unsigned char color_[3];
    unsigned char alpha_;
    unsigned short int size_;
};

#endif
