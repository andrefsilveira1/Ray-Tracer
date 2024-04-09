#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glm/glm.hpp>
#include "color.h"
class Material {
public:
    // Implement type ?

    ~Material() = default;
    virtual Color color() const = 0;

};


#endif // MATERIAL_H
