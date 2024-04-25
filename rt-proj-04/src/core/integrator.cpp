#include "integrator.h"
#include "material.h"

namespace rt3{

void SamplerIntegrator::render( const unique_ptr<Scene> &scene ) {
    int w = camera->film->width();
    int h = camera->film->height();

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            // Determine the ray for the current camera type.
            Point2f screen_coord{ float(j)/float(w), float(i)/float(h) };
            Ray ray = camera->generate_ray(i,j); // Generate the ray from (x,y)
            // Determine the incoming light.
            auto temp_L =  Li( ray, scene );
            Color L = (temp_L.has_value()) ?  temp_L.value() : scene->background->sampleXYZ(screen_coord) ;
            // Add color (radiance) to the image.
            camera->film->add_sample( Point2i( i, j ), L ); // Set color of pixel (x,y) to L.
        }
    }
    camera->film->write_image();

    return;
}

} // namespace rt3
