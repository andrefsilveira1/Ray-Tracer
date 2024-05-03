#include "sphere.h"
#include "../core/material.h"

namespace rt3 {
    bool Sphere::intersect(const Ray &r, shared_ptr<Surfel> &isect) const {
        //std::cout << "oi???" << std::endl;
        Vector3f oc = (r.o - center);
        real_type A = glm::dot(r.d, r.d);
        real_type B = 2 * glm::dot(oc, r.d);
        real_type C = glm::dot(oc, oc) - (radius * radius);
        real_type delta = (B*B) - (4*A*C);

        if(delta >= 0){
            //std::cout << "delta >= 0" << std::endl;
            real_type t[2] = {
                (-B - (real_type)sqrt(delta)) / (2 * A),
                (-B + (real_type)sqrt(delta)) / (2 * A),
            };
            if(t[0] > t[1]) std::swap(t[0], t[1]);

            Point3f contact = r(t[0]);
            Vector3f normal = glm::normalize(contact - center);

            isect = shared_ptr<Surfel>(new Surfel(
                contact,
                normal,
                -r.d,
                t[0]
            ));

            return true;
        }else{
            //std::cout << "delta < 0" << std::endl;
            return false;
        }
    }

    bool Sphere::intersect_p(const Ray& r, real_type maxT) const {
        Vector3f oc = (r.o - center);

        real_type A = glm::dot(r.d, r.d);
        real_type B = 2 * glm::dot(oc, r.d);
        real_type C = glm::dot(oc, oc) - radius * radius;

        real_type delta = B * B - 4 * A * C;
        if(delta >= -0.0001){
            real_type t[2] = {
                (-B - (real_type)sqrt(delta)) / (2 * A),
                (-B + (real_type)sqrt(delta)) / (2 * A),
            };
            if(t[0] > t[1]) std::swap(t[0], t[1]);
            if(t[0] > 0) return t[0] < maxT;
            else if(t[1] > 0) return t[1] < maxT;
            else return false;
        }else return false;
    }

    Sphere *create_sphere(const ParamSet &ps) {
        return new Sphere(
            retrieve(ps, "center", Point3f()),
            retrieve(ps, "radius", real_type(1))
        );
    }
}