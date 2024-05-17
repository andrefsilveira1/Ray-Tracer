#ifndef DIRECTIONAL_HIT_H
#define DIRECTIONAL_HIT_H 

#include "../core/rt3.h"
#include "../core/ray.h"
#include "../core/surfel.h"

namespace rt3 {

class DirectionalHit {
public:
    Point3f low, high; // Low represents the point with minimum x, y, and z. High the maximum x, y, and z.

    DirectionalHit() : low(Point3f(std::numeric_limits<float>::infinity())), high(Point3f(-std::numeric_limits<float>::infinity())) {}
    DirectionalHit(const Point3f& l, const Point3f& h) : low(l), high(h) {}

    bool intersect(const Ray& r, float *t_hit, Surfel *sf) const {
        float t_min = (low.x - r.o.x) / r.d.x;
        float t_max = (high.x - r.o.x) / r.d.x;
        if (t_min > t_max) std::swap(t_min, t_max);

        float ty_min = (low.y - r.o.y) / r.d.y;
        float ty_max = (high.y - r.o.y) / r.d.y;
        if (ty_min > ty_max) std::swap(ty_min, ty_max);

        if ((t_min > ty_max) || (ty_min > t_max))
            return false;

        if (ty_min > t_min)
            t_min = ty_min;
        if (ty_max < t_max)
            t_max = ty_max;

        float tz_min = (low.z - r.o.z) / r.d.z;
        float tz_max = (high.z - r.o.z) / r.d.z;
        if (tz_min > tz_max) std::swap(tz_min, tz_max);

        if ((t_min > tz_max) || (tz_min > t_max))
            return false;

        if (tz_min > t_min)
            t_min = tz_min;
        if (tz_max < t_max)
            t_max = tz_max;

        *t_hit = t_min;
        sf->p = r(t_min);
        return true;
    }

    bool intersect_p(const Ray& r) const {
        float t;
        Surfel sf;
        return intersect(r, &t, &sf);
    }
};

} // namespace rt3

#endif // DIRECTIONAL_HIT_H
