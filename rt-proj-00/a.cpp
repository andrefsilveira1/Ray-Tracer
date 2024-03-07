#include <iostream>
#include "lodepng.h"

using byte = unsigned char;

float lerp(float a, float b, float t) {
    return (1-t)*a + t*b;
}

struct RGB {
    byte r = 0;
    byte g = 0;
    byte b = 0;
    byte alpha = 255;
};

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int main() {
    int nx = 400;
    int ny = 200;

    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    std::vector<byte> v;

    for(int j = ny - 1; j >= 0; j--) {
        for(int i = 0; i < nx; i++) {
            float r  = lerp(0, 255, float(i) / float(nx));
            float g = lerp(0, 255, float(j) / float(ny));
            float b = lerp(0, 255, 0.2);

            int ir = r;
            int ig = g;
            int ib = b;
            
            v.push_back(ir);
            v.push_back(ig);
            v.push_back(ib);
            v.push_back(255);

            //std::cout << ir << " " << ig << " " << ib << '\n';
        }
    }

    encodeOneStep("out.png", v, nx, ny);
}