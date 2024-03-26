#include "camera.h"

namespace rt3 {

pair<real_type, real_type> Camera::get_uv(int i, int j) {
    real_type u = sw.l + sw.width() * (i + 0.5);
    u /= film->width();

    real_type v = sw.b + sw.height() * (j + 0.5);
    v /= film->height();

    return {u, v};
}

Camera::Camera(unique_ptr<Film> &_film, Point3f lf, Point3f la, Vector3f up, ScreenWindow _sw) 
: film(std::move(_film)), e(lf), sw(_sw)
{
    Vector3f gaze = lf - la;
    w = glm::normalize(gaze);

    u = glm::normalize(glm::cross(up, w));

    v = glm::normalize(glm::cross(w, u));
}

};
