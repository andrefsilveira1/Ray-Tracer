#include "flat.h"

namespace rt3 {
    FlatMaterial * create_flat_material( const ParamSet &ps ){
        return new FlatMaterial(
            retrieve(ps, "color", std::vector<real_type>{ 0, 0, 0, }) // I had to change this
        );
    }
}