#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "../core/light.h"

namespace rt3{

class DirectionalLight : public Light{
public:
  DirectionalLight(const Color &c, const Vector3f &scl):Light(c, scl){};
  virtual void preprocess( const Scene & ){}; // Is this necessary ?
};

DirectionalLight* create_directional_light( const ParamSet &ps );
DirectionalLight* normalize_light(const Vector3f &scl);

}



#endif