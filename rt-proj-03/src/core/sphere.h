#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"
#include "Material.h"

namespace rt3 {
    class Sphere : public {
        public:
            Point3f center;
            float r;
            std::shared_ptr<FlatMaterial> material;

            Sphere(const Point3f& center, float r, const std::shared_ptr<FlatMaterial>& material);
            virtual ~Sphere() override;

            virtual bool intersect(const Ray& r, Surfel* sf) const override;
            virtual bool intersect_p(const Ray& r) const override; 
        
    }
}

#endif