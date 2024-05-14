#include "ping_pong.h"

#include "../materials/ping_pong.h"
#include "../lights/ambient.h"

namespace rt3{

Vector3f calc_h_vec(const Vector3f &viewDir, const Vector3f &lightDir){
    auto h = viewDir + lightDir;
    return -glm::normalize(h);
}

optional<Color> PingPongIntegrator::Li(const Ray& ray, const unique_ptr<Scene>& scene) const {
    return recursiveLi(ray, scene, 1);
}

optional<Color> PingPongIntegrator::recursiveLi(const Ray& ray, const unique_ptr<Scene>& scene, int currRecurStep) const{
    shared_ptr<Surfel> isect; // Intersection information.  
    if (!scene->intersect(ray, isect)) {
        return {};
    }else{
        shared_ptr<PingPongMaterial> material = std::dynamic_pointer_cast<PingPongMaterial>(isect->primitive->get_material());

        Color color;
        for(auto &light : scene->lights){
            if(typeid(*light) == typeid(AmbientLight)){
                color = color + light->color_int * material->ambient;
            }else{
                shared_ptr<LightLi> new_light = std::dynamic_pointer_cast<LightLi>(light);

                auto [lightColor, lightDir, visTester] = new_light->sample_Li(isect);


                if(visTester->unoccluded(scene)){ // 
                    // difuse
                    {
                        real_type coef = std::max(real_type(0), glm::dot(isect->n, (-lightDir)));
                        Color diffuseContrib = material->diffuse * lightColor * coef;
                        
                        color = color + diffuseContrib;
                    }
                    
                    // specular
                    if(material->glossiness){
                        auto h = calc_h_vec(ray.d, lightDir);

                        real_type coef = std::max(real_type(0), glm::dot(isect->n, h));
                        coef = pow(coef, material->glossiness);
                        Color specularContrib = material->specular * lightColor * coef;
                    
                        color = color + specularContrib;
                    }
                } /* else {
                    color = {1, 1, 1};
                }*/
            }
        }

        if(currRecurStep < max_depth){
            Vector3f newDir = glm::normalize((ray.d + (isect->n * (-2 * glm::dot(ray.d, isect->n)))));
            optional<Color> mayb_color = recursiveLi(Ray(isect->p + newDir, newDir), scene, currRecurStep + 1);
            if(mayb_color.has_value()) {
                color = color + material->mirror * mayb_color.value();
            } 
        }

        return color;
    }
}

PingPongIntegrator* create_ping_pong_integrator(const ParamSet & ps_integrator, unique_ptr<Camera> &&camera){
    return new PingPongIntegrator(
        std::move(camera),
        retrieve(ps_integrator, "depth", int(1))
    );
}


}