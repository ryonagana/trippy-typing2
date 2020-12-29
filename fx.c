#include "fx.h"

void Fx_Plasma(Plasma *p, int width, int height)
{
    int x,y;
    static double f = 0.0;

    for(y = 0; y < height; y++){
        for(x = 0;x < width; x++){
            float p1 = sin(x / 50.0 + f + y  / 200.0);
            float p2 = sqrt((sin(0.8 * f) * 160 - x + 160) * (sin(0.8 * f) * 160 - x + 160) + (cos(1.2 * f) * 100 - y + 100) * (cos(1.2 * f) * 100 - y + 100));
            p2 = sin(p2 / 50.0);
            float p3 = p1 + p2  / 2;

            int res = ceil(p3 + 1) * 127;

            DrawPixel(x,y, (Color){ (int)p->r[res], (int)p->g[res], (int)p->g[res], 255} );

        }
    }

    f += 0.1;

}


Plasma Fx_FuzzyColors()
{
    Plasma p;
    int i;
    for(i = 0; i < 256; i++){
        p.r[i] = 255 - ceil(sin(M_PI * 2 * i  - 255) + 1) * 127;
        p.g[i] = ceil((sin(M_PI * 2 * i  / 127.0) + i)) * 64;
        p.b[i] = 255 - p.r[i];
    }


    return p;
}
