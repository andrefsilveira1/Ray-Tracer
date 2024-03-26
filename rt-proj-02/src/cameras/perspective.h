#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "../core/camera.h"

namespace rt3 {

class PerspectiveCamera : public Camera {
    // ...
};

PerspectiveCamera* create_perspective_camera(
    const ParamSet& ps_camera,
    const ParamSet& ps_look_at, unique_ptr<Film>&& the_film
);

};

#endif