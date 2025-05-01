// C++ program for Ex B: Lattice energy of LJ atoms in an BCC
/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 7.11.2024
Task 		    : C
Time required	: 2 hours
Program Description:
In this programm the total lattice energy of a crystal is computed based on the Lennard-Jones-Energy
between two atoms in a BCC crystal.
I have implemented ideas and theories discussed in the short report section of ex3B to make the
programm more efficient. All in all i think that i did a good job with computing this theory as
the results look realistic and the runtime is better than the runtime of ex3C2, where i used the
old theory from ex3B as a base to compare the runtimes.
Short report:

Lattice Energy in kJ/mol
Ne: -2.35631
Ar: -7.9037
Kr: -10.6452
Xe: -15.2088

A:
No the values are not sufficiently converged. In the graph it is visible that the calculation for
n = 40 for the FCC lattice is very similar to the full convergence value of the BCC lattice. Similarly
the with n = 40 calculated value for the BCC lattice is visible above the fully converged value for
the BCC lattice.

B:
The calculated values for the FCC lattice are far lower than the experimentally determined values
for the FCC lattice. This is due to the approximation that there are only attractions inside the
crystal, while in reality there is also shielding of these attractive forces due to other electrons.
This results in a lower amount of lattice energy as the energy is partially absorbed / used otherwise.

C:
I think that it is very likely that these crystals crystalize in FCC lattices, as these have the
lowest lattice energy compared to the others. But the values converge for Neon, which overall
means that the crystallization in a FCC lattice is not given for all rare gases, as it is visible
that the FCC and BCC lattice of Neon have similar values, meaning that it would also be possible for
Neon to crystallize in a BCC lattice.
Also this is modelled for only one condition, under physically different conditions, these elements
could possibly crystallize in another way.

D:
I think that the reason why not all metals crystalise in a FCC lattice is because of the electron
gas. As metals have a specific type of crystal, where there are the atomic nucleei whom give of
some of their valence electrons to the electron gas, they need space for this electron gas. It is
therefore more efficient for these atoms that they are not as tightly packed because there are some
repulsions because of the partically positive charge of the atoms and there is the need for space
because of the electron gas.

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
double CalculateDistance(int ix, int jx, int iy, int jy, int iz, int jz);
double CalculateLJEnergy(double sig, double eps, double a, double asc6, double asc12);
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

double CalculateLatticeEnergy(int n, double a, double sig, double eps) {
    double r = 0, energy = 0;
    int m = 2*n-1;
    // CORRECT THE LATTICE PARAMETER (DOUBLE NOT INT DIVISION)
    a = a*sqrt(4.0/3.0)/2.0;
    // DECLARE THE CONSTANTS
    double asc6 = 0;
    double asc12 = 0;
    for (int ix = 0; ix < m; ix++) {
        for (int iy = 0; iy < m; iy++) {
            for (int iz = 0; iz < m; iz++) {
              for (int jx = 0; jx < m; jx++) {
                for (int jy = 0; jy < m; jy++) {
                  for (int jz = 0; jz < m; jz++) {
                    if (!(ix == jx && iy == jy && iz == jz)) {
                        if (!((ix%2 + iy%2 + iz%2)%3) && !((jx%2 + jy%2 + jz%2)%3)) {
                          	// CALCULATE DISTANCE AND FROM THEN THE CONSTANTS
                            r = CalculateDistance(ix, jx, iy, jy, iz, jz);
                            double r3 = r*r*r, r6 = r3*r3;
                            asc6 += 1.0/r6;
                            asc12 += 1.0/(r6*r6);
                      }
    				}
                  }
                }
              }
            }
        }
    }
    // CALCULATE LJ ENERGY OF THE WHOLE CRYSTAL BASED ON THE FUNCTION DISCUSSED IN EX3B E
    energy = CalculateLJEnergy(sig, eps, a, asc6, asc12);
    // DIVIDE ENERGY BY DOUBLE OF NUMBER OF ATOMS TO REMOVE REDUNDANT CALCULATIONS
    return energy / double(2 * (n * n * n + pow((n-1), 3)));
}

// CALCULATE THE DISTANCE BETWEEN TWO THREE DIMENSIONAL POINTS
double CalculateDistance(int ix, int jx, int iy, int jy, int iz, int jz) {
  	double d = (ix-jx)*(ix-jx) + (iy-jy)*(iy-jy) + (iz-jz)*(iz-jz);
    return sqrt(d);
}

// CALCULATE LENNARD-JONES-ENERGY BETWEEN TWO POINTS
double CalculateLJEnergy(double sig, double eps, double a, double asc6, double asc12) {
    double x = sig/a, x3 = x*x*x, x6=x3*x3;
    return 4.0*eps*(x6*x6*asc12-x6*asc6);
}

// PRINT THE RESULTS WITH A SMALL DESCIRPTION
void PrintResult(int n, double a, double sig, double eps, double ene) {
    cout << "# Given number of atoms: " << n <<endl;
    cout << "# Given lattice parameter a in nm: " << a<< endl;
    cout << "# Given LJ parameter sigma in nm: " << sig << endl;
    cout << "# Given LJ parameter epsilon in kJ/mol: " << eps << endl;
    cout << "Calculated lattice energy [kJ/mol]: " << ene << endl;
}