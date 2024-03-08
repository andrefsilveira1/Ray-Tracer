#include <iostream>
#include "lodepng.h"
#include "common.h"
#include "background.h"

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int main() {
    int nx = 400;
    int ny = 200;

    std::vector<RGBColor> corns;
    int r, g, b;
    std::cin >> r >> g >> b;
    corns.push_back({(byte) r, (byte) g, (byte) b});
    std::cin >> r >> g >> b;
    corns.push_back({(byte) r, (byte) g, (byte) b});
    std::cin >> r >> g >> b;
    corns.push_back({(byte) r, (byte) g, (byte) b});
    std::cin >> r >> g >> b;
    corns.push_back({(byte) r, (byte) g, (byte) b});

    BackgroundColor bgc(corns);
    std::vector<byte> vc;

    for(int j = 0; j < ny; j++) {
        for(int i = 0; i < nx; i++) {
            real_type u = float(i)/float(nx);
            real_type v = float(j)/float(ny);

            RGBColor c = bgc.sampleUV(u, v);

            vc.push_back(c.r);
            vc.push_back(c.g);
            vc.push_back(c.b);
            vc.push_back(255);
        }
    }

    encodeOneStep("out.png", vc, nx, ny);
}