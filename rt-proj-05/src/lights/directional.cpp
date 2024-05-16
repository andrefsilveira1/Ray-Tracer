#include "directional.h"

namespace rt3 {

    DirectionalLight* create_directional_light(const ParamSet &ps) {
        return new DirectionalLight(retrieve(ps, "L", Color()), retrieve(ps, "scale", Vector3f()));
    }

    Vector3f DirectionalLight::normalize_light(const Vector3f &scl) {
        Vector3f lightDir = normalize(-scl);

        return lightDir;
    }

}  // namespace rt3