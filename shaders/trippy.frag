#version 330
precision mediump float;
#define PI 3.1415926535897932384626433832795
 
uniform float u_time;
uniform vec2 u_k;
varying vec2 v_coords;


vec3 set_color(float v){

    float  r =  float(sin((v * PI)));
    float  g =  float(sin(v*PI + 2.0 * PI / 3.0));
    float  b =  float(sin(v*PI + 2.0 * PI / 3.0));

    return vec3(1.0);
}
 
void main() {
    float v = 0.0;
    vec2 c = v_coords * u_k - u_k/2.0;
    v += sin((c.x+u_time));
    v += sin((c.y+u_time)/2.0);
    v += sin((c.x+c.y+u_time)/2.0);
    c += u_k/2.0 * vec2(sin(u_time/3.0), cos(u_time/2.0));
    v += sin(sqrt(c.x*c.x+c.y*c.y+1.0)+u_time);
    v = v/2.0;

    

    gl_FragColor = vec4(set_color(v), 1.0);




    //gl_FragColor = vec4(0.2667, 0.1922, 0.1922, 1.0);
}