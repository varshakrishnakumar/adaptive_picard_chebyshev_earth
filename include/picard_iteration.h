/*
*  AUTHORS:          Robyn Woollands (robyn.woollands@gmail.com)
*  DATE WRITTEN:     Feb 2017
*  LAST MODIFIED:    Feb 2017
*  AFFILIATION:      Department of Aerospace Engineering, Texas A&M University, College Station, TX
*  DESCRIPTION:      Header file
*/

// #ifndef __PI__
// #define __PI__

// #include <stdio.h>
// #include <math.h>
// #include <complex.h>
// #include <string.h>
// #include <stdlib.h>

#pragma once
#include <iostream> 
#include <string>
#include <cmath>
#include <complex>
#include <cstdlib>
#include "const.h"

void picard_iteration(double* Xint, double* Vint, double* X, double* V, double* times, int N, int M, double deg, double deg_low, int hot, double tol, double* P1, double* P2, double* T1, double* T2, double* A, double* Feval, double* Alpha, double* Beta);

// #endif
