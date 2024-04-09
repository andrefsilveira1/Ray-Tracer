#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glm/glm.hpp>

class Material {
public:
    // Implement type ?

    Material(const glm::vec3& color): rgb_color(color){}


    glm::vec3 getColor() const {
        return rgb_color;
    }

private:
    glm::vec3 rgb_color;
};

#endif // MATERIAL_H
