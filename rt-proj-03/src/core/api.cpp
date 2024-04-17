#include "api.h"
#include "background.h"

#include <chrono>
#include <memory>
#include "color.h"
#include "../materials/flat.h"
#include "../integrators/flat.h"
#include "../integrators/normal_map.h"
#include "../shapes/sphere.h"

namespace rt3 {

// ***** TEST OF THE PREVIOUS PROJECT ******
/*
struct Sphere {
  Point3f center;
  Sphere(real_type x, real_type y, real_type z) {
    center.x = x;
    center.y = y;
    center.z = z;
  } 

  Sphere() {}

  real_type r = 0.4;
};

real_type delta(const Sphere &s, const Ray &r) {
  Vector3f oc = r.o - s.center;

  return (glm::dot(oc, r.d)*glm::dot(oc, r.d)) - (glm::dot(r.d,r.d) * glm::dot(oc, oc) - s.r*s.r);
}

bool intersect(const Sphere &s, const Ray &r) {
  return delta(s, r) >= 0;
}

// *****************************************

void render(Camera *camera, Background *bckg, RunningOptions &opt, vector<real_type> cw) {
  int w = camera->film->width();
  int h = camera->film->height();

  auto crop_window = opt.crop_window;

  if (cw[0] == 0 && cw[1] == 1 && cw[2] == 0 && cw[3] == 1) {
    if (crop_window[0][0] == 0 && crop_window[0][1] == 1 && crop_window[1][0] == 0 && crop_window[1][1] == 1) {
        std::cout << "--> Using default crop window." << std::endl;
        w = camera->film->width();
        h = camera->film->height();
    } else {
        std::cout << "--> Using crop window from flag." << std::endl;
        w = crop_window[1][1] - crop_window[1][0] + 1;
        h = crop_window[0][1] - crop_window[0][0] + 1;
    }
  } else {
      std::cout << "--> Using custom crop window." << std::endl;
      w = cw[1] - cw[0] + 1;
      h = cw[3] - cw[2] + 1;
  }


  vector<Sphere> ss;
  ss.push_back({-1, 0.5, 5}); 
  ss.push_back({1, -0.5, 8});
  ss.push_back({-1, -1.5, 3.5});

  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      Ray r = camera->generate_ray(i, j);


      //std::cout << "Ray r = " << r << std::endl;
      Color c = bckg->sampleXYZ({float(j)/float(w), float(i)/float(h)});
      for(Sphere s : ss) {
        if(intersect(s, r)) {
          c = {1, 0, 0};
          //std::cout << "inter(" << i << " " << j << ")";
        }
      }
       
      camera->film->add_sample({i,j}, c);

    }
  }
  camera->film->write_image();
}

*/

//=== API's static members declaration and initialization.
API::APIState API::curr_state = APIState::Uninitialized;
RunningOptions API::curr_run_opt;
std::unique_ptr<RenderOptions> API::render_opt;
vector<std::pair<ParamSet, shared_ptr<Material>>> API::global_primitives;
shared_ptr<Material> API::curr_material;
std::map<string, shared_ptr<Material>> API::named_materials;
// GraphicsState API::curr_GS;

// THESE FUNCTIONS ARE NEEDED ONLY IN THIS SOURCE FILE (NO HEADER NECESSARY)
// ˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇˇ

Film* API::make_film(const std::string& name, const ParamSet& ps) {
  std::cout << ">>> Inside API::make_film()\n";
  Film* film{ nullptr };
  film = create_film(ps);

  // Return the newly created film.
  return film;
}

Background* API::make_background(const std::string& name, const ParamSet& ps) {
  std::cout << ">>> Inside API::make_background()\n";
  Background* bkg{ nullptr };
  bkg = create_color_background(ps);

  // Return the newly created background.
  return bkg;
}

Camera* API::make_camera(const ParamSet &ps_camera, const ParamSet &ps_lookat, unique_ptr<Film> &&the_film) {
  std::cout << ">>> Inside API::make_camera()\n";
  Camera* cam{ nullptr };

  std::string type = retrieve(ps_camera, "type", std::string { "ortographic" });

  if(type == "orthographic"){
    cam = create_orthographic_camera(ps_camera, ps_lookat, std::move(the_film));
  }else if(type == "perspective"){
    cam = create_perspective_camera(ps_camera, ps_lookat, std::move(the_film));
  }

  // Return the newly created camera.
  return cam;
}

Material * API::make_material(const ParamSet &ps_material)
{
    std::cout << ">>> Inside API::make_material()\n";
    std::string type = retrieve(ps_material, "type", std::string{ "flat" });
    std::cout << ">>>> TYPE:" << type << std::endl;

    Material *material = nullptr;
    if(type == "flat"){
        material = create_flat_material(ps_material);
    } else {
        RT3_ERROR("Uknown material type.");
    }
    std::cout << "RETURNED" << std::endl;
    // Return the newly created material
    return material;
}

Integrator * API::make_integrator(const ParamSet &ps_integrator, unique_ptr<Camera> &&camera) {
  std::cout << ">>> Inside API::make_integrator() \n";
  std::string type = retrieve(ps_integrator, "type", std::string{ "flat" });
  Integrator *integrator = nullptr;
  if(type == "flat") {
    std::cout << "fazendo flat integrator" << std::endl;
    integrator = create_flat_integrator(std::move(camera));
  } else if(type == "normal_map") {
    std::cout << "fazendo normal integrator" << std::endl;
    integrator = create_normal_integrator(std::move(camera));
  } else {
    RT3_ERROR("Integrator type unknown.");
  }

  return integrator;
}

Shape * API::make_shape(const ParamSet &ps) {
  string type = retrieve(ps, "type", std::string{"sphere"});
  std::cout << ">>> Inside API::make_shape()\n";

  Shape *shape = nullptr;

  if(type == "sphere") {
    shape = create_sphere(ps);
  } else {
    RT3_ERROR("Unknown object type.");
  }

  return shape;
}

GeometricPrimitive * API::make_geometric_primitive(unique_ptr<Shape> &&shape, 
                                                   shared_ptr<Material> material) {

    std::cout << ">>> Inside API::make_geometric_primitive()\n";

    return new GeometricPrimitive(
        material,
        std::move(shape)
    );
}

// ˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆˆ
// END OF THE AUXILIARY FUNCTIONS
// =========================================================================

//=== API's public methods implementation
void API::init_engine(const RunningOptions& opt) {
  // Save running option sent from the main().
  curr_run_opt = opt;
  // Check current machine state.
  if (curr_state != APIState::Uninitialized) {
    RT3_ERROR("API::init_engine() has already been called! ");
  }
  // Set proper machine state
  curr_state = APIState::SetupBlock;
  // Preprare render infrastructure for a new scene.
  render_opt = std::make_unique<RenderOptions>();
  // Create a new initial GS
  // curr_GS = GraphicsState();
  RT3_MESSAGE("[1] Rendering engine initiated.\n");
}

void API::clean_up() {
  // Check for correct machine state
  if (curr_state == APIState::Uninitialized) {
    RT3_ERROR("API::clean_up() called before engine initialization.");
  } else if (curr_state == APIState::WorldBlock) {
    RT3_ERROR("API::clean_up() called inside world definition section.");
  }
  curr_state = APIState::Uninitialized;

  RT3_MESSAGE("[4] Rendering engine clean up concluded. Shutting down...\n");
}

void API::run() {
  // Try to load and parse the scene from a file.
  RT3_MESSAGE("[2] Beginning scene file parsing...\n");
  // Recall that the file name comes from the running option struct.
  parse(curr_run_opt.filename.c_str());
}

void API::world_begin() {
  VERIFY_SETUP_BLOCK("API::world_begin");  // check for correct machine state.
  curr_state = APIState::WorldBlock;       // correct machine state.
}

void API::world_end() {
  VERIFY_WORLD_BLOCK("API::world_end");
  // The scene has been properly set up and the scene has
  // already been parsed. It's time to render the scene.

  std::unique_ptr<Scene> the_scene;
  std::unique_ptr<Integrator> the_integrator;

  // MAKING THE SCENE
  std::unique_ptr<Background> the_background{ make_background(render_opt->bkg_type,
                                                              render_opt->bkg_ps) };

  vector<std::shared_ptr<Primitive>> primitives;

  for(auto [obj_ps, mat] : global_primitives) {
    unique_ptr<Shape> shape(make_shape(obj_ps));

    primitives.push_back(shared_ptr<Primitive>(make_geometric_primitive(std::move(shape), mat)));
  }

  unique_ptr<PrimList> prim_list = unique_ptr<PrimList>(new PrimList(std::move(primitives)));
  
  the_scene = make_unique<Scene>(std::move(prim_list), std::move(the_background));
  // MADE THE SCENE

  // MAKE THE INTEGRATOR -----------------------------------------------------------------------------------
  std::unique_ptr<Film> the_film{ 
                  make_film(render_opt->film_type, 
                            render_opt->film_ps) };

  std::unique_ptr<Camera> the_camera{ 
                  make_camera(render_opt->camera_ps, 
                              render_opt->lookat_ps, 
                              std::move(the_film)) };

  the_integrator = unique_ptr<Integrator>(make_integrator(render_opt->integrator_ps, std::move(the_camera)));
  // MADE THE INTEGRATOR -----------------------------------------------------------------------------------

  // Run only if we got film and background.
  if (the_integrator and the_scene) {
    RT3_MESSAGE("    Parsing scene successfuly done!\n");
    RT3_MESSAGE("[2] Starting ray tracing progress.\n");

    // Structure biding, c++17.
    /*auto res = the_camera->film->get_resolution();
    size_t w = res[0];
    size_t h = res[1];
    RT3_MESSAGE("    Image dimensions in pixels (W x H): " + std::to_string(w) + " x "
                + std::to_string(h) + ".\n");*/
    RT3_MESSAGE("    Ray tracing is usually a slow process, please be patient: \n");

    //================================================================================
    auto start = std::chrono::steady_clock::now();

    //std::vector<real_type> cw = retrieve(render_opt->film_ps, "crop_window", std::vector<real_type>{ 0, 1, 0, 1 });
    the_integrator->render(the_scene);  // TODO: This is the ray tracer's  main loop.
    auto end = std::chrono::steady_clock::now();
    //================================================================================
    auto diff = end - start;  // Store the time difference between start and end
    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    RT3_MESSAGE("    Time elapsed: " + std::to_string(diff_sec.count()) + " seconds ("
                + std::to_string(std::chrono::duration<double, std::milli>(diff).count())
                + " ms) \n");
  }
  // [4] Basic clean up
  curr_state = APIState::SetupBlock;  // correct machine state.
  reset_engine();
}

/// This api function is called when we need to re-render the *same* scene (i.e.
/// objects, lights, materials, etc) , maybe with different integrator, and
/// camera setup. Hard reset on the engine. User needs to setup all entities,
/// such as camera, integrator, accelerator, etc.
void API::reset_engine() {
  // curr_GS = GraphicsState();
  // This will delete all information on integrator, cameras, filters,
  // acceleration structures, etc., that has been set previously.
  render_opt = std::make_unique<RenderOptions>();
}

void API::background(const ParamSet& ps) {
  std::cout << ">>> Inside API::background()\n";
  VERIFY_WORLD_BLOCK("API::background");

  // retrieve type from ps.
  std::string type = retrieve(ps, "type", string{ "unknown" });
  render_opt->bkg_type = type;
  // Store current background object.
  render_opt->bkg_ps = ps;
}

void API::film(const ParamSet& ps) {
  std::cout << ">>> Inside API::film()\n";
  VERIFY_SETUP_BLOCK("API::film");

  // retrieve type from ps.
  std::string type = retrieve(ps, "type", string{ "unknown" });
  render_opt->film_type = type;
  render_opt->film_ps = ps;
}

void API::camera(const ParamSet& ps) {
  std::cout << ">>> Inside API::camera()\n";
  VERIFY_SETUP_BLOCK("API::camera");

  // retrieve type from ps.
  std::string type = retrieve(ps, "type", string{ "perspective" });
  render_opt->camera_type = type;
  render_opt->camera_ps = ps;
}

void API::lookat(const ParamSet& ps) {
  std::cout << ">>> Inside API::lookat()\n";
  VERIFY_SETUP_BLOCK("API::lookat");

  render_opt->lookat_ps = ps;
}

void API::make_named_material(const ParamSet &ps) {
  std::cout << ">>> Inside API::make_named_material()\n";
  VERIFY_SETUP_BLOCK("API::make_named_material");

  string material_name = retrieve(ps, "name", string());

  named_materials[material_name] = shared_ptr<Material>(make_material(ps));
}

void API::named_material(const ParamSet &ps) {
  std::cout << ">>> Inside API::named_material()\n";
  VERIFY_WORLD_BLOCK("API::named_material");

  string material_name = retrieve(ps, "name", string());

  curr_material = named_materials[material_name];
}

void API::material(const ParamSet &ps) {
  std::cout << ">>> Inside API::material()\n";
  VERIFY_WORLD_BLOCK("API::material");

  std::shared_ptr<Material> new_material(make_material(ps));

  curr_material = new_material;
}

void API::integrator(const ParamSet &ps) {
  std::cout << ">>> Inside API::integrator()\n";
  VERIFY_SETUP_BLOCK("API::integrator");

  render_opt->integrator_ps = ps;
}

void API::object( const ParamSet &ps ) {
  std::cout << ">>> Inside API::object()\n";
  VERIFY_WORLD_BLOCK("API::object");

  global_primitives.push_back({ps, curr_material});
}

}  // namespace rt3
