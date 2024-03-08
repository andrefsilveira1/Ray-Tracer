#include "background.h"

BackgroundColor::BackgroundColor( const std::vector< RGBColor >& colors ) {
    corners[bl] = colors[bl];
    corners[tl] = colors[tl];
    corners[tr] = colors[tr];
    corners[br] = colors[br];
}

RGBColor BackgroundColor::lerp( const RGBColor &A, const RGBColor &B, float t ) const {
    return A*(1-t) + B*t;
}

RGBColor BackgroundColor::sampleUV( real_type u, real_type v ) const {
    RGBColor xb = lerp(corners[bl], corners[br], u);
    RGBColor xt = lerp(corners[tl], corners[tr], u);
    
    return lerp(xt, xb, v);
}