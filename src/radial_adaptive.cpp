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
#include <numeric>

// //from adaptive_picard_chebyshev_v4
#include "const.h"
#include "c_functions.h"
#include "radial_adaptive.h"



//chebyshev polynomial of 9
//This function takes the matrix grav_surf generated from MATLAB as a string and outputs a readable vector appropriate for C++ compilation
// std::vector<double> load_grav(std::string input) {
//     // std::string input;
//     std::vector<double> outputmatrix;

//     std::string file = "grav_surf.csv";
//     int i = 0;
//     std::ifstream grav_surf(file); //open matrix csv 
//     if (grav_surf.is_open()) {
//         while (!grav_surf.eof()) {
//             getline(grav_surf, input, ',');
//             outputmatrix.push_back(std::stof(input));
//             i += 1;
//         }
//         grav_surf.close();
//     }
//     else {
//         std::cout<< "unable to open grav_surf file" << std::endl;
//     }

//     for (int j=0; j < i; j++) {
//         std::cout << outputmatrix[j] << std::endl;
//     }
//     return outputmatrix;

// }
// double dot_product(double vector_a[], double vector_b[]) {
//    int product = 0;
//    size_t size = vector_a.size();
//    for (int i = 0; i < size; i++) {
//        product = product + vector_a[i] * vector_b[i];
//    }
//    return product;
// }


void radial_adaptive(double* X, double tol, double deg, double* grav) {
    // std::vector<double> grav_surff = outputmatrix;
    double grav_surf[160] = {9, 15.77777778, 23.38888889, 31.44444444, 36, 38.61111111, 41.22222222, 44.05555556, 46.66666667, 49.5, 52.33333333, 55, 57.72222222, 60.44444444, 63.38888889, 66,
    -14, -27.501949, -42.47277293, -58.04487177, -65.59016733, -68.39789003, -70.82656006, -73.50263914, -76.21265237, -78.70044338, -81.33793398, -83.78713651, -86.53573822, -89.00299673, -91.69960832, -94.40962155,
    14, 27.34759506, 41.63065844, 55.90032019, 61.30789632, 63.07399264, 64.2136272, 65.80949142, 67.29424452, 68.36135646, 70.08886429, 71.58701903, 72.86295155, 74.28858367, 75.5259277, 77.01068081,
    -14, -27.11111111, -40.44444444, -53.33333333, -58, -58.55555556, -59.11111111, -59.66666667, -59.88888889, -60.55555556, -60.88888889, -61.33333333, -61.44444444, -61.88888889, -62.66666667, -62.88888889,
    14, 26.8210206, 39.16118609, 51.10889727, 54.95262819, 54.52841754, 54.61490319, 54.15210406, 53.57819382, 53.34474778, 53.12935771, 52.94790179, 52.54422365, 52.04283603, 51.84797847, 51.27406823,
    -14, -26.51231273, -38.00353158, -49.46956358, -52.41397417, -51.3630391, -50.55951309, -49.8876307, -48.98639523, -47.86293753, -47.02082304, -45.72713325, -44.99612987, -44.36283596, -43.20078978, -42.29955431,
    14, 26.22222222, 37.11111111, 48.22222222, 50.66666667, 49.22222222, 47.77777778, 46.11111111, 45, 43.66666667, 42, 40.66666667, 39.44444444, 37.88888889, 36.44444444, 35.33333333,
    -14, -25.98573827, -36.52369549, -47.15223132,-48.9958585, -47.23907087, -45.61392685, -43.60973015, -42.13428573, -40.43661909, -38.64124297, -37.15239691, -35.46813191, -33.63416731, -31.76626857, -30.29082414,
    14, 25.83138434, 36.20815546, 46.32411588, 48.07280882, 46.06425649, 44.17146961, 42.37173785, 40.46089499, 38.6272291, 36.44844467, 34.79841251, 32.92615813, 31.33524696, 29.29276049, 27.38191763,
    -7, -12.88888889, -18.05555556, -23, -24, -22.94444444, -21.88888889, -20.83333333, -19.77777778, -18.94444444, -18.11111111, -17, -16.05555556, -15.11111111, -14.16666667, -13.11111111};
    auto grav_vec = *grav;
    if (*grav = 1) {
        double col = std::abs(-std::log10((tol) + 1));
        double normR = std::norm(*X);
        std::vector<double> grav_col; 
        for (unsigned int i = 0; i < 160; i++) {
            if (i % 16 == 0)

            {
                grav_col.push_back(grav_surf[i]);
            }

        }
        size_t size = grav_col.size();
        double tau1=-1+(2)/(8-1.02)*(normR-1.02);
        double T1[10];
        double value;
        for (unsigned int i = 0; i < size; i++) {
            T1[i] = cos((i-1)*acos(tau1));
            value += T1[i] * grav_col[i];
        }
        
        grav_vec = ceil(value);

        if (grav_vec > deg) {
            grav_vec = deg;
        }
        else if (grav_vec < 2) {
            grav_vec = 2;
        }        
    }
    else if (*grav == 0) {
        grav_vec = deg;
    }
}
