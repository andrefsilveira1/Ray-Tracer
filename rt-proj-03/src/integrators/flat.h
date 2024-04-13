#ifndef FLAT_INTEGRATOR_H
#define FLAT_INTEGRATOR_H

#include "../core/integrator.h"
#include "../core/camera.h"

namespace rt3 {

class FlatIntegrator : public Integrator {
public:
    FlatIntegrator(std::shared_ptr<const Camera> cam) : FlatIntegrator(cam) {}

    Color Li(const Ray& ray, const Scene& scene) const override;
};

} // namespace rt3

#endif // FLAT_INTEGRATOR_H
