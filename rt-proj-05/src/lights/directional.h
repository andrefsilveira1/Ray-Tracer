#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "../core/light.h"

namespace rt3 {

class DirectionalLight : public LightLi {
public:
  Vector3f from, to;
  DirectionalLight(const Color& c, const Vector3f& scl, const Vector3f& from, const Vector3f& to)
      : LightLi(c, scl), from(from), to(to){};
  virtual void preprocess(const Scene&) {};
  Vector3f normalize_light(const Vector3f& scl);
  tuple<Color, Vector3f, unique_ptr<VisibilityTester>> sample_Li(
    const shared_ptr<Surfel>& hit) override;
};

DirectionalLight* create_directional_light(const ParamSet& ps);

}  // namespace rt3

#endif