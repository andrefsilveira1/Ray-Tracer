#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

namespace rt3 {

class Material {
public:
    // Implement type ?

    virtual ~Material() = default;
    virtual Color color() const = 0;

};

class FlatMaterial : public Material {
    public:
        FlatMaterial(const Color& color) : received_color(color) {}

        Color color() const override {
            return received_color;
        }

    private:
        Color received_color;
};
}

#endif // MATERIAL_H
