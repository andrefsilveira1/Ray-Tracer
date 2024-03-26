#ifndef ORTOGRAPHIC_H
#define ORTOGRAPHIC_H

#include "../core/camera.h"

namespace rt3 {

class OrthographicCamera : public Camera {
    // ...
};

OrthographicCamera* create_orthographic_camera(
    const ParamSet& ps_camera,
    const ParamSet& ps_look_at, unique_ptr<Film>&& the_film
);

};

#endif