#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h> // use sqrt()
#include <vector> // use vectors
#include <algorithm> // use abs()
#include <ctime>

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

// Error detection:
// valgrind ./a.out L030sgGAUSR_e0c100sgGAU_J1_1c0_j2_0c0_G0c80__DBC_J1______map.sd

using namespace std;

int main()
{

	int start_s=clock();

	std::cout << endl ;
	std::cout << BOLDYELLOW << "    __________________________________________________" << std::endl ;
	std::cout << BOLDYELLOW << "            _=_                                       " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          q(-_-)p                                     " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          '_) (_`     Water Wire Membrane Percolation" << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\     Carles Triguero 2018           " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                   " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                                " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    __________________________________________________" << RESET << std::endl ;
	std::cout << endl ;


	// Input-Output Files
	std::ifstream IFCL1( "Cluster1.xyz" ) ;
	std::ifstream IFCL2( "Cluster2.xyz" ) ;
	std::ifstream IFCOM( "com.xyz" ) ;
	std::ifstream IFPUC( "P8u.xyz" ) ;
	std::ifstream IFPUD( "P8d.xyz" ) ;

	std::string line ;
	unsigned int element ; // Atoms type
	double x, y, z ; // Coordinates
	unsigned int Natoms ; // Atoms in the cluster at this specific frame
	
	unsigned int FrameCounter = 0 ; // Frame number
//	std::vector<double> Xx, Yy, Zz ;

	while (getline(IFCL1, line))
	{
		std::stringstream aa(line) ;

		if (line.length() < 5)
		{
			FrameCounter++ ;
			aa >> Natoms ; // Gets the number of atoms in this specific frame (not constant anymore)
			cout << "Natoms= " << Natoms << std::endl ;
			cout << "Analyzing frame = " << FrameCounter << std::endl ;
			getline(IFCL1, line) ; // Skip 2nd line
		}

//		//for (int i=0; i<Natoms; i++)
//		for (int i=0; i<5; i++)
//		{	
			std::getline(IFCL1, line) ;
			std::stringstream cc(line) ;
			cc >> element >> x >> y >> z ;

			std::cout << line << std::endl ;
			std::cout << element << '\t' << x << '\t' << y << '\t' << z << std::endl ;
////			Xx.push_back (x) ;
////			Yy.push_back (y) ;
////			Zz.push_back (z) ;
////		}

//		// Extract center of mass of the membrane for this frame
//		//std::getline(IFCOM, line) ;
//		//std::getline(IFCOM, line) ;
//		std::getline(IFCOM, line) ;
//		//std::stringstream aa(line) ;
//		aa >> element >> x >> y >> z ;
//		std::cout << "COM :" << aa << std::endl ;
//		std::cout << "COM :" << x << '\t' << y << '\t' << z << std::endl ;



		return 0 ;   
	}

	IFCL1.close() ;
	



	
	int stop_s=clock();
	cout << endl ;
	cout << "Total execution time: " << BOLDBLACK << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << RESET << endl;
	
	return (0) ;
}
