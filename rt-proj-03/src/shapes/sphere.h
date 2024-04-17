#ifndef SPHERE_H
#define SPHERE_H

#include "../core/shape.h"

namespace rt3 {

class Sphere : public Shape {
private:
    real_type bhaskara(const Ray &r, real_type &A, real_type &B) const {return 0.2;};
    bool getT(const Ray &r, real_type &t) const {return false;};
public:
    Point3f center;
    real_type radius;
 
    Sphere(Point3f ori, real_type r): center(ori), radius(r) {}

    ~Sphere(){}

    bool intersect_p(const Ray &r) const override;
    bool intersect(const Ray &r, shared_ptr<Surfel> &isect) const override;
};


Sphere *create_sphere(const ParamSet &ps);

}

#endif