#ifndef FLAT_INTEGRATOR_H
#define FLAT_INTEGRATOR_H

#include "integrator.h"
#include "camera.h"

namespace rt3 {

class SamplerIntegrator : public Integrator {
public:
    SamplerIntegrator(std::shared_ptr<const Camera> cam) : camera(cam) {}
    virtual ~SamplerIntegrator() {}

    virtual Color Li(const Ray& ray, const Scene& scene) const = 0;
    virtual void render(const Scene& scene) {}
    virtual void preprocess(const Scene& scene) {}

protected:
    std::shared_ptr<const Camera> camera;
};

} // namespace rt3

#endif // FLAT_INTEGRATOR_H
