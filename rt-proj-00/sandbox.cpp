#include <bits/stdc++.h>
#include "background.h"
#include "common.h"

using namespace std;

int main() {
    BackgroundColor bgc;
    
    RGBColor c = bgc.lerp({0,0,0}, {255, 255, 255}, 0.5);

    cout << (int) c.r << " " << (int) c.g << " " << (int) c.b << endl;
}

