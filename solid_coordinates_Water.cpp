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
	std::cout << BOLDYELLOW << "          '_) (_`         SOLID MEMBRANE WITH HOLE   " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
	std::cout << endl ;

	// Parameters:
	//----------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------	
	unsigned int Lx=18 ;		// Number of atoms 60A/rm
	unsigned int Ly=18 ;		// Number of atoms 60A/rm
	unsigned int Lz=14 ;		// Number of atoms 50A/rm
	const double rm=3.54575 ;	// Minimum distance in Angstroms
	const double radius=10.0 ;	// Angstroms
	int molecules= 2000 ; 
	#define QO -1.1128
	#define QH  0.5564
	//----------------------------------------------------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------------------------------------------------		
	
	
	for ( int k = 1; k < argc ; ++k )
	{
		if ( ( argv[k] == std::string("-h") ) || ( argv[k] == std::string("-HELP") ) || ( argv[k] == std::string("-H") ) || ( argv[k] == std::string("-help") ) )
		{ 
			cout  << BOLDBLACK << "    HELP:" << RESET << std::endl ;
			cout << "    Generates a xyz configuration of A and B species" << std::endl ;
			cout << "    Interpenetrated rectangular 2d lattices" << std::endl ;
			cout << "    Lattice parameter is 1" << std::endl ;
			cout << "    Lattice parameter is 1" << std::endl ;
			cout << "    X-+-X-+-" << std::endl ;
			cout << "    +-O-+-O-" << std::endl ;
			cout << "    X-+-X-+-" << std::endl ;
			cout << "    ------------------------------------------------" << std::endl ;
			cout << BOLDBLACK << "    Mandatory flags:" << RESET << std::endl ; 
			cout << "    -lx" << "\t" << "    to set integer linear Lx size (e.g. ./a.out -lx 10)" << std::endl ;
			cout << "    -ly" << "\t" << "    to set integer linear Lx size  (e.g. ./a.out -ly 5)" << std::endl ; 
			cout << BOLDBLACK << "    Optional flags:" << RESET << std::endl ;
			cout << "    -h" << "\t" << "    to get help  (e.g. ./a.out -help)" << std::endl ; 
			cout << std::endl ;
			return (0) ;
		}
		if ( ( argv[k] == std::string("-lx") ) || ( argv[k] == std::string("-Lx") )  || ( argv[k] == std::string("-LX") ) ) { Lx = atoi(argv[k+1]) ; }
		if ( ( argv[k] == std::string("-ly") ) || ( argv[k] == std::string("-Ly") )  || ( argv[k] == std::string("-LY") ) ) { Ly = atoi(argv[k+1]) ; }
	}
	
