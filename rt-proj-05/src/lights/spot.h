#ifndef SPOT_H
#define SPOT_H

#include "../core/light.h"
#include "hit.h"

namespace rt3 {

class SpotLight : public LightLi {
public:
  Point3f pos;
  Vector3f dir;
  real_type cutoff, falloff; // I considered that this will arrive as radians 

  SpotLight(const Color& c,
            const Vector3f& scl,
            const Point3f& pos,
            const Vector3f& dir,
            const real_type& cutoff,
            const real_type& falloff)
      : LightLi(c, scl), pos(pos), dir(dir), cutoff(cutoff), falloff(falloff) {};

  virtual void preprocess(const Scene&) override {}
  virtual tuple<Color, Vector3f, unique_ptr<VisibilityTester>> sample_Li(
    const shared_ptr<Surfel>& hit) override;
  Vector3f normalize_light(const Vector3f& dir);
  Color scaleColor(const Vector3f& vec);
};
  SpotLight* create_spot_light(const ParamSet& ps);

};  // namespace rt3

#endif