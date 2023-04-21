
// #ifndef _F_and_G_
// #define _F_and_G_

#pragma once 
// #include <stdio.h>
// #include <math.h>
// #include <complex.h>
// #include <string.h>
// #include <stdlib.h>

#include <iostream> 
#include <string>
#include <cmath>
#include <complex>
#include <cstdlib>
#include "const.h"

void FandG( const double* z0, double* zf, const double dt);

double newtonFandG( const double a, const double dt, const double rMag,
                    const double sig0, const double tol );

// #endif