//	if ( argc < 5 ) 
//	{ 
//		cout << " Wrong ussage man!" << endl ; 
//		return (0) ;
//	}
	
	// Count execution time
	int start_s=clock();
	
	// Files to store data
	ofstream CONFIG ;
	CONFIG.open ("config.xyz", ios::out | ios::trunc); // All computed densities inside cylinders
	ofstream SOLID ;
	SOLID.open ("solid.data", ios::out | ios::trunc); // All computed densities inside cylinders
	// Position coordinates of all atoms
	std::vector<double> xw, yw, zw ;


	int Atoms=0 ;
	for ( int i = 0; i < Lx; ++i )
	{
		for ( int j = 0; j < Ly; ++j )
		{
			for ( int k = 0; k < Lz; ++k )
			{
				double x=rm*(i-Lx/2.0)+rm/2.0 ;
				double y=rm*(j-Ly/2.0)+rm/2.0 ;
				double z=rm*(k-Lz/2.0)+rm/2.0 ;

				double dxy=sqrt(x*x+y*y) ;
				if ( dxy > radius )
				{
					Atoms++ ;
				}
			}
		}
	}
	//std::cout << Atoms << std::endl ;




	SOLID << "Solid membrane atomic data" << std::endl ;
	SOLID << endl ;
	SOLID << Atoms+3*molecules << " atoms" << std::endl ;
	SOLID << 2*molecules << " bonds" << endl ;
	SOLID << 1*molecules << " angles" << endl ;
	SOLID << endl ;
	SOLID << "3" << " atom types" << std::endl ;
	SOLID << "1 bond types" << endl ;
	SOLID << "1 angle types" << endl ;
	SOLID << std::endl ;
	SOLID << rm*(0-Lx/2.0) << "\t" << rm*(Lx-Lx/2.0) << "\t" << "xlo xhi" << std::endl ;
	SOLID << rm*(0-Ly/2.0) << "\t" << rm*(Ly-Ly/2.0) << "\t" << "ylo yhi" << std::endl ;
	SOLID << rm*(0-Lz/2.0)-50.0 << "\t" << rm*(Lz-Lz/2.0)+50.0 << "\t" << "zlo zhi" << std::endl ;
	SOLID << std::endl ; 
	SOLID << "Masses" << std::endl ;
	SOLID << std::endl ; 
	SOLID << "1" << "\t" << "15.999" << std::endl ;
	SOLID << "2" << "\t" << "15.999" << std::endl ;
	SOLID << "3" << "\t" << "1.0008" << std::endl ;
	SOLID << std::endl ; 
	SOLID << "Atoms" << std::endl ;
	SOLID << std::endl ; 




	CONFIG << Atoms+3*molecules << std::endl ;
	CONFIG << std::endl ;

	
	

 
	Atoms=0 ;

	// Membrane bulk atoms
	for ( int k = 2; k < Lz-2; ++k )
	{
		for ( int i = 0; i < Lx; ++i )
		{
			for ( int j = 0; j < Ly; ++j )
			{
			
				double x=rm*(i-Lx/2.0)+rm/2.0 ;
				double y=rm*(j-Ly/2.0)+rm/2.0 ;
				double z=rm*(k-Lz/2.0)+rm/2.0 ;

				double dxy=sqrt(x*x+y*y) ;
				if ( dxy > radius )
				{
					xw.push_back (x) ;
					yw.push_back (y) ;
					zw.push_back (z) ;

					Atoms++ ;
					// Atom number, molecule number, atom type, charge, coordinates
					//SOLID << Atoms << "\t" << "1" << "\t" << "\t" << x << "\t" << y << "\t" << z << std::endl ;
					SOLID << Atoms << "\t" << Atoms << "\t" << "1" << "\t" << "0.0" << "\t" << x  << "\t" << y << "\t" << z << endl ;

					CONFIG << "C" << "\t" << x << "\t" << y << "\t" << z << std::endl ; 
				}
			}
		}
	}

	int AtomsBulk=Atoms ;
	std::cout  << YELLOW << "    -> Inserted: " << BOLDYELLOW << AtomsBulk << RESET << YELLOW << " bulk solid atoms" << std::endl ;
	std::cout  << BLUE << "       * Their index number goes from: " << BOLDBLUE << "1 to " << AtomsBulk << RESET << BLUE << " bulk solid atoms" << RESET << std::endl ;

	// Surface atoms layer of 2 atoms side 1
	for ( int k = 0; k < 2; ++k )
	{
		for ( int i = 0; i < Lx; ++i )
		{
			for ( int j = 0; j < Ly; ++j )
			{
			
				double x=rm*(i-Lx/2.0)+rm/2.0 ;
				double y=rm*(j-Ly/2.0)+rm/2.0 ;
				double z=rm*(k-Lz/2.0)+rm/2.0 ;

				double dxy=sqrt(x*x+y*y) ;
				if ( dxy > radius )
				{
					xw.push_back (x) ;
					yw.push_back (y) ;
					zw.push_back (z) ;

					Atoms++ ;
					// Atom number, molecule number, atom type, charge, coordinates
					//SOLID << Atoms << "\t" << "1" << "\t" << "\t" << x << "\t" << y << "\t" << z << std::endl ;
					SOLID << Atoms << "\t" << Atoms << "\t" << "1" << "\t" << "0.0" << "\t" << x  << "\t" << y << "\t" << z << endl ;

					CONFIG << "N" << "\t" << x << "\t" << y << "\t" << z << std::endl ; 
				}
			}
		}
	}

	

	// Surface atoms layer of 2 atoms side 2
	for ( int k = Lz-2; k < Lz; ++k )
	{
		for ( int i = 0; i < Lx; ++i )
		{
			for ( int j = 0; j < Ly; ++j )
			{
			
				double x=rm*(i-Lx/2.0)+rm/2.0 ;
				double y=rm*(j-Ly/2.0)+rm/2.0 ;
				double z=rm*(k-Lz/2.0)+rm/2.0 ;

				double dxy=sqrt(x*x+y*y) ;
				if ( dxy > radius )
				{
					xw.push_back (x) ;
					yw.push_back (y) ;
					zw.push_back (z) ;

					Atoms++ ;
					// Atom number, molecule number, atom type, charge, coordinates
					//SOLID << Atoms << "\t" << "1" << "\t" << "\t" << x << "\t" << y << "\t" << z << std::endl ;
					SOLID << Atoms << "\t" << Atoms << "\t" << "1" << "\t" << "0.0" << "\t" << x  << "\t" << y << "\t" << z << endl ;

					CONFIG << "N" << "\t" << x << "\t" << y << "\t" << z << std::endl ; 
				}
			}
		}
	}

	std::cout  << YELLOW << "    -> Inserted: " << BOLDYELLOW << Atoms-AtomsBulk << RESET << YELLOW << " surface solid atoms" << std::endl ;

	int SolidAtoms=Atoms ;
	std::cout  << YELLOW << "    -> Inserted: " << BOLDYELLOW << xw.size() << RESET << YELLOW << " solid atoms" << std::endl ;
	
	// Water inclusion
	//1	 0.000000	 0.000000	0.000000
	//2	-0.756950	-0.585882	0.000000
	//3	 0.756950	-0.585882	0.000000
	// Box size
	double lxp2=rm*Lx/2.0 ;
	double lyp2=rm*Ly/2.0 ;
	double lzp2=rm*Lz/2.0+50.0 ;

	// Random real numbers
	std::random_device rd1 ;  //Will be used to obtain a seed for the random number engine
	std::random_device rd2 ;  //Will be used to obtain a seed for the random number engine
	std::random_device rd3 ;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen1(rd1()) ; //Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen2(rd2()) ; //Standard mersenne_twister_engine seeded with rd()
	std::mt19937 gen3(rd3()) ; //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis_cartesian1(-lxp2+1.5, lxp2-1.5) ;
	std::uniform_real_distribution<> dis_cartesian2(-lyp2+1.5, lyp2-1.5) ;
	std::uniform_real_distribution<> dis_cartesian3(-lzp2, lzp2) ;
	
	int mol=0 ;

	newmol:

	double Ox=dis_cartesian1(gen1) ;
	double Oy=dis_cartesian2(gen2) ;
	double Oz=dis_cartesian3(gen3) ;

	double owx=Ox ;
	double owy=Oy+0.585882 ;
	double owz=Oz ;

	double hw2x=Ox-0.756950 ;
	double hw2y=Oy ;
	double hw2z=Oz ;

	double hw3x=Ox+0.756950 ;
	double hw3y=Oy ;
	double hw3z=Oz ;

	if ( mol == molecules) { goto fin ; }

	for ( int k=0; k<xw.size(); k++)
	{
		double distance=sqrt((Ox-xw[k])*(Ox-xw[k])+(Oy-yw[k])*(Oy-yw[k])+(Oz-zw[k])*(Oz-zw[k])) ;

		//std::cout << Ox << " " << Oy << " " << Oz << " " << xw[k] << " " << yw[k] << " " << zw[k] << std::endl ;
		//std::cout << "d=" << distance << std::endl ;

		if ( distance < 4.00 ) 
		{ 
			//cout << "Try again" ;
			goto newmol ; 
		}		
	}

	
	xw.push_back (owx) ;
	yw.push_back (owy) ;
	zw.push_back (owz) ;
	xw.push_back (hw2x) ;
	yw.push_back (hw2y) ;
	zw.push_back (hw2z) ;
	xw.push_back (hw3x) ;
	yw.push_back (hw3y) ;
	zw.push_back (hw3z) ;

	Atoms++ ;
	mol++ ;

	// Atom number, molecule number, atom type, charge, coordinates
	SOLID << Atoms << "\t" << SolidAtoms+mol << "\t" << "2" << "\t" << QO << "\t" << "\t" << owx << "\t" << owy << "\t" << owz << std::endl ;
	Atoms++ ;
	SOLID << Atoms << "\t" << SolidAtoms+mol << "\t" << "3" << "\t" << QH << "\t" << "\t" << hw2x << "\t" << hw2y << "\t" << hw2z << std::endl ;
	Atoms++ ;
	SOLID << Atoms << "\t" << SolidAtoms+mol << "\t" << "3" << "\t" << QH << "\t" << "\t" << hw3x << "\t" << hw3y << "\t" << hw2z << std::endl ;

	CONFIG << "O" << "\t" << owx << "\t" << owy << "\t" << owz << std::endl ;
	CONFIG << "H" << "\t" << hw2x << "\t" << hw2y << "\t" << hw2z << std::endl ;
	CONFIG << "H" << "\t" << hw3x << "\t" << hw3y << "\t" << hw3z << std::endl ;

	goto newmol ;

	fin:


	// Velocities
	SOLID << std::endl ; 
	SOLID << "Velocities" << std::endl ;
	SOLID << std::endl ;
	for ( int i = 0; i < xw.size(); ++i ) {  SOLID << i+1 << "\t" << "0.0" << "\t" << "0.0" << "\t" << "0.0" << std::endl ; }
	
	// Bonds
	SOLID << endl ;
	SOLID << "Bonds" << endl ;
	SOLID << endl ;

	for (int i = 0; i < mol; ++i)
	{
		SOLID << SolidAtoms+2*i+1 << "\t" << "1" << "\t" << SolidAtoms+3*i+1 << "\t" << SolidAtoms+3*i+2 << endl ;
		SOLID << SolidAtoms+2*i+2 << "\t" << "1" << "\t" << SolidAtoms+3*i+1 << "\t" << SolidAtoms+3*i+3 << endl ;
	}

	// Angles
	SOLID << endl ;
	SOLID << "Angles" << endl ;
	SOLID << endl ;

	for (int i = 0; i < mol; ++i)
	{
		SOLID << SolidAtoms+i+1 << "\t" << "1" << "\t" << SolidAtoms+3*i+2 << "\t" << SolidAtoms+3*i+1 << "\t" << SolidAtoms+3*i+3 << endl ;
	}





	std::cout  << YELLOW << "    -> Inserted: " << BOLDYELLOW << (xw.size()-SolidAtoms)/3.0 << RESET << YELLOW << " water molecules" << std::endl ;
	std::cout  << YELLOW << "    -> Inserted: " << BOLDYELLOW << xw.size() << RESET << YELLOW << " atoms" << std::endl ;


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
