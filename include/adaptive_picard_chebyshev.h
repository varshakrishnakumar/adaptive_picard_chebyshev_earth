/*
*  AUTHORS:          Robyn Woollands (robyn.woollands@gmail.com)
*  DATE WRITTEN:     Feb 2017
*  LAST MODIFIED:    Feb 2017
*  AFFILIATION:      Department of Aerospace Engineering, Texas A&M University, College Station, TX
*  DESCRIPTION:      Header file
*/

// #ifndef __APC__
// #define __APC__

#pragma once
// #include <stdio.h> --C
#include <iostream>
#include <string>
// #include <math.h> --C
#include <cmath>
// #include <complex.h> --C
#include <complex>
// #include <string.h> --C
// #include <stdlib.h> --C
#include <cstdlib>
#include "const.h"

void adaptive_picard_chebyshev(double* r0,double* v0, double* PHI0, double t0, double tf, double dt, double deg, double deg_low, double tol, int soln_size, double* Soln, double* Feval);

// #endif
