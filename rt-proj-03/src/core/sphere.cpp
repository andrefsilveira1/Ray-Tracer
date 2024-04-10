#include "sphere.h"
#include "material.h"

namespace rt3 {
    Sphere::Sphere(const Point3f& center, float r, const std::shared_ptr<Material>& material)
    : center(center), r(r), material(material) {}

    Sphere::~Sphere() {}

    bool Sphere::intersect(const Ray& r, Surfel* sf) const {
        return (glm::dot(oc, r.d) * glm::dot(oc, r.d)) - (glm::dot(r.d,r.d) * glm::dot(oc, oc) - s.r*s.r) >= 0;
    }

    bool Sphere::intersect_p(const Ray& r) const {
        // TODO ?
    }

    const Material* Sphere::get_color() const {
        return material->color();
    }
}