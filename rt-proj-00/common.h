#ifndef COMMON_H
#define COMMON_H

using byte = unsigned char;
using real_type = float;

/// RGBColor struct 
struct RGBColor {
    byte r = 0;
    byte g = 0;
    byte b = 0;

    RGBColor() {}
    RGBColor(byte mr, byte mg, byte mb) : r(mr), g(mg), b(mb) {}

    RGBColor operator * (const real_type t) const { return {(byte)(r*t), (byte)(g*t), (byte)(b*t)}; }
    RGBColor operator + (const RGBColor c) const { return {(byte)(r+c.r), (byte)(g+c.g), (byte)(b+c.b)}; }
};

#endif