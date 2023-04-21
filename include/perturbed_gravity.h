/*
*  AUTHORS:          Robyn Woollands (robyn.woollands@gmail.com)
*  DATE WRITTEN:     Feb 2017
*  LAST MODIFIED:    Feb 2017
*  AFFILIATION:      Department of Aerospace Engineering, Texas A&M University, College Station, TX
*  DESCRIPTION:      Header file
*/

// #ifndef __PERT__
// #define __PERT__
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

void perturbed_gravity(double t, double* Xo, double err, int ii, int N, double deg, double deg_low, int hot, double* G, double tol, int* itr, double* Feval);

// void Grav_Approx(double t, double* X, double* dX, double* Feval);

// void Grav_Full(double t, double* Xo, double* acc, double tol, double deg, double* Feval);
void Grav_Full(double t, double* Xo, double* acc, double tol, double deg, double* Feval, double deg_low, int grav_model);