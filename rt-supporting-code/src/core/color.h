#ifndef COLOR_H
#define COLOR_H

#include <vector>
using std::vector;

using real_type = float;
using byte = unsigned char;

namespace rt3 {

class Color {
    public:
        real_type r;
        real_type g;
        real_type b;

        Color() {}
        Color(const vector<real_type> &v) {
            r = v[0];
            g = v[1];
            b = v[2];
        }
        Color(real_type mr, real_type mg, real_type mb) : r(mr), g(mg), b(mb) {}

        Color operator * (const real_type t) const;
        Color operator + (const Color c) const;

        static inline Color real_color(const vector<real_type> &v) {
            return Color(v);
        }

        static inline Color int_color(vector<real_type> &v) {
            for(int i = 0; i < 3; i++) v[i] /= 255.0;
            return real_color(v);
        }
};

}

#endif 