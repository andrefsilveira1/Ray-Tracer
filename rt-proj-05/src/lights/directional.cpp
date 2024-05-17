#include "directional.h"
#include "hit.h"

namespace rt3 {

tuple<Color, Vector3f, unique_ptr<VisibilityTester>> DirectionalLight::sample_Li(const shared_ptr<Surfel>& hit) {
    Vector3f lightDirection = glm::normalize(lightDir);
    Ray source(hit->p, -lightDirection);
    Point3f o = {0,0,0};
    shared_ptr<Surfel> lightSurfel = make_shared<Surfel>(
        from, 
        Vector3f(),
        lightDirection,
        std::numeric_limits<float>::infinity() // This really should be infinity or from light source ?
    );

    unique_ptr<VisibilityTester> visTester = std::make_unique<VisibilityTester>(hit, lightSurfel);

    return std::make_tuple(color_int, lightDirection, std::move(visTester));

}

DirectionalLight* create_directional_light(const ParamSet& ps) {
    Point3f from = retrieve(ps, "from", Point3f());
    Point3f to = retrieve(ps, "to", Point3f());

    return new DirectionalLight(
        retrieve(ps, "L", Color()),
        retrieve(ps, "scale", Vector3f()),
        normalize(to - from),
        from
    );
}

Vector3f DirectionalLight::normalize_light(const Vector3f& d) {
    return glm::normalize(-d); // Maybe should replace the normalize lightDirection from sample_Li
}

} // namespace rt3
