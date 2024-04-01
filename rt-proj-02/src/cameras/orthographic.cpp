#include "orthographic.h"


namespace rt3 {

OrthographicCamera::OrthographicCamera
    (std::unique_ptr<Film> && f, Point3f lf, Point3f la, Vector3f up, ScreenWindow sw): 
    Camera(std::move(f), lf, la, up, sw) {}


Ray OrthographicCamera::generate_ray(int i, int j) {
    auto [u2,v2] = get_uv(i,j);
    Vector3f dir = w; // Expendable
    return Ray{e + u * u + v * v, dir};
}

OrthographicCamera* create_orthographic_camera(
    const ParamSet& ps_camera,
    const ParamSet& ps_look_at, unique_ptr<Film>&& the_film
) {
    ScreenWindow sw;

    if(ps_camera.count("screen_window")) { // Try to retrieve screen window
        sw = retrieve(ps_camera, "screen_window", ScreenWindow());
    } else {
        if(ps_camera.count("fovy")) { // If it doesn't exists, infer with the fovy
            real_type fovy = retrieve(ps_camera, "fovy", real_type{});

            // crazy math
            real_type h = fabs(tan(fovy/2.0));
            real_type asp = the_film->aspect_ratio();
            sw = ScreenWindow(h * asp * -1, h * asp, -h, h);
        } else { // If fovy doesn't exists, we have an error
            RT3_ERROR("Could not infer Screen Window.");
        }
    }

    return new OrthographicCamera(
        std::move(the_film),
        retrieve( ps_lookat, "look_from",  Point3f({0.0, 0.1, 0.0})),
        retrieve( ps_lookat, "look_at",    Point3f({0.0, 0.1, 0.0})),
        retrieve( ps_lookat, "up",         Vector3f({0.0, 0.1, 0.0})),
        sw
    );
}

}