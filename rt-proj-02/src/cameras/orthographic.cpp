#include "orthographic.h"


namespace rt3 {

OrthographicCamera::OrthographicCamera
    (std::unique_ptr<Film> && f, Point3f lf, Point3f la, Vector3f up, ScreenWindow sw): 
    Camera(std::move(f), lf, la, up, sw) {}


Ray OrthographicCamera::generate_ray(int i, int j) {
    auto [u2,v2] = get_uv(i,j);
    Vector3f dir = w; // Expendable
    return Ray{e + (u * u2) + (v * v2), dir};
}

OrthographicCamera* create_orthographic_camera(
    const ParamSet& ps_camera,
    const ParamSet& ps_look_at, unique_ptr<Film>&& the_film
) {
    
    return new OrthographicCamera(
        std::move(the_film),
        retrieve( ps_lookat, "look_from",  Point3f({0.0, 0.1, 0.0})),
        retrieve( ps_lookat, "look_at",    Point3f({0.0, 0.1, 0.0})),
        retrieve( ps_lookat, "up",         Vector3f({0.0, 0.1, 0.0})),
    );
}

}