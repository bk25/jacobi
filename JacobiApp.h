#include "stdafx.h"
#include "jacobi_dll\jacobi_dll.h"
#include "winreg_dll\winreg_dll.h"


/**
 * definitions
 */
#if M_SIZE>4; 
#undef M_SIZE; 
#endif;
#ifndef M_SIZE;
#define M_SIZE 2; 
#endif;
#if PRECISION>1; 
#undef PRECISION; 
#endif;
#ifndef PRECISION;
#define PRECISION 0.01;
#endif;

/**
 * main class of application
 */
class JacobiApp {
private:

	/**
	* defines whatever application runs deffault or user settings
	*/
	bool def;

	/**
	* registry path
	*/
	LPCSTR path;

public:
	/**
	* constructor
	*/
	JacobiApp(bool def=false, LPCSTR path = "Software\\JevgeniAnttonen\\");
	/**
	* destructor
	*/
	~JacobiApp();

	/**
	* checks for arguments of application
	*/
	bool arglist(int argc, char* argv[]);
	void setDef (bool def){this->def=def;}	
	bool getDef (){return def;}
	void setPath (LPCSTR path){this->path=path;}	
	LPCSTR getPath (){return path;}

};

JacobiApp::JacobiApp(bool def, LPCSTR path)
	: def(def), path(path) {
}

JacobiApp::~JacobiApp(){
}

/**
* looping arguments
*/
bool JacobiApp::arglist (int argc, char* argv[]){
	path = "Software\\JevgeniAnttonen\\";	// default path
	def = false;
	if (argc < 2) { 
	cout << "No arguments found. Use -h to show argument list\n"; 
	return false;
    } else {
		for (int i = 1; i < argc; i++) {

				//cout << argv[i] << endl;		
				if (string(argv[i]) == "-h") {		// help
					cout << "-h : help" << endl;
					cout << "-r : select reigstry path" << endl;
					cout << "-d : use default settings (matrix size:2, precision:0.01)" << endl;
					return false;
                } else if (string(argv[i])  == "-r") {	// registry path change
					cout << "Enter existing registry path (default Software\\JevgeniAnttonen\\ ) :";
					string str;
					cin>>str;
					path = str.c_str();
                } else if (string(argv[i])  == "-d") {	// run using default matrix size and precision (2, 0.01)
					def = true;
                } else {
					cout << "Not enough or invalid arguments, use -h for help\n";
					return false;
				}
		}
		return true;
	}
}
