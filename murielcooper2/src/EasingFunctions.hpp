//
//  EasingFunctions.hpp
//  murielcooper2
//
//  Created by Ying Quan Tan on 10/12/17.
//

#ifndef EasingFunctions_hpp
#define EasingFunctions_hpp

#include <stdio.h>

float function_SmoothStep (float x);
float function_SmootherStep (float x);
float function_AdjustableSigmaHalfGaussian (float x, float a);
float function_CubicBezier (float x, float a, float b, float c, float d);
float function_QuadraticBezierStaircase (float x, float a, int n);
float function_VariableStaircase (float x, float a, int n);
float function_DoubleEllipticSigmoid (float x);

// internal helper functions
float slopeFromT (float t, float A, float B, float C);
float xFromT (float t, float A, float B, float C, float D);
float yFromT (float t, float E, float F, float G, float H);

#endif /* EasingFunctions_hpp */
