#ifndef SPOT_H
#define SPOT_H

#include "../core/light.h"
#include "hit.h"

namespace rt3 {

class SpotLight : public LightLi {
public:
  Point3f pos;
  Vector3f dir;
  real_type cutoff;

  SpotLight(const Color& c,
            const Vector3f& scl,
            const Point3f& pos,
            const Vector3f& dir,
            float angle)
      : LightLi(c, scl), pos(pos), dir(normalize(dir)), cutoff(std::cos(angle)) {}

  virtual void preprocess(const Scene&) override {}
  tuple<Color, Vector3f, unique_ptr<VisibilityTester>> sample_Li(
    const shared_ptr<Surfel>& hit) override {}
  Vector3f normalize_light(const Vector3f& dir) {}
  SpotLight* create_spot_light(const ParamSet& ps) {}
  Color scaleColor(const Vector3f& vec) {}
};

};  // namespace rt3

#endif