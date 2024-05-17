#include "directional.h"

namespace rt3 {

tuple<Color, Vector3f, unique_ptr<VisibilityTester>> DirectionalLight::sample_Li(const shared_ptr<Surfel>& hit) {
    Vector3f lightDirection = to - from; // Calculate the light dir. Should I put this as negative ?
    lightDirection = glm::normalize(lightDirection);

    shared_ptr<Surfel> lightSurfel = make_shared<Surfel>(
        to, 
        Vector3f(),
        lightDirection,
        std::numeric_limits<float>::infinity() // This really should be infinity or from light source ?
    );

    unique_ptr<VisibilityTester> visTester = std::make_unique<VisibilityTester>(hit, lightSurfel);

    return std::make_tuple(color_int, lightDirection, std::move(visTester));

}

DirectionalLight* create_directional_light(const ParamSet& ps) {
    return new DirectionalLight(
        retrieve(ps, "L", Color()),
        retrieve(ps, "scale", Vector3f()),
        retrieve(ps, "from", Point3f()),
        retrieve(ps, "to", Point3f())
    );
}

Vector3f DirectionalLight::normalize_light(const Vector3f& scl) {
    return glm::normalize(-scl); // Maybe should replace the normalize lightDirection from sample_Li
}

} // namespace rt3
