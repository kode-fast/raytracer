#ifndef COLOR_H
#define COLOR_H


#include <fstream>
#include "vec3.hpp"


using color = vec3;

void write_image(std::ofstream &image, const color &pixel_color ){

    double red =    pixel_color.x();
    double green =  pixel_color.y();
    double blue =   pixel_color.z();

    int r255 = int(255.0 * red);
    int g255 = int(255.0 * green);
    int b255 = int(255.0 * blue);

    image << r255 << ' ' << g255 << ' ' << b255 << '\n';

}

#endif