// classes example
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <cerrno>
#include <cfenv>
#include <ctime>
#include <algorithm> // use abs() needed for sort
#include <random>

//#include <string> // 
//#include<math.h> // use sqrt()



#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

using namespace std;


///
/// This program calculates the distribution of: 
///
/// (1) Number of first neighbours
/// (2) First neighbours distances
///
/// Based on the connectivity criterion imposed by topological clustering and NOT
/// on the distance based clustering
///
	

//**********************************************************************************
// main function
//**********************************************************************************
int main( int argc, const char* argv[] )
{
	std::cout << endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << std::endl ;
	std::cout << BOLDYELLOW << "            _=_                                      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          q(-_-)p                                    " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          '_) (_`         LAMMPS H2O configuration in a box        " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
	std::cout << endl ;

	// Check the number of arguments (1 means only the name of the program => No argument)
	if ( argc == 1 )
	{
		cout << "\t Wrong usage. You should execute:" << endl ;
		cout << BOLDRED << "\t " << argv[0] << " [File to analyze.dat]" << RESET << endl ;
		cout << " " << endl ;
		return (0) ;
	}

	#define PI  3.14159265
	#define QH -0.8476
	#define QO  0.4238
	double Lx=10;
	double Ly=10;
	double Lz=10;
	int mol=3;

	for ( int k = 1; k < argc ; ++k )
	{
		if ( ( argv[k] == std::string("-h") ) || ( argv[k] == std::string("-HELP") ) || ( argv[k] == std::string("-H") ) || ( argv[k] == std::string("-help") ) )
		{ 
			cout  << BOLDBLACK << "    HELP:" << RESET << std::endl ;
			cout << "    Generates a histogram with the second column of a file containing real data" << std::endl ;
			cout << "    [Column can be changed and also addapted to integer data]" << std::endl ;
			cout << "    ------------------------------------------------" << std::endl ;
			cout << BOLDBLACK << "    Execution: ./a.out [+flags]" << RESET << std::endl ; 
			cout << BOLDBLACK << "    Mandatory flags:" << RESET << std::endl ; 
			cout << "    -box" << "\t" << "    to set the box size in Angstroms (e.g. ./a.out -box 100 50 75) default box=10X10X10" << std::endl ;
			cout << "    -mol" << "\t" << "    to set the number of molecules to be created (e.g. ./a.out -mol 10) default mol=1" << std::endl ;
			cout << BOLDBLACK << "    Optional flags:" << RESET << std::endl ;
			cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ; 
			cout << std::endl ;
			return (0) ;
		}
		if ( ( argv[k] == std::string("-box") ) || ( argv[k] == std::string("-b") )  || ( argv[k] == std::string("-BOX") ) ) { Lx = atoi(argv[k+1]) ; Ly = atoi(argv[k+2]) ; Lz = atoi(argv[k+3]) ; }
		if ( ( argv[k] == std::string("-mol") ) || ( argv[k] == std::string("-m") )  || ( argv[k] == std::string("-MOL") ) ) { mol = atoi(argv[k+1]) ; }
	}	
	
	// Set angle value
	const double angleOHO=104.52 ;	// Assumed angle HOH in water Reference TIP4P
	const double distanceOH=0.9572 ;	// Assumed distance OH in water in Angstroms Reference TIP4P
	
	// Count execution time
	int start_s=clock();
	
	// Create data file to store data
	ofstream DataFile ;
	DataFile.open ("TIP4P2005_lammps.data", ios::out | ios::trunc);

	// Headers
	DataFile << "LAMMPS data file for " << mol << " TIP4P water molecules" << endl ;
	DataFile << endl ;
	DataFile << 3*mol << " atoms" << endl ;
	DataFile << 2*mol << " bonds" << endl ;
	DataFile << 1*mol << " angles" << endl ;
	DataFile << endl ;
	DataFile << "2 atom types" << endl ;
	DataFile << "1 bond types" << endl ;
	DataFile << "1 angle types" << endl ;
	DataFile << endl ;
	double const lxp2=Lx/2.0 ;
	double const lyp2=Ly/2.0 ;
	double const lzp2=Lz/2.0 ;
	DataFile << -lxp2 << " " << lxp2 << " xlo xhi" << endl ;
	DataFile << -lyp2 << " " << lyp2 << " ylo yhi" << endl ;
	DataFile << -lzp2 << " " << lzp2 << " zlo zhi" << endl ;
	DataFile << endl ;
	DataFile << "Masses" << endl ;
	DataFile << endl ;
	DataFile << "1 15.9996"<< endl ;
	DataFile << "2  1.0008"<< endl ;
	DataFile << endl ;
	DataFile << "Atoms" << endl ;
	DataFile << endl ;

	// Random real numbers
	std::random_device rd1;  //Will be used to obtain a seed for the random number engine
	std::random_device rd2;  //Will be used to obtain a seed for the random number engine
	std::random_device rd3;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen1(rd1()); //Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen2(rd2()); //Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen3(rd3()); //Standard mersenne_twister_engine seeded with rd()

	std::uniform_real_distribution<> dis_cart(-lxp2, lxp2);
	std::uniform_real_distribution<> dis_Phi(0, 360);
	std::uniform_real_distribution<> dis_Theta(-90, 90);

	double Ox, Oy, Oz ;
	double H1x, H1y, H1z ;
	for (int i = 0; i < mol; ++i)
		{
		//Use dis to transform the random unsigned int generated by gen into a double in [-lxp2, lxp2[
		// First atom anywhere
		Ox=dis_cart(gen1) ;
		Oy=dis_cart(gen1) ;
		Oz=dis_cart(gen1) ;
		// Add coordinates to a vector to avoid proximity
		
		// Second atom over sphere

		again1:
		double Phi=dis_Phi(gen2)*PI/180.0 ;
		double Theta=dis_Theta(gen3)*PI/180.0 ;
		std::cout << endl ;
		std::cout << "Theta " << Theta*180/PI << endl ;
		std::cout << "Phi " << Phi*180/PI << endl ;
		std::cout << endl ;

		H1x=Ox+distanceOH*cos(Theta)*cos(Phi) ;
		H1y=Oy+distanceOH*cos(Theta)*sin(Phi) ;
		H1z=Oz+distanceOH*sin(Theta) ;
		// Check proximity
		// Add coordinates to a vector to avoid proximity
		// Check boundaries
		if ( ( H1x > lxp2) | ( H1y > lxp2) | ( H1z > lxp2) ) { cout << "AGAIN" << endl ; goto again1 ; }
		if ( ( H1x < -lxp2) | ( H1y < -lxp2) | ( H1z < -lxp2) ) { cout << "AGAIN" << endl ; goto again1 ; }


		// Add coordinates to a vector to avoid proximity
		
		// Check distance between O-H1
		if ( abs(distanceOH-sqrt(pow(Ox-H1x,2)+pow(Oy-H1y,2)+pow(Oz-H1z,2))) > 0.0001 ) { exit (0) ; } // with certain tolerance

		std::cout << "O " << " " << Ox << " " << ' ' << Oy << ' ' << Oz << endl ; //Each call to dis(gen) generates a new random double
		std::cout << "H1 " << " " << H1x << " " << ' ' << H1y << ' ' << H1z << endl ; //Each call to dis(gen) generates a new random double

		// Atom number, molecule number, atom type, charge, coordinates
		DataFile << 3*i+1 << "\t" << i+1 << "\t" << "1" << "\t" << QH << "    " << Ox  << "    " << Oy << "    " << Oz << endl ;
		DataFile << 3*i+2 << "\t" << i+1 << "\t" << "2" << "\t" << QO << "    " << H1x  << "    " << H1y  << "    " << H1z << endl ;

		// Third atom over a cone
		//Need to compute 3rd vecto for vec(H2)
		DataFile << 3*i+3 << "\t" << i+1 << "\t" << "2" << "\t" << QO << "    " << Ox  << "    " << Oy  << "    " << Oz << endl ;

		
		

		
	}

	DataFile << endl ;
	DataFile << "Velocities" << endl ;
	DataFile << endl ;

	for (int i = 0; i < mol; ++i)
	{
		DataFile << 3*i+1 << "\t" << "0.00" << "\t" << "0.00" << "\t" << "0.00" << endl ;
		DataFile << 3*i+2 << "\t" << "0.00" << "\t" << "0.00" << "\t" << "0.00" << endl ;
		DataFile << 3*i+3 << "\t" << "0.00" << "\t" << "0.00" << "\t" << "0.00" << endl ;
	}

	DataFile << endl ;
	DataFile << "Bonds" << endl ;
	DataFile << endl ;

	for (int i = 0; i < mol; ++i)
	{
		DataFile << 2*i+1 << "\t" << "1" << "\t" << 3*i+1 << "\t" << 3*i+2 << endl ;
		DataFile << 2*i+2 << "\t" << "1" << "\t" << 3*i+1 << "\t" << 3*i+3 << endl ;
	}

	DataFile << endl ;
	DataFile << "Angles" << endl ;
	DataFile << endl ;

	for (int i = 0; i < mol; ++i)
	{
		DataFile << i+1 << "\t" << "1" << "\t" << 3*i+2 << "\t" << 3*i+1 << "\t" << 3*i+3 << endl ;
	}

	// End counting time 	
 	int stop_s=clock();
 	
	// Execution time
 	std::cout << endl ;
	std::cout  << YELLOW << "    -> Execution time: " << BOLDYELLOW << ( stop_s - start_s )/double(CLOCKS_PER_SEC) << RESET << YELLOW << " seconds" << std::endl ;
	std::cout << endl ;
	std::cout  << BOLDYELLOW << "    Program finished" << RESET << std::endl ;
	std::cout << endl ;
	
	return (0) ;
}

