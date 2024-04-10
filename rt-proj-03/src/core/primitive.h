#ifndef PRIMITIVE_H
#define PRIMITIVE_H

namespace rt3 {

class Primitive {
	public:
		virtual ~Primitive();
		virtual bool intersect( const Ray& r, Surfel *sf ) const = 0;
		virtual bool intersect_p( const Ray& r ) const = 0;
		virtual const Material * get_material(void) const = { return material; }
	private:
		std::shared_ptr<Material> material;
};
}

#endif