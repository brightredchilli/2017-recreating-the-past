//
//  EasingFunctions.cpp
//  murielcooper2
//
//  Created by Ying Quan Tan on 10/12/17.
//

#include "EasingFunctions.hpp"
#include "ofMain.h"

#define EPSILON 0.00001

//------------------------------------------------------------------
float function_CubicBezier (float x, float a, float b, float c, float d){
    float min_param_a = 0.0 + EPSILON;
    float max_param_a = 1.0 - EPSILON;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    float min_param_c = 0.0 + EPSILON;
    float max_param_c = 1.0 - EPSILON;
    float min_param_d = 0.0;
    float max_param_d = 1.0;

    a = ofClamp(a, min_param_a, max_param_a);
    b = ofClamp(b, min_param_b, max_param_b);
    c = ofClamp(c, min_param_c, max_param_c);
    d = ofClamp(d, min_param_d, max_param_d);
    
    //-------------------------------------------
    float y0a = 0.00; // initial y
    float x0a = 0.00; // initial x 
    float y1a = b;    // 1st influence y   
    float x1a = a;    // 1st influence x 
    float y2a = d;    // 2nd influence y
    float x2a = c;    // 2nd influence x
    float y3a = 1.00; // final y 
    float x3a = 1.00; // final x 
    
    float A =   x3a - 3*x2a + 3*x1a - x0a;
    float B = 3*x2a - 6*x1a + 3*x0a;
    float C = 3*x1a - 3*x0a;   
    float D =   x0a;
    
    float E =   y3a - 3*y2a + 3*y1a - y0a;    
    float F = 3*y2a - 6*y1a + 3*y0a;             
    float G = 3*y1a - 3*y0a;             
    float H =   y0a;
    
    // Solve for t given x (using Newton-Raphelson), then solve for y given t.
    // Assume for the first guess that t = x.
    float currentt = x;
    int nRefinementIterations = 5;
    for (int i=0; i<nRefinementIterations; i++){
        float currentx = xFromT (currentt, A,B,C,D); 
        float currentslope = slopeFromT (currentt, A,B,C);
        currentt -= (currentx - x)*(currentslope);
        currentt = ofClamp(currentt, 0,1.0);
    } 
    
    //------------
    float y = yFromT (currentt,  E,F,G,H);
    return y;
}


//==========================================================
float slopeFromT (float t, float A, float B, float C){
    float dtdx = 1.0/(3.0*A*t*t + 2.0*B*t + C); 
    return dtdx;
}
//==========================================================
float xFromT (float t, float A, float B, float C, float D){
    float x = A*(t*t*t) + B*(t*t) + C*t + D;
    return x;
}
//==========================================================
float yFromT (float t, float E, float F, float G, float H){
    float y = E*(t*t*t) + F*(t*t) + G*t + H;
    return y;
}

float function_QuadraticBezierStaircase (float x, float a, int n) {

    float aa = (a - 0.5);
    if (aa == 0) {
        return x;
    }

    float x0 = (floor (x*n))/ (float) n;
    float x1 = (ceil  (x*n))/ (float) n;
    float y0 = x0;
    float y1 = x1;

    float px = 0.5*(x0+x1) + aa/n;
    float py = 0.5*(x0+x1) - aa/n;

    float p0x = (x0 + px)/2.0;
    float p0y = (y0 + py)/2.0;
    float p1x = (x1 + px)/2.0;
    float p1y = (y1 + py)/2.0;


    float y = 0;
    float denom = (1.0/n)*0.5;

    if ((x <= p0x) && (x >= x0)) {
        // left side
        if (floor (x*n) <= 0){
            y = ofMap(x, x0, px, y0, py);
        } else {

            if (abs(x - x0) < EPSILON){
                // problem when x == x0 !
            }

            float za = (x0  - (p1x - 1.0/n))/denom;
            float zb = (y0  - (p1y - 1.0/n))/denom;
            float zx = ( x  - (p1x - 1.0/n))/denom;
            float om2a = 1.0 - 2.0*za;

            float interior = max(0.f, za*za + om2a*zx);
            float t = (sqrt(interior) - za)/om2a;
            float zy = (1.0-2.0*zb)*(t*t) + (2*zb)*t;
            zy *= (p1y - p0y);
            zy += p1y; //(p1y - 1.0/n);
            if (x > x0){
                zy -= 1.0/n;
            }
            y = zy;
        }
    }

    else if ((x >= p1x) && (x <= x1)) {
        // right side
        if (ceil  (x*n) >= n) {
            y = ofMap(x, px, x1, py, y1);
        }
        else {
            if (abs(x - x1) < EPSILON){
                // problem when x == x1 !
            }

            float za = (x1 - p1x)/denom;
            float zb = (y1 - p1y)/denom;
            float zx = ( x - p1x)/denom;
            if (za == 0.5) {
                za += EPSILON;
            }
            float om2a = 1.0 - 2.0*za;
            if (abs(om2a) < EPSILON) {
                om2a = ((om2a < 0) ? -1:1) * EPSILON;
            }

            float interior = max(0.f, za*za + om2a*zx);
            float t = (sqrt(interior) - za)/om2a;
            float zy = (1.0-2.0*zb)*(t*t) + (2*zb)*t;
            zy *= (p1y - p0y);
            zy += p1y;
            y = zy;
        }
    }

    else {
        // center
        float za = (px - p0x)/denom;
        float zb = (py - p0y)/denom;
        float zx = ( x - p0x)/denom;
        if (za == 0.5) {
            za += EPSILON;
        }
        float om2a = 1.0 - 2.0*za;
        float t = (sqrt(za*za + om2a*zx) - za)/om2a;
        float zy = (1.0-2.0*zb)*(t*t) + (2*zb)*t;
        zy *= (p1y - p0y);
        zy += p0y;
        y = zy;
    }
    return y;

}

float function_VariableStaircase (float x, float a, int n) {

    float aa = (a - 0.5);
    if (aa == 0) {
        return x;
    }

    float x0 = (floor (x*n))/ (float) n;
    float x1 = (ceil  (x*n))/ (float) n;
    float y0 = x0;
    float y1 = x1;

    float px = 0.5*(x0+x1) + aa/n;
    float py = 0.5*(x0+x1) - aa/n;

    float y = 0;
    if ((x < px) && (x > x0)) {
        y = ofMap(x, x0, px, y0, py);
    }
    else {
        y = ofMap(x, px, x1, py, y1);
    }

    return y;
}
