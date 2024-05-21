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

  virtual void preprocess(const Scene&) override {}

  Vector3f normalize_light(const Vector3f& dir) {
    return normalize(-dir);
  }
};

};  // namespace rt3

#endif