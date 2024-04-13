#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "color.h"
#include "scene.h"
namespace rt3 {

class Integrator {
	public:
		virtual ~Integrator();
		// virtual void render( const Scene& scene ) =0; Is this necessary ?
};

}

#endif // INTEGRATOR_H