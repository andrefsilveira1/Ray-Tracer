#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.h"
#include "surfel.h"
#include "material.h"

namespace rt3 {

class Primitive {
	public:
		virtual ~Primitive();
		virtual bool intersect( const Ray& r, Surfel *sf ) const = 0;
		virtual bool intersect_p( const Ray& r ) const = 0;
		virtual const Color get_color(void) const = 0;

	private:
		std::shared_ptr<FlatMaterial> material;
};

} // namespace rt3

#endif // PRIMITIVE_H