#include "color.h"

namespace rt3 {

Color Color::operator * (const real_type t) const { 
    return {(r*t), (g*t), (b*t)}; 
}

Color Color::operator * (const Color &x) const { 
    return {(r*x.r), (g*x.g), (b*x.b)}; 
}


Color Color::operator + (const Color c) const { 
    return {(r+c.r), (g+c.g), (b+c.b)}; 
}

}