#include "spot.h"
#include "directional.h"
#include "hit.h"

namespace rt3 {

Color vectorToColor(const Vector3f& vec) { return Color(vec.x, vec.y, vec.z); }

tuple<Color, Vector3f, unique_ptr<VisibilityTester>> SpotLight::sample_Li(
  const shared_ptr<Surfel>& hit) {
  Vector3f lightDir = normalize(pos - hit->p);
  real_type t = dot(lightDir, dir);

  if (t > cutoff) {
    Color intensity = color_int * vectorToColor(scale);
    auto visTester = std::make_unique<VisibilityTester>(
      hit, std::make_shared<Surfel>(Surfel{ pos, Vector3f(0, 0, 0), Vector3f(0, 0, 0), 0.0f }));
    return std::make_tuple(intensity, lightDir, std::move(visTester));
  } else {
    Color ambientIndex = color_int * 0.1f;
    return std::make_tuple(ambientIndex, lightDir, nullptr);
  }
}

DirectionalLight* create_spot_light(const ParamSet& ps) {
  Point3f from = retrieve(ps, "from", Point3f());
  Point3f to = retrieve(ps, "to", Point3f());

  return new DirectionalLight(
    retrieve(ps, "L", Color()), retrieve(ps, "scale", Vector3f()), normalize(to - from), from);
}

Vector3f DirectionalLight::normalize_light(const Vector3f& d) { return glm::normalize(-d); }

}  // namespace rt3
