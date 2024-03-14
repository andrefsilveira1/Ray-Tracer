#include "background.h"

namespace rt3 {

Color BackgroundColor::lerp( const Color &A, const Color &B, float t ) const {
  return A*(1-t) + B*t;
}

/*!
 * Samples a color base on spherical interpolation of an image ou colored
 * background.
 *
 * @param pixel_ndc Pixel position in NDC space,  in \f$[0:1]\f$.
 * \return The interpolated color.
 */
Color BackgroundColor::sampleXYZ(const Point2f& pixel_ndc) const {
  Color xb = lerp(corners[bl], corners[br], pixel_ndc.x);
  Color xt = lerp(corners[bl], corners[br], pixel_ndc.x);
  RT3_MESSAGE("abacate");
  return lerp(xt, xb, pixel_ndc.y);
}

BackgroundColor* create_color_background(const ParamSet& ps) {
  Color bl = retrieve( ps, "bl", Color(0, 0, 0));
  Color tl = retrieve( ps, "tl", Color(0, 0, 0));
  Color tr = retrieve( ps, "tr", Color(0, 0, 0));
  Color br = retrieve( ps, "br", Color(0, 0, 0));

  return new BackgroundColor({bl, tl, tr, br});
}

}  // namespace rt3
