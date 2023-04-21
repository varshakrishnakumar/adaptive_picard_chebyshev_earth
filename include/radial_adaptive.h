#pragma once

//from C++ std libs
#include <iostream> 
#include <string>
#include <cstring>
#include <cmath>
#include <complex>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>

//from adaptive_picard_chebyshev_v4
#include "const.h"
#include "c_functions.h"
#include "radial_gravity.h"


void radial_adaptive(double* X, double tol, double deg, double* grav);
