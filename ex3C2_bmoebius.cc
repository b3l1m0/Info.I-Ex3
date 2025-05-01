// C++ program for Ex B: Lattice energy of LJ atoms in an FCC
/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 7.11.2024
Task 		    : C
Time required	: 2 hours
Program Description:
In this programm the total lattice energy of a crystal is computed based on the Lennard-Jones-Energy
between two atoms in a FCC crystal. The program is built similar to the program of ex3B as a way to
compare the impact of different changes in ex3C1 on the runtime.
All in all i think that i did a good job with computing this theory as i took care of the different
criterias and calculation parameters needed to calculate the lattice energy.

Short report:
The questions are answered in the program ex3C1.cc

Lattice Energy in kJ/mol
Ne: -2.44756
Ar: -8.22655
Kr: -11.0915
Xe: -15.842

*/
// INCLUDES
#include <iostream>
#include <iomanip>
#include <cmath>
// NAMESPACE
using namespace std;

// PROTOTYPES
bool GetInput(int& n, double& a, double& sig, double& eps);
double CalculateLatticeEnergy(int n, double a, double sig, double eps);
double CalculateDistance(int ix, int jx, int iy, int jy, int iz, int jz, double a);
double CalculateLJEnergy(double r, double sig, double eps);
void PrintResult(int n, double a, double sig, double eps, double ene);

// MAIN
int main() {
    // DECLARE VARIABLES
    int n;
    double a, sigma, epsilon, energy;
    // CALL FUNCTIONS
    GetInput(n, a, sigma, epsilon);
    energy = CalculateLatticeEnergy(n, a, sigma, epsilon);
    PrintResult(n, a, sigma, epsilon, energy);
    return 0;
}

// FUNCTION DEFINITIONS FOR THE 5 REQUIRED FUNCTIONS
bool GetInput(int& n, double& a, double& sig, double& eps) {
    cout << "# Please enter number of atoms in each direction: " << endl;
    cin >> n;
    cout << "# Please enter lattice parameter a in nm: " << endl;
    cin >> a;
    cout << "# Please enter LJ parameter sigma in nm: " << endl;
    cin >> sig;
    cout << "# Please enter LJ parameter epsilon in kJ/mol: " << endl;
    cin >> eps;
    return n > 0 && a > 0 && sig > 0 && eps > 0;
}

// CALCULATE TOTAL LATTICE ENERGY OF THE GIVEN CRYSTAL
double CalculateLatticeEnergy(int n, double a, double sig, double eps) {
    double r = 0, energy = 0;
    // CORRECT ASC TO AFCC
    a = a*sqrt(2.0)/2.0;
    int m = 2*n-1;
    for (int ix = 0; ix < m; ix++) {
        for (int iy = 0; iy < m; iy++) {
            for (int iz = 0; iz < m; iz++) {
              for (int jx = 0; jx < m; jx++) {
                for (int jy = 0; jy < m; jy++) {
                  for (int jz = 0; jz < m; jz++) {
                    if (!(ix == jx && iy == jy && iz == jz)) {
                        if (!((ix%2 + iy%2 + iz%2)%2) && !((jx%2 + jy%2 + jz%2)%2)) {
                          	// CALCULATE THE DISTANCE BETWEEN TWO ATOMS IN A 3D CRYSTAL
                            r = CalculateDistance(ix, jx, iy, jy, iz, jz, a);
                            // CALCULATE THE LENNARD-JONES-ENERGY BETWEEN THESE ATOMS AND ADD IT UP
                            energy += CalculateLJEnergy(r, sig, eps);
                      }
    				}
                  }
                }
              }
            }
        }
    }
    // DIVIDE BY THE NUMBER OF REDUNDANT CALCULATIONS
    return energy/double(2 * (n * n * n + 3.0*pow((n-1), 3) + 3.0*pow((n-1), 2)));
}

// CALCULATE DISTANCE BETWEEN TWO ATOMS IN A THREE DIMENSIONAL SPACE
double CalculateDistance(int ix, int jx, int iy, int jy, int iz, int jz, double a) {
  	double d = (ix-jx)*(ix-jx) + (iy-jy)*(iy-jy) + (iz-jz)*(iz-jz);
    return a*sqrt(d);
}

// CALCULATE THE LENNARD-JONES ENERGY
double CalculateLJEnergy(double r, double sig, double eps) {
    double x = sig/r, x3 = x*x*x, x6=x3*x3;
    return 4.0*eps*(x6*(x6-1.0));
}

// PRINT THE RESULTS WITH A SHORT DESCRIPTION
void PrintResult(int n, double a, double sig, double eps, double ene) {
    cout << "# Given number of atoms: " << n <<endl;
    cout << "# Given lattice parameter a in nm: " << a<< endl;
    cout << "# Given LJ parameter sigma in nm: " << sig << endl;
    cout << "# Given LJ parameter epsilon in kJ/mol: " << eps << endl;
    cout << "Calculated lattice energy [kJ/mol]: " << ene << endl;
}