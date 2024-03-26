#include "Ray.h"
#include "rt3.h"
#include "rt3-base.h"
#include <cmath>

Ray::Ray(const Point3f& o, const Vector3f& d, real_type start, real_type end)
    : o{o}, d{d}, t_min{start}, t_max{end} {}

Ray::Ray(): t_min{0.f}, t_max{INFINITY} {} // Check infinity properties ?


Point3f Ray::operator() (real_type t) const {
    return o + d * t;
}

void Ray::norm() { // Refactor for normalize from glm 
    real_type t = d.length() // Check vector3f
    if (t == 0) {
        std::cout << "--> The vector provided it is unsuitable (zero length)"
        return 
    }

    d = d / t;

}

