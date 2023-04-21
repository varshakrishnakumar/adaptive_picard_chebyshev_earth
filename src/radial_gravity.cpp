/*
*  AUTHORS:          Robyn Woollands (robyn.woollands@gmail.com)
*  DATE WRITTEN:     May 2017
*  LAST MODIFIED:    May 2017
*  AFFILIATION:      Department of Aerospace Engineering, Texas A&M University, College Station, TX
*  DESCRIPTION:      Computes the required spherical harmonic gravity degree (up to 100) as a function of orbital radius
*
* INPUT:
*    X    -- Position vector
*    tol  -- Tolerance
*    deg  -- Gravity degree
*
* OUTPUTS:
*    grav -- Radially adapted gravity degree
*
* REFERENCES:
* 1. Probe, A., Macomber, B., Read, J., Woollands, R. and Junkins, J., "Radially Adaptive
*    Evaluation of the Spherical Harmonic Gravity Series for Numerical Orbit Propagation",
*    AAS/AIAA Space Flight Mechanics Meeting, Williamsburg, Virginia, 2015.
*/

// #include <math.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

//from C++ std libs
#include <iostream> 
#include <string>
#include <cstring>
#include <cmath>
#include <complex>
#include <cstdlib>

//from adaptive_picard_chebyshev_v4
#include "const.h"
#include "c_functions.h"

