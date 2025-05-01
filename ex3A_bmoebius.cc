// C++ program for Ex 3A: Lattice energy of LJ atoms in one dimension
/*
Student name    : Bente Moebius
Username	    : bmoebius
Date		    : 1.11.2024
Task 		    : A
Time required	: 4 (reading) + 2 hours
Program Description:
The program calculates the lattice energy inside of a one dimensional crystal of noble gases.
The user puts in the parameters needed for the calculation. Then two loops loop over each atom and
calculate the distance to another atom. This distance is then used to calculate the Lennard-Jones-
Energy between these atoms which is all added up to the total lattice energy of the crystal.
At last the lattice energy is divided by double the amount of atoms in the crystal to remove
redundancies. The finished result is printed along with the given parameters.

Short report:
A:
E for N(50) = -0.272778 -> 2.11 %
E for N(500) = -0.278073 -> 2.11 %
E for N(5000) = -0.278603 -> 2.06 %

B:
The error is positive because the calculated lattice energy is calculated for these finite atoms.
In an inifinte crystal there are infinite interactions meaning there is always more lattice energy.
E would increase when changing N if the lattice energy would be positive because then the absolute
would be increasing when the number of atoms increases.

C:
The computational scaling of my code is O[N*N] as seen in the regression. This corresponds to my
expactations because of the double loop, which takes up most of the time.
The computational scaling of a three dimensional crystal would probably be O[N^6] because we would
need to have in total 6 for loops for all of the needed coordinates.

D:
In the data it is visible that the calculation for double the number of atoms takes up 2^2 more
time to calculate the lattice energy. Similar the calculation for three times the number of atoms
takes up 3^2 more time to calculate the lattice energy. Therefore the regression would be quadratic.

E:
Timing in s
V1: 0:06.37
V2: 0:05.63
V3: 0:03.50
V4: 0:01.41
V5: 0:01.04
V6: 0:00.89
The time ratio between V1 and V6 is: 4.5 : 1
These trends are because of the call of different math functions. This call of the functions
and return of the values is time intensive as seen in the different between V5 and V6, where only
the call of the function is removed but the calculation is basically the same.

F:
It would be possible to half the calculation cost by changing the for loops to not iterate each
atom for each loop but only iterate half of the atoms in the loop. This would eliminate these double
calculations and therefore cut the calculation time in half.

G:
No, this would not happen as the distance is later multiplied 6 times with itself. Because of the
even exponent the result is always positive as the minuses calcel each other out.

H:
Lattice Energy in kJ/mol
Ne: -0.278603
Ar: -0.940475
Kr: -1.27078
Xe:  -1.80757

Yes the trend coincides with my expectations as i though that the bigger the atom nucleus, the more
the atoms attract each other.
The calculated energies for the one dimensional crystal are smaller than the ones for the three
dimensional and also for the BCC and FCC lattice. This is because in a three dimensional crystal
there are way more interactions between the different atoms. In the real world these interactions
are not only limited to one dimension.

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
double CalculateDistance(int i, int j, double a);
double CalculateLJEnergy(double r, double sig, double eps);
void PrintResult(int n, double a, double sig, double eps, double ene);

// MAIN
int main() {
    // DECLARE VARIABLES
    int n;
    double a, sigma, epsilon, energy;
    // CALL FUNCTIONS
    // READ INPUT AND CHECK IF EVERYTHIN IS REALISTIC
    GetInput(n, a, sigma, epsilon);
    // CALCULATE THE ENERGY
    energy = CalculateLatticeEnergy(n, a, sigma, epsilon);
    // PRINT THE RESULTS
    PrintResult(n, a, sigma, epsilon, energy);
    return 0;
}

// FUNCTION DEFINITIONS FOR THE 5 REQUIRED FUNCTIONS
bool GetInput(int& n, double& a, double& sig, double& eps) {
    cout << "# Please enter number of atoms: " << endl;
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
  // DECLARE AND INITIALIZE THE VARIABLES
  double r = 0;
  double energy = 0;
  // NESTED FOR LOOPS TO CALCULATE ONE DIMENSIONAL SPACE
  for (int i = 0; i <= n-1; i++) {
  	for (int j = 0; j <= n-1; j++) {
        // CHECK THAT THE COODINATES DO NOT MATCH
    	if (j != i) {
          // CALCULATE DISTANCE AND ENERGY
          r = CalculateDistance(i, j, a);
          energy += CalculateLJEnergy(r, sig, eps);
        }
    }
  }
  // DIVIDE ENERGY BY THE DOUBLE OF THE NUMBER OF ATOMS TO SUBTRACT REPETITIONS
  return energy/(2*n);
}

// CALCULATE DISTANCE BETWEEN TWO ATOMS
double CalculateDistance(int i, int j, double a) {
   	double d;
  	j > i ? d = j*a - i*a : d = i*a - j*a;
   	return d;
}

// CALCULATE LENNERD-JONES-ENERGY
double CalculateLJEnergy(double r, double sig, double eps) {
    // V1
    //return 4.0*eps*(pow(sig/r, 12.0)-pow(sig/r, 6.0));
    // V5
    double x = sig/r, x3 = x*x*x, x6=x3*x3;
    return 4.0*eps*(x6*(x6-1.0));
}

// PRINT THE RESULTS EACH PARAMETER AT A TIME
void PrintResult(int n, double a, double sig, double eps, double ene) {
    cout << "# Given number of atoms: " << n <<endl;
    cout << "# Given lattice parameter a in nm: " << a<< endl;
    cout << "# Given LJ parameter sigma in nm: " << sig << endl;
    cout << "# Given LJ parameter epsilon in kJ/mol: " << eps << endl;
    cout << "Calculated lattice energy [kJ/mol]: " << ene << endl;
}