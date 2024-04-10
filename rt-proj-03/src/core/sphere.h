#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include "material.h"

namespace rt3 {
    class Sphere : public Primitive {
        public:
            Point3f center;
            float radius;
            std::shared_ptr<FlatMaterial> material;

            Sphere(const Point3f& center, float r, const std::shared_ptr<FlatMaterial>& material);
            virtual ~Sphere() override;

            virtual bool intersect(const Ray& r, Surfel* sf) const override;
            virtual bool intersect_p(const Ray& r) const override; 
            virtual const Material* get_color() const override;
        
    };
}

#endif