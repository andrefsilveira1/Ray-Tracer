#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "rt3.h"
#include "ray.h"
#include "surfel.h"
#include "shape.h"
#include "material.h"

namespace rt3{

class Primitive {
public:
	Primitive() = default;
	virtual ~Primitive(){};
	virtual bool intersect( const Ray& r, std::shared_ptr<Surfel> &isect ) const = 0;
	virtual bool intersect_p( const Ray& r) const = 0;
};

/*class AggregatePrimitive : public Primitive {
public:
	vector<std::shared_ptr<Primitive>> primitives;

	AggregatePrimitive(vector<std::shared_ptr<Primitive>> prim) : primitives(prim) {}

	virtual ~AggregatePrimitive(){};

	virtual bool intersect( const Ray& r, std::shared_ptr<Surfel> &isect ) const = 0;
	virtual bool intersect_p( const Ray& r) const = 0;
};*/


class PrimList : public Primitive {
public:
	vector<std::shared_ptr<Primitive>> primitives;

	PrimList(vector<std::shared_ptr<Primitive>> prim):primitives(prim){}

	~PrimList(){};

	bool intersect_p( const Ray& r ) const override;

	bool intersect( const Ray& r, std::shared_ptr<Surfel> &isect ) const override;

};

class GeometricPrimitive : public Primitive{
public:
	std::shared_ptr<Material> material;
	std::unique_ptr<Shape> shape;

	GeometricPrimitive(std::shared_ptr<Material> mat, std::unique_ptr<Shape> &&s) {}

	~GeometricPrimitive(){};

	bool intersect_p( const Ray& r ) const override;

	bool intersect( const Ray& r, std::shared_ptr<Surfel> &isect ) const override;

	std::shared_ptr<Material> get_material() const{  return material; }
};

} // namespace rt3



#endif