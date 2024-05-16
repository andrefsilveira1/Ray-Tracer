#include "directional.h"

namespace rt3 {

tuple<Color, Vector3f, unique_ptr<VisibilityTester>> DirectionalLight::sample_Li(
  const shared_ptr<Surfel>& hit) {}

DirectionalLight* create_directional_light(const ParamSet& ps) {
  return new DirectionalLight(retrieve(ps, "L", Color()),
                              retrieve(ps, "scale", Vector3f()),
                              retrieve(ps, "from", Vector3f()),
                              retrieve(ps, "to", Vector3f()));
}

Vector3f DirectionalLight::normalize_light(const Vector3f& scl) {
  Vector3f lightDir = normalize(-scl);

  return lightDir;
}

}  // namespace rt3