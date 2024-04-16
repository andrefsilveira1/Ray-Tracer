#ifndef SCENE_H
#define SCENE_H

#include "integrator.h"
#include "camera.h"
#include "background.h"
#include "rt3.h"
#include "background.h"
#include "primitive.h"

namespace rt3 {
class Scene {
    public:
        //std::vector<shared_ptr<Light>> lights; // list of lights
        std::unique_ptr< Background > background; // The background object.
        std::shared_ptr<Primitive> primitive; // The scene graph of objects, acceleration structure.

        Scene( std::shared_ptr<Primitive> &&prim, std::unique_ptr< Background > &&bkg)
             : background(std::move(bkg)), primitive(std::move(prim))
        {/* empty */}

        ~Scene() = default;
        /// Determines the intersection info; return true if there is an intersection.
        bool intersect( const Ray& r, std::shared_ptr<Surfel> &isect) const;
        /*! A faster version that only determines whether there is an intersection or not;
         * it doesn't calculate the intersection info.
         */
        bool intersect_p( const Ray& r ) const;
};

} // namespace rt3

#endif // SCENE_H


