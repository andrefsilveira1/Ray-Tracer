#ifndef RAY_H
#define RAY_H

#include "rt3.h"
#include "rt3-base.h"

namespace rt3 {

using rt3::Point3f;
using rt3::Vector3f;

class Ray {
    public:
        Ray (const Point3f& o, const Vector3f& d,
            real_type start=0, real_type end=INFINITY) : o{o}, d{d},
            t_min{start}, t_max{end} {/*empty*/}
        Ray() : t_min{0.f}, t_max{INFINITY}{/*empty*/}
    private:
        Point3f o; //!< origin
        Vector3f d; //!< direction
        mutable real_type t_min, t_max; //!< parameters
        // ... the methods goes here
        Point3f operator()(real_type t) const { return o + d * t; }
};

};
//Ray r{ Point3{0,0,0}, Vector3{3,2,-4} }; // creating an infinity ray.
//float t{2.3};                            // a parameter for the ray.
//Point3 p = r( t );                       // overloading operator()(), so that it returns o + t*d.

#endif