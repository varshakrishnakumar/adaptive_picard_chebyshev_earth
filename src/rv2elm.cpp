/*
*  AUTHORS:          Robyn Woollands (robyn.woollands@gmail.com)
*  DATE WRITTEN:     Feb 2016
*  LAST MODIFIED:    Feb 2016
*  AFFILIATION:      Department of Aerospace Engineering, Texas A&M University, College Station, TX
*  DESCRIPTION:      Convert r & v to orbital elements
*
* INPUT:
*    r     -- Initial position vector (km)
*    v     -- Initial velocity vector (km/s)
*    tol   -- Integration Time (sec)
*
* OUTPUTS:
*    elm   -- Keplerian orbit elements (p,a,e,inc,Om,w,f,E,M,s)
*
*    WHERE: p  -- Semilatus Rectum (km)
*           a  -- Semimajor Axis (km)
*           e  -- Eccentricity
*           i  -- Inclination (rad)
*           Om -- Right Ascension of Ascending Node (rad)
*           w  -- Argument of Perigee (rad)
*           f  -- True Anomaly (rad)
*           E  -- Eccentric Anomaly (rad)
*           M  -- Mean Anomaly (rad)
*           s  -- Special case location of perigee (rad)
*                    -- Longitude of Perigee
*                    -- Argument of Latitude
*                    -- True Longitude
*
* REFERENCES:
* Vallado (p. 125 , Algorithm 9)
*
* COMMENTS:
*
*/

#include "rv2elm.h"
#include "adaptive_picard_chebyshev.h"
#include "c_functions.h"

void rv2elm(double* r, double* v, double tol, double* elm){

  // Position & Velocity Magnitudes
  double *ra;
  ra = r;

  double *ve;
  ve = v;

  double R, V;
  // printf("r %f\n", ra[0]);
  // std::cout<< ra[0] << std::endl;
  R = sqrt(ra[0]*ra[0] + ra[1]*ra[1] + ra[2]*ra[2]);
  V = sqrt(ve[0]*ve[0] + ve[1]*ve[1] + ve[2]*ve[2]);
  // printf("R %f\n", R);
  // printf("V %f\n", V);

  // Angular Momentum Vector
  double H;
  double h[3] = {0.0};
  cross_product_3D(ra,ve,h);
  H = sqrt(h[0]*h[0] + h[1]*h[1] + h[2]*h[2]);
  // printf("H %f\n", H);
  // Line of Nodes Vector
  double nvec[3] = {0.0};
  double vert[3] = {0.0};
  double n;
  vert[0] = 0.0;
  vert[1] = 0.0;
  vert[2] = 1.0;
  cross_product_3D(vert,h,nvec);
  n = sqrt(nvec[0]*nvec[0] + nvec[1]*nvec[1] + nvec[2]*nvec[2]);
  // printf("n %f\n", n);

  // Eccentricity Vector
  double evec[3] = {0.0};
  double rv, e;
  rv = ra[0]*ve[0] + ra[1]*ve[1] + ra[2]*ve[2];
  for (int i=0; i<=2; i++){
    evec[i] = 1/C_MU*((pow(V,2) - C_MU/R)*ra[i] - rv*ve[i]);
  }
  e = sqrt(evec[0]*evec[0] + evec[1]*evec[1] + evec[2]*evec[2]);

  // printf("e %f\n", e);


  // Energy
  double xi;
  xi      = (pow(V,2))/2 - C_MU/R;
  // printf("xi %f\n", xi);
  // Semimajor Axis (a) & Semillatus Rectum (p)
  double a, p;
  if (fabs(1-e) <= tol){
    a   = INFINITY;
    p   = (pow(H,2))/C_MU;
  }
  else if (fabs(1-e) > tol){
    a   = -C_MU/2/xi;
    p   = a * (1 - pow(e,2));
  }
  // printf("a %f\n", a);

  // Inclination
  double inc;
  inc     = acos(h[2]/H);
  // printf("inc %f\n", inc);
  // Right Ascension of Ascending Node
  double Om;
  if (fabs(inc) >= tol){
    Om      = acos(nvec[0]/n);
    if (nvec[2] < 0){
      Om = 2*C_PI - Om;
    }
  } else if (fabs(inc) < tol){
    Om = 0.0;
  }

  // printf("Om %f\n", Om);
  // Argument of Perigee
  double w;
  if (fabs(inc) >= tol){
    w = acos((nvec[0]*evec[0] + nvec[1]*evec[1] + nvec[2]*evec[2]) / n / e);
    if (evec[2] < 0){
      w = 2*C_PI - w;
    }
  } else if (fabs(inc) < tol){
    w = 0.0;
  }
  // printf("w %f\n", w);

  // True Anomaly
  double f;
  double temp;
  temp = (evec[0]*ra[0] + evec[1]*ra[1] + evec[2]*ra[2]) / R / e;
  if (fabs(temp-1.0) <= tol){
    f = 0.0;
  }
  else if (fabs(temp-1.0) > tol){
    f = acos(temp);
  }
  // f = acos((evec[0]*r[0] + evec[1]*r[1] + evec[2]*r[2]) / R / e);
  if (rv < 0){
    f = 2*C_PI - f;
  }
  // printf("f %f\n", f);
  // printf("temp %f\n", temp);

  // Mean Anomaly & Eccentric Anomaly
  double E, M;
  E = 2*atan2(sqrt(1-e)*tan(f/2),sqrt(1+e));
  if (E < 0){
    E = 2*C_PI + E;
  }
  M = E - e*sin(E);
  if (M < 0){
    M = 2*C_PI + M;
  }
  // printf("E %f\n", E);
  // printf("M %f\n", M);

  // Special Cases
  // Elliptical Equatorial (ascending node undefined)
  double s;
  if (inc < tol && e >= tol){
    s = acos(evec[0] / e);
    if (evec[1] < 0)
    s = 2*C_PI - s;   // Longitude of Perigee
  }
  // Circular Inclined (perigee undefined)
  else if (inc >= tol && e < tol){
    s = acos((nvec[0]*ra[0] + nvec[1]*ra[1] + nvec[2]*ra[2])/R/n);    // Argument of Latitude
    if (ra[2] < 0){
      s = 2*C_PI - s;
    }
    // Circular Equatorial (perigee & ascending node undefined)
    else if (inc < tol && e < tol){
      s = acos(ra[0]/R);
      if (ra[1] < 0){
        s = 2*C_PI - s;    // True Longitude
      }
    }
  }
  // printf("s %f\n", s);

  // OUTPUT
  elm[0] = p;
  elm[1] = a;
  elm[2] = e;
  elm[3] = inc;
  elm[4] = Om;
  elm[5] = w;
  elm[6] = f;
  elm[7] = E;
  elm[8] = M;
  elm[9] = s;


// // OUTPUT
// elm[0] = p;
// elm[1] = a;
// elm[2] = e;
// elm[3] = inc;
// elm[4] = Om;
// elm[5] = w;
// elm[6] = f;
// elm[7] = E;
// elm[8] = M;
// elm[9] = s;
// // printf("elm %f\n", elm[0]);
}
