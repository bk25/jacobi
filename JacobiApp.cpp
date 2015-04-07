// JacobiApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "JacobiApp.h"
/**
* main function
*/
int main(int argc, char* argv[], char* env[])
{
	JacobiApp *japp = new JacobiApp();
	if (!japp->arglist(argc, argv)){
		return 0;
	}


	LPCSTR path = japp->getPath();

	Winreg *winreg = new Winreg(path);
	Jacobi *jacobi = new Jacobi();

	int i, j;
	int size;
	char *str = new char[1024];
	string answer;
	double **coefficient, **solution, precision;
	winreg->readdata("size");
	winreg->readdata("precision");
	
	if (!japp->getDef()){
		cout << "Jacobi rotation method for symmetrical matrixes. Enter the matrix size: ";
		cin >> size;
	} else {
		size = M_SIZE;
	}
	winreg->writedata("size", itoa(size, str, 10));

	if (!japp->getDef()){
		cout << "Enter the precision of calculation (ie 0.01): ";
		cin >> precision;
	} else {
		precision = PRECISION;
	}
	stringstream ss;
	ss << precision;
	winreg->writedata("precision", (char*)ss.str().c_str());

	cout << "\nEnter matrix elements: \n";
	coefficient = new double*[size];
	solution = new double*[size];

	for ( i = 0; i < size; i++ ) {
		coefficient[i] = new double[size];
		solution[i] = new double[size];
	}
	for ( i = 0; i < size; i ++ ){
		for ( j = 0; j < size; j ++ ){
			solution[i][j] = 0;}
		solution[i][i] = 1;}
	for ( i = 0; i < size; i ++ ){
		cout << "Enter " << i + 1 << " row: ";
		for ( j = 0; j < size; j ++ ){
			cin >> coefficient[i][j];
		}
	}

	if ( !jacobi->isSymmetrical( coefficient, size ) ) {
		cout << "Matrix is not symmetrical";}
	else {
		int steps = jacobi->iteration( coefficient, size, solution, precision );
		cout << "Result:\n";
		for ( i = 0; i < size; i++ ) {
			cout << "Eigenvector k " << i + 1 << ":\n";
			for ( j = 0; j < size; j ++ ){
				cout << solution[j][i] << "\n";
			}
		}
		cout << "Eigenvalues:\n";
		for ( i = 0; i < size; i++ ) {
			cout << coefficient[i][i] << "\n";
		}
		cout << "Number of steps: " << steps << "\n";
	}
	return 0;
}

