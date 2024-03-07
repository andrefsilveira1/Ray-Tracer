#include "background.h"

BackgroundColor::BackgroundColor( const std::vector< RGBColor >& colors ) {
    for(int i = 0; i < 4; i++) {
        corners[i] = colors[i];
    }
}