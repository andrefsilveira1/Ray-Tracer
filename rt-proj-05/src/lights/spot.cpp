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
    if (t < falloff) {
        float smothCriminal = (t - falloff) / (cutoff - falloff); // forgive me about this joke
        intensity = intensity * smothCriminal;
    }
    auto visTester = std::make_unique<VisibilityTester>(
      hit, std::make_shared<Surfel>(Surfel{ pos, Vector3f(0, 0, 0), Vector3f(0, 0, 0), 0.0f }));
    return std::make_tuple(intensity, lightDir, std::move(visTester));
  } else {
    Color ambientIndex = color_int * 0.1f;
    return std::make_tuple(ambientIndex, lightDir, nullptr);
  }
}

SpotLight* create_spot_light(const ParamSet& ps) {
    Point3f from = retrieve(ps, "from", Point3f{0, 0, 0});
    Point3f to = retrieve(ps, "to", Point3f{1, 1, 1});
    Vector3f dir = normalize(to - from);
    Color I = retrieve(ps, "I", Color{0.5, 0.5, 0.5});
    Vector3f scale = retrieve(ps, "scale", Vector3f{0, 0, 0});
    real_type cutoff = Radians(retrieve(ps, "cutoff", 30.F));
    real_type falloff = Radians(retrieve(ps, "falloff", 15.F));

    std::cout << "inside spot light ===>>" << std::endl;

    return new SpotLight(
        I,
        scale,
        from,
        dir, 
        cutoff,
        falloff
    );
}

}  // namespace rt3
