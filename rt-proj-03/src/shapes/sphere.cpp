#include "sphere.h"
#include "../core/material.h"

namespace rt3 {
    bool Sphere::intersect(const Ray &r, shared_ptr<Surfel> &isect) const {
        return false;
        // TODO ? 
    }

    bool Sphere::intersect_p(const Ray& r) const {
        Vector3f oc = r.o - center;
        return (glm::dot(oc, r.d) * glm::dot(oc, r.d)) - (glm::dot(r.d,r.d) * glm::dot(oc, oc) - radius * radius) >= 0;
    }

    Sphere *create_sphere(const ParamSet &ps) {
    return new Sphere(
        retrieve(ps, "center", Point3f()),
        retrieve(ps, "radius", real_type(1))
    );
}
}