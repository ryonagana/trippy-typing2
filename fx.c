#include "fx.h"


inline double fx_calc_dist(float x1, float y1, float x2, float y2){
    double x,y;
    x = x2 - x1;
    y = y2 - y1;
    return (double) sqrt( (x*x) + (y*y));
}

void Fx_LavaLamp(ColorPallette *p, int width, int height)
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

    f += 0.5;

}


ColorPallette Fx_FuzzyColors()
{
    ColorPallette p;
    int i;
    for(i = 0; i < 256; i++){
        p.r[i] = 255 - ceil(sin(M_PI * 2 * i  - 255) + 1) * 127;
        p.g[i] = ceil((sin(M_PI * 2 * i  / 127.0) + i)) * 64;
        p.b[i] = 255 - p.r[i];
    }


    return p;
}

void Fx_Plasma(int width, int height, float frame_counter)
{
    int x,y;



    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){


            double plasma = sin(fx_calc_dist(x + frame_counter,y, 128.0, 128.0) / 8.0) +
                            sin(fx_calc_dist(x,y,64.0,64.0) / 8.0) +
                            sin(fx_calc_dist(x, y + frame_counter / 7.0, 192.0, 64.0) / 7.0) +
                            sin(fx_calc_dist(x,y,192.0,100.0) / 8.0);

            int  res = ((int)4 + plasma) * 32;

            DrawPixel(x,y, (Color){ res, res * 2, 255 - res, 255});


        }
    }
}

ColorPallette Fx_PlasmaPallete()
{

}
