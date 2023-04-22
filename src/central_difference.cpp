#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <complex>
#include <ctime>
#include <cmath>
#include "EGM2008.h"
#include "central_difference.h"
#include "eci2ecef.h"

void central_difference(double time, double* X, double* PHI, int stm_deg, double* PHI_dot) {
    double h = 1e-3;
    double rp_temp[3], rm_temp[3];
    double fp[3], fm[3];
    double J_centdiff[3][3];

    for (int i = 0; i < 6; i++) {
        int index = i * 6;

        // Extract X and PHI values for this row
        for (int j = 0; j < 3; j++) {
            rp_temp[j] = X[index + j] + h;
            rm_temp[j] = X[index + j] - h;
        }
        for (int j = 0; j < 6; j++) {
            PHI_dot[index + j] = 0.0;
        }

        // Compute J_centdiff using central differences
        for (int n = 0; n < 3; n++) {
            for (int m = 0; m < 3; m++) {
                // Compute rp_temp and rm_temp for this partial
                rp_temp[n] = X[index + n] + h;
                rm_temp[n] = X[index + n] - h;

                // Compute gravity at rp_temp and rm_temp
                EGM2008(rp_temp, fp, stm_deg);
                EGM2008(rm_temp, fm, stm_deg);

                // Compute J_centdiff for this partial
                J_centdiff[n][m] = (fp[m] - fm[m]) / (2.0 * h);
            }
            // Reset rp_temp and rm_temp to their original values
            rp_temp[n] = X[index + n];
            rm_temp[n] = X[index + n];
        }

        // Compute PHI_dot for this row using J_centdiff
        for (int j = 0; j < 3; j++) {
            PHI_dot[index + j + 3] = J_centdiff[0][j];
            PHI_dot[index + j + 18] = J_centdiff[1][j];
            PHI_dot[index + j + 33] = J_centdiff[2][j];
        }
    }
}