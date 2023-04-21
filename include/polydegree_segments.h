/*
*  AUTHORS:          Robyn Woollands (robyn.woollands@gmail.com)
*  DATE WRITTEN:     Feb 2017
*  LAST MODIFIED:    Feb 2017
*  AFFILIATION:      Department of Aerospace Engineering, Texas A&M University, College Station, TX
*  DESCRIPTION:      Header file
*/

// #ifndef __PDS__
// #define __PDS__
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
#include "rv2elm.h"
#include "FandG.h"
#include "c_functions.h"
#include "perigee_approx.h"
#include "radial_gravity.h"
#include "EGM2008.h"
#include "lsq_chebyshev_fit.h"
#include "matrix_loader.h"

// class polyDegree {
//     public:
//         void polydegree_segments(double* Period);
//     private:
//         double* r0;
//         double* v0;
//         double deg;
//         double tol;
//         double* Feval;
//         int* seg;
//         int* degree;
//         double* tp;

// };

void polydegree_segments( double* r0, double* v0, double deg, double tol, double* Feval, int* seg, int* degree, double* tp, double* Period );

// #endif
