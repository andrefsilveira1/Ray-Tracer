#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "../core/light.h"

namespace rt3{

class DirectionalLight : public Light{
public:
  DirectionalLight(const Color &c, const Vector3f &scl):Light(c, scl){};
  virtual void preprocess( const Scene & ){};
  Vector3f normalize_light(const Vector3f &scl);

};

DirectionalLight* create_directional_light( const ParamSet &ps );

}



#endif