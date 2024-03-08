#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>
using std::vector;

#include "common.h"

class BackgroundColor {
  private:
    /// Each corner has a color associated with.
    RGBColor corners[4]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
    /// Corner indices.
    enum Corners_e {
      bl=0, //!< Bottom left corner.
      tl,   //!< Top left corner.
      tr,   //!< Top right corner.
      br    //!< Bottom right corner.
    };

    /// Return the linearly interpolated color in [A;B], based on the parameter \f$0\leq t \leq 1.\f$
  public:
    RGBColor lerp( const RGBColor &A, const RGBColor &B, float t ) const;
    BackgroundColor() = default;
    /// Ctro receives a list of four colors, for each corner.
    BackgroundColor( const vector< RGBColor >& colors );
    /// Dtro
    ~BackgroundColor() { };
    /// Sample and returns a color, based on the raster coordinate.
    RGBColor sampleUV( real_type u, real_type v ) const;
};

#endif