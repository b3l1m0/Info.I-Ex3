// C++ program for Ex B: Lattice energy of LJ atoms in simple cubic
/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 7.11.2024
Task 		    : B
Time required	: 3 hours
Program Description:
The program calculates the lattice energy inside a three-dimensional simple crystal of noble gases.
The user puts in the parameters needed for the calculation. Then six nested loops loop over each atom
in the crystal and calculate the distance to each other atom in the crystal. This distance is then
used to calculate the Lennard-Jones-Energy between these atoms which is all added up to the total
lattice energy of the crystal. At last the lattice energy is divided by double the amount of atoms
in the crystal to remove redundancies. The finished result is printed along with the given parameters
to ensure that no error occured.

Short report:

A:
E for N(10) = -1.40115 -> 18.06 %
E for N(20) = -1.54583 -> 9.60 %
E for N(40) = -1.62216 -> 5.14 %

B:
The computational scaling of my code is O[n^6] as seen in the graph at the 6th degree regression.
This corresponds to my expectations as i thought that the six loops would probably take up the most
amount of time. Which is also the case as it seems.

C:
It would be possible to calculate the square root using an iterative approach. Or to remove the
function call and calculate the square root inside of the function using an effective algorithm.

D:
Lattice Energy in kJ/mol
Ne: -1.62216
Ar: -5.44115
Kr: -7.32845
Xe: -10.4702
The trend follows my expectations as i thought that the energy would decrease because of the
big nuclei.
These numbers are bigger than the numbers for the BCC and FCC lattice and i think that this
is because of the fact that the atoms are packed less thight and therefore the calculated attraction
and energy is smaller.

E:
The function presents a way to calculate the energy more efficiently.
Because epsilon, sigma and a_sc are all constants and the energy of the crystal solely depends on
the number of atoms in the crystal and more generally the distances between these many atoms, the
function can be expressed using the distributivity of constants and writing A_SC, 6 and A_Sc, 12
as these constants relative to the numbers and values of these crystals:

E = f(sig, eps, a_sc; Asc6 , Asc12)
E = 4.0 * \epsilon * ((\frac{\sigma}{a_{sc}})^{12} * A_{SC, 12}- (\frac{\sigma}{a_{sc}}^{6}) * A_{SC, 6})

Therefore the constants Asc6 and Asc12 can be expressed as the sum of the distances in each crystal
A_{SC, 6}=\sum_{i,j=0}^{n} \frac{1}{r_{ij}^{6}}
A_{SC, 12}=\sum_{i,j=0}^{n} \frac{1}{r_{ij}^{12}}

These could be calculated as the sum of the distances to the power of 6 or 12 respectively
inside the six loops.
This theory is also implemented in ex3C1 to make the program more effective.

F:
If we exclude the expression that r = d*asc and assume that r is just the ideal distance we can
find an expression for r if we put the derivative of the Lennard-Jones-Potential equal to zero.
This expression is then:
(2*sigma^6/r^6)^(1/6) = asc
Therefore we can assume that asc is this expression at it can be calculated as given.
If we insert Asc6 as given by the definition we would get:
asc = (2*sigma^6*Asc6)^(1/6)
We would not need a computer to do this for us but it is faster and more fun like that.

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
// GET INPUT
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

// OVERALL FUNCTION TO CALCULATE THE TOTAL LATTICE ENERGY
double CalculateLatticeEnergy(int n, double a, double sig, double eps) {
    // DECLARE AND INITIALIZE VARIABLES
    double r = 0;
    double energy = 0;
    // SIX FOR LOOPS TO MODEL A THREE DIMENSIONAL SPACE
    for (int ix = 0; ix < n; ix++) {
        for (int iy = 0; iy < n; iy++) {
            for (int iz = 0; iz < n; iz++) {
              for (int jx = 0; jx < n; jx++) {
                for (int jy = 0; jy < n; jy++) {
                  for (int jz = 0; jz < n; jz++) {
                    // CHECK THAT THE COORDINATES ARE NOT THE SAME
                    if (!(ix == jx && iy == jy && iz == jz)) {
                        // CALCULATE DISTANCE AND LENNARD-JONES-ENERGY FOR EVERY PAIR
    					r = CalculateDistance(ix, jx, iy, jy, iz, jz, a);
        				energy += CalculateLJEnergy(r, sig, eps);
    				}
                  }
                }
              }
            }
        }
    }
    // RETURN ENERGY DIVIDED BY THE DOUBLE OF THE NUMBER OF ATOMS TO REMOVE DOUBLE CALCULATIONS
    return energy/double(2 * n * n * n);
}

// CALCULATE DISTANCE IN A THREE DIMENSIONAL SPACE
double CalculateDistance(int ix, int jx, int iy, int jy, int iz, int jz, double a) {
    return a*sqrt((ix - jx)*(ix - jx)+(iy - jy)*(iy - jy)+(iz - jz)*(iz - jz));
}

// CALCULATE THE LENNARD-JONES-ENERGY FOR ONE INTERACTION
double CalculateLJEnergy(double r, double sig, double eps) {
    double x = sig/r, x3 = x*x*x, x6=x3*x3;
    return 4.0*eps*(x6*(x6-1.0));
}

// PRINT THE RESULTS WITH THE GIVEN DESCRIPTION
void PrintResult(int n, double a, double sig, double eps, double ene) {
    cout << "# Given number of atoms: " << n <<endl;
    cout << "# Given lattice parameter a in nm: " << a<< endl;
    cout << "# Given LJ parameter sigma in nm: " << sig << endl;
    cout << "# Given LJ parameter epsilon in kJ/mol: " << eps << endl;
    cout << "Calculated lattice energy [kJ/mol]: " << ene << endl;
}