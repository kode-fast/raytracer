

/*
1. using ppm file format for writing 

*/

#include <iostream>
#include <fstream>

#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"


double ASPECT_RATIO = 2.0; // 2.0/1.0 WIDTH/HEIGHT

int IMAGE_WIDTH = 512;

int IMAGE_HEIGHT = int(IMAGE_WIDTH/ASPECT_RATIO);
// w / (w/h) = w/1 * h/w = h


color diffuse(ray &ray, vec3 normal){

    // return dot of normal and ray
    return color(0,0,0);
}

double sphere_hit (ray &ray){

    vec3 center = vec3(0,0,-2);
    double radius = 1;

    vec3 ray_to_sphere = center - ray.origin();

    // TODO do the math 
    double a = dot(ray.direction(), ray.direction());
    double b = -2.0 * dot(ray.direction(), ray_to_sphere);
    double c = dot(ray_to_sphere,ray_to_sphere) - (radius*radius);

    double discrimanite = (b*b) - (4*a*c);
    
    // if discrimative is negative no hits - as no roots where found 
    if (discrimanite < 0.0){
        return 0.0;
    }
    else{
        
        // this is t value for the ray 
        // using - as we want the closer (smaller) t valuee
        return (-b - std::sqrt(discrimanite)) / (2*a) ;
 
    }



}

color ray_color(ray &ray){
    //color sphere_color 
    color pixel = color(0.0, 0.4, 0.2);
    double hit = sphere_hit(ray);

    // sphere was hit
    if (hit > 0.0){
        
        vec3 N = unit_vector(ray.pos(hit) - vec3(0,0,-2));

        // normal color
        // pixel = color(N.x(), N.y(), N.z());
        
        // basic diffuse color
        // added 0.5 for when ray and normal are orthogonal and dot is 0 
        pixel = pixel * ( 0.5 + (dot( -ray.direction(), N)));

        return pixel;
    }


    // background
    // make direction a unit vector 
    vec3 unit_direction = unit_vector(ray.direction());
    // now vector has length 1, so y vector must be -1<y<1
    // calculate a based on y vector 
    // abs(y) means y is longest in the middle 
    double a = 0.5 * (unit_direction.y() + 1);
    // lerp from top to bottoms
    // (1-a)*(value a) + (a)*(value b)
    pixel = (1-a)*color(1.0,1.0,1.0) + a*color(0.2, 0.4, 0.7);
    return pixel;

}


int main(){

    // set up image file stream 
    // .open w/ no flages overwrites the file
    std::ofstream image;
    image.open("image.ppm");
    image << "P3" << '\n' << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << '\n' << "255" << '\n';

    // view and screen (image) 

    point3 ray_origin;
    vec3 ray_direction;


    // for view we want camera at (0,0,0)
    // but for our image the pixels start writing at the top left 

    /*
    view aspect ratio needs to match image aspect ratio
    */

    // arbatrary viewport height for now 

    // recalculate aspect ratio to avoid of by one rounding errors 
    // where number of dots in viewport is +- number of pixels 
    // standerd is 1/1 pixel height width ratio
    double aspect_ratio = (double)IMAGE_WIDTH/(double)IMAGE_HEIGHT;
    // distance from camera origin to viewport 
    double focal_length = 2.0; 
    double viewport_height = 4.0;
    double viewport_width = viewport_height * (aspect_ratio) ;

    // x,y = u,v
    point3 camera_center = point3(0,0,0);
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // how much space is in between each ray-dot
    vec3 pixel_delta_u = viewport_u / IMAGE_WIDTH;
    vec3 pixle_delta_v = viewport_v / IMAGE_HEIGHT;

    // starting pixel in top left corner 
    // standerd right hand coord
    // negitive z axis points forward
    point3 viewport_top_left = camera_center 
    - point3(0,0, focal_length) - viewport_u/2 - viewport_v/2;

    // get center of first pixel dot in viewport 
    vec3 top_left_pixel = viewport_top_left + ( 0.5 * (  pixel_delta_u + pixle_delta_v) );


    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        for(int j = 0; j< IMAGE_WIDTH; j++) {
            
            point3 pixel_center = top_left_pixel + (i * pixle_delta_v) + (j * pixel_delta_u);

            // for orthographic ray origin is the viewport-dot
            ray_origin = camera_center;
            ray_direction = pixel_center - camera_center;

            color pixel_color = ray_color(ray(ray_origin, ray_direction));

            write_image(image, pixel_color);
            
        }
    }

    image.close();

}

