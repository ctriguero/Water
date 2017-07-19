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

#define PI	3.14159265358979323846  /* pi */

using namespace std;


///
/// 	sed -ie 's/X/1/g' Cluster1.xyz
///	sed -ie 's/atoms in 1 th largest cluster//g' Cluster1.xyz
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
	std::cout << BOLDYELLOW << "          '_) (_`         EXTRACT DATA FROM log file " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "          /__/  \\         Carles Triguero 2017      " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "        _(<_   / )_                                  " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "       (__\\_\\_|_/__)                               " << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    _________________________________________________" << RESET << std::endl ;
	std::cout << BOLDYELLOW << "    Extracts different magnitudes into different files" << RESET << std::endl ;
	std::cout << endl ;



	// Check the number of arguments (1 means only the name of the program => No argument)
	if ( argc == 1 )
	{
		cout << "\t Wrong usage. You should execute:" << endl ;
		cout << BOLDRED << "\t " << argv[0] << " [File to analyze.dat]" << RESET << endl ;
		cout << " " << endl ;
		return (0) ;
	}
	
	// Check if the file exists
	ifstream file(argv[1]) ;
	if (!file)
	{
    	std::cout << BOLDRED <<"    -> ERROR: File test.xyz does not exist. ABORTING" << RESET << std::endl ;
    	std::cout << std::endl ;
		abort () ;
	}
	file.close() ;
	
	std::cout << YELLOW << "    -> File " << BOLDYELLOW << argv[1] << RESET << YELLOW << " found" << RESET << std::endl ;
	std::cout << YELLOW << "    -> Data will be extracted from " << BOLDYELLOW << argv[1] << RESET << YELLOW << RESET << std::endl ;

	
	// Count execution time
	int start_s=clock();

	
	double x1, x2, x3, x4, x5, x6, x7, x8, x9 ;
	std::string line ;
	
	
	std::string File(argv[1]); // set up a stringstream variable named convert, initialized with the input from argv[1]
	

//	cout << YELLOW << "    -> Adding box vectors to: " << BOLDYELLOW << File << RESET << endl ;
	
	std::ifstream InputFile ;
	InputFile.open( File.c_str(), ios::in );

	
	std::ofstream OutFile1 ;
	std::ofstream OutFile2 ;
	std::ofstream OutFile3 ;
	std::ofstream OutFile4 ;
	std::ofstream OutFile5 ;
	std::ofstream OutFile6 ;
	std::ofstream OutFile7 ;

	OutFile1.open("Lz.dat", ios::out );
	OutFile2.open("Lx.dat", ios::out );
	OutFile3.open("Ly.dat", ios::out );
	OutFile4.open("Pressure.dat", ios::out );
	OutFile5.open("Temperature.dat", ios::out );
	OutFile6.open("Rho_h2o.dat", ios::out );
	OutFile7.open("Volume.dat", ios::out );

	unsigned int element, atoms ;
	
	unsigned int FrameCounter = 0 ;
	while (getline(InputFile, line))
	{
		std::stringstream aa(line) ; //procesar primera línea

		if (line.length() > 80)
		{		
			aa >> element >> x1 >> x2 >> x3 >> x4 >> x5 >> x6 >> x7 >> x8 >> x9 ;
			OutFile1 << element << "  " << x8 << std::endl ;
			OutFile2 << element << "  " << x6 << std::endl ;
			OutFile3 << element << "  " << x7 << std::endl ;
			OutFile4 << element << "  " << x2 << std::endl ;
			OutFile5 << element << "  " << x1 << std::endl ;
			double Rho_h2o=2000.0/(x6*x7*(x8-50.0)) ; //+PI*100.0*50.0
			OutFile6 << element << "  " << Rho_h2o << std::endl ;
			OutFile7 << element << "  " << x9 << std::endl ;
		}
		//if ( ( line.length() < 7 ) && ( line.length() > 1 ) )
		//{
		//	aa >> atoms ;
		//	OUT << atoms << std::endl ;	
		//	OUT << BoxVectorX[FrameCounter] << "    " << BoxVectorY[FrameCounter] << "    " << BoxVectorZ[FrameCounter] << std::endl ;
		//	getline(InputFile, line) ; //procesar segunda línea (sin hacer nada)
		//	FrameCounter++ ;	
		//}
	}
	InputFile.close() ;
	OutFile1.close() ;
	OutFile2.close() ;
	OutFile3.close() ;
	OutFile4.close() ;
	OutFile5.close() ;
	OutFile6.close() ;
	OutFile7.close() ;

	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Temperature.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;
	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Pressure.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;
	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Volume.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;
	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Lx.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;
	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Ly.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;
	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Lz.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;
	std::cout << YELLOW << "    -> The file: " << BOLDYELLOW << "Rho_h2o.dat" << RESET << YELLOW << " has been created." << RESET << std::endl ;

	

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