void radial_gravity(double* X, double tol, double deg, double* grav){

  // Numerically computed radial adaptove gravity surface (max deg = 100)
  // cols: [-2    -3    -4    -5    -6    -7    -8    -9   -10   -11   -12 -13   -14   -15]

  // The numbers below were determined in a simulation conducted by Brent Macomber and Austin Probe (2015).
  double grav_surf[1400] = {2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,    99,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,    99,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     9,    93,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     7,    86,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     7,    74,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     7,    69,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     7,    56,   100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     7,    45,    99,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     7,    39,    87,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     6,    33,    73,   100,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     6,    25,    61,    93,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     4,    22,    51,    80,   100,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     4,    18,    42,    66,    91,   100,   100,   100,   100,   100,   100,   100,
    2,     2,     3,    15,    35,    56,    76,    99,   100,   100,   100,   100,   100,   100,
    2,     2,     3,    13,    28,    49,    66,    83,   100,   100,   100,   100,   100,   100,
    2,     2,     3,    11,    25,    42,    56,    72,    87,   100,   100,   100,   100,   100,
    2,     2,     3,    11,    22,    35,    49,    62,    75,    88,   100,   100,   100,   100,
    2,     2,     2,    10,    18,    30,    42,    54,    64,    76,    88,   100,   100,   100,
    2,     2,     2,     9,    16,    25,    36,    47,    57,    68,    77,    87,    98,   100,
    2,     2,     2,     7,    14,    23,    32,    42,    51,    59,    69,    77,    87,    95,
    0,     2,     2,     7,    13,    20,    28,    36,    45,    53,    61,    69,    76,    84,
    0,     2,     2,     6,    11,    18,    25,    32,    40,    46,    54,    61,    69,    75,
    0,     2,     2,     5,    11,    16,    22,    28,    35,    42,    48,    55,    61,    68,
    0,     2,     2,     5,    10,    14,    20,    25,    31,    37,    43,    49,    55,    61,
    0,     2,     2,     4,     9,    13,    18,    23,    28,    34,    39,    45,    50,    55,
    0,     2,     2,     4,     8,    11,    16,    21,    25,    31,    35,    40,    45,    50,
    0,     2,     2,     3,     7,    11,    15,    19,    23,    28,    33,    37,    42,    46,
    0,     2,     2,     3,     7,    10,    13,    17,    22,    25,    30,    34,    38,    42,
    0,     2,     2,     3,     6,     9,    13,    16,    20,    23,    27,    31,    35,    39,
    0,     2,     2,     2,     5,     8,    11,    15,    18,    22,    25,    28,    33,    36,
    0,     2,     2,     2,     5,     8,    11,    14,    17,    20,    23,    26,    30,    33,
    0,     2,     2,     2,     4,     7,    10,    13,    16,    19,    22,    25,    28,    31,
    0,     2,     2,     2,     4,     7,     9,    11,    15,    17,    20,    23,    26,    29,
    0,     2,     2,     2,     4,     6,     9,    11,    14,    16,    19,    22,    25,    27,
    0,     0,     2,     2,     3,     6,     8,    11,    13,    15,    18,    21,    23,    25,
    0,     0,     2,     2,     3,     6,     8,    10,    12,    14,    17,    19,    22,    24,
    0,     0,     2,     2,     3,     5,     7,     9,    11,    14,    16,    18,    21,    23,
    0,     0,     2,     2,     3,     5,     7,     9,    11,    13,    15,    17,    20,    22,
    0,     0,     2,     2,     3,     4,     7,     8,    10,    13,    14,    17,    19,    21,
    0,     0,     2,     2,     2,     4,     6,     8,    10,    11,    14,    16,    18,    20,
    0,     0,     2,     2,     2,     4,     6,     8,    10,    11,    13,    15,    17,    19,
    0,     0,     2,     2,     2,     4,     6,     7,     9,    11,    13,    14,    16,    18,
    0,     0,     2,     2,     2,     4,     5,     7,     9,    10,    12,    14,    16,    17,
    0,     0,     2,     2,     2,     3,     5,     7,     8,    10,    11,    13,    15,    17,
    0,     0,     2,     2,     2,     3,     5,     6,     8,    10,    11,    13,    14,    16,
    0,     0,     2,     2,     2,     3,     5,     6,     8,     9,    11,    12,    14,    16,
    0,     0,     2,     2,     2,     3,     4,     6,     7,     9,    11,    12,    13,    15,
    0,     0,     0,     2,     2,     3,     4,     6,     7,     9,    10,    11,    13,    15,
    0,     0,     0,     2,     2,     3,     4,     6,     7,     8,    10,    11,    13,    14,
    0,     0,     0,     2,     2,     3,     4,     5,     7,     8,    10,    11,    12,    14,
    0,     0,     0,     2,     2,     2,     4,     5,     7,     8,     9,    11,    12,    13,
    0,     0,     0,     2,     2,     2,     4,     5,     6,     8,     9,    10,    11,    13,
    0,     0,     0,     2,     2,     2,     3,     5,     6,     7,     9,    10,    11,    13,
    0,     0,     0,     2,     2,     2,     3,     5,     6,     7,     9,    10,    11,    13,
    0,     0,     0,     2,     2,     2,     3,     5,     6,     7,     8,    10,    11,    12,
    0,     0,     0,     2,     2,     2,     3,     4,     6,     7,     8,     9,    11,    12,
    0,     0,     0,     2,     2,     2,     3,     4,     6,     7,     8,     9,    10,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     7,     8,     9,    10,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     7,     8,     9,    10,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     9,    10,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     9,    10,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,    10,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,    11,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,    10,
    0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,    10,
    0,     0,     0,     0,     2,     2,     3,     4,     5,     6,     7,     8,     9,    10,
    0,     0,     0,     0,     2,     2,     2,     3,     5,     6,     7,     8,     9,    10,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     6,     7,     8,     9,    10,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     6,     7,     8,     9,    10,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     7,     7,     9,    10,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     9,    10,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9,
    0,     0,     0,     0,     2,     2,     2,     3,     4,     5,     6,     7,     8,     9};

    // Radius corresponding to gravity surface
    // The numbers below were determined in a simulation conducted by Brent Macomber and Austin Probe (2015).
    double rcos[100] = {1.0157, 1.0157, 1.0157, 1.0158, 1.0159, 1.0161, 1.0166, 1.0173, 1.0184,
      1.0201, 1.0223, 1.0254, 1.0294, 1.0344, 1.0408, 1.0486, 1.0581, 1.0694, 1.0828,
      1.0984, 1.1166, 1.1374, 1.1612, 1.1882, 1.2185, 1.2524, 1.2900, 1.3317, 1.3775,
      1.4277, 1.4825, 1.5419, 1.6061, 1.6754, 1.7497, 1.8292, 1.9140, 2.0041, 2.0995,
      2.2004, 2.3066, 2.4181, 2.5350, 2.6570, 2.7842, 2.9165, 3.0536, 3.1954, 3.3417,
      3.4924, 3.6471, 3.8058, 3.9680, 4.1336, 4.3022, 4.4736, 4.6474, 4.8233, 5.0009,
      5.1800, 5.3601, 5.5409, 5.7221, 5.9033, 6.0841, 6.2642, 6.4433, 6.6209, 6.7967,
      6.9705, 7.1419, 7.3105, 7.4760, 7.6382, 7.7968, 7.9515, 8.1019, 8.2480, 8.3894,
      8.5260, 8.6574, 8.7836, 8.9043, 9.0193, 9.1286, 9.2319, 9.3291, 9.4201, 9.5047,
      9.5830, 9.6547, 9.7199, 9.7783, 9.8301, 9.8750, 9.9131, 9.9444, 9.9687, 9.9861,
      9.9965};

      // Determine column corresponding to tolerance
      double col;
      col = fabs(log10(tol)+1);

      // Compute radius & corresponding index
      int ind;
      double R;
      R = sqrt(pow(X[0],2) + pow(X[1],2) + pow(X[2],2))/DU;
      for (int j=0; j<100; j++){
        if (rcos[j] <= R){
          ind = j;
        }
      }
      // Compute gravity degree
      *grav = grav_surf[(ind-1)*14 + (int)col-1];
      if (*grav > deg){
        *grav = deg;
      }
    }
