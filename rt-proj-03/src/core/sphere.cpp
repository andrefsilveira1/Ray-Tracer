#include "sphere.h"
#include "material.h"

namespace rt3 {
    Sphere::Sphere(const Point3f& center, float radius, const std::shared_ptr<FlatMaterial>& material)
    : center(center), radius(radius), material(material) {}

    Sphere::~Sphere() {}

    bool Sphere::intersect(const Ray& r, Surfel* sf) const {
        return false;
        // TODO ? 
    }

    bool Sphere::intersect_p(const Ray& r) const {
        Vector3f oc = r.o - center;
        return (glm::dot(oc, r.d) * glm::dot(oc, r.d)) - (glm::dot(r.d,r.d) * glm::dot(oc, oc) - radius * radius) >= 0;
    }

}