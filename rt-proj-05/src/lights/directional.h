#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "../core/light.h"

namespace rt3 {

class DirectionalLight : public LightLi {
public:
  Vector3f lightDir;
  Point3f from;
  DirectionalHit bounds;
  DirectionalLight(const Color& c, const Vector3f& scl, const Vector3f& direction, Point3f& from, const DirectionalHit& bounds)
      : LightLi(c, scl), lightDir(direction), from(from), bounds(bounds){};

  virtual void preprocess(const Scene&) {};
  Vector3f normalize_light(const Vector3f& scl);
  tuple<Color, Vector3f, unique_ptr<VisibilityTester>> sample_Li(const shared_ptr<Surfel>& hit) override;
};

DirectionalLight* create_directional_light(const ParamSet& ps);

}  // namespace rt3

#endif