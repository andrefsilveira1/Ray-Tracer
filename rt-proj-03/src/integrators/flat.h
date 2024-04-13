#ifndef FLAT_INTEGRATOR_H
#define FLAT_INTEGRATOR_H

#include "../core/integrator.h"
#include "../core/camera.h"
#include "sampler.h"

namespace rt3 {

class FlatIntegrator : public SamplerIntegrator {
public:
    FlatIntegrator(std::shared_ptr<const Camera> cam) : SamplerIntegrator(cam) {}

    Color Li(const Ray& ray, const Scene& scene) const; // This should override later
};

} // namespace rt3

#endif // FLAT_INTEGRATOR_H
