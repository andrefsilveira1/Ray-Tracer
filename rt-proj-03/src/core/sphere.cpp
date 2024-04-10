#include "sphere.h"
#include "material.h"

namespace rt3 {
    Sphere::Sphere(const Point3f& center, float r, const std::shared_ptr<FlatMaterial>& material)
    : center(center), r(r), material(material) {}
}