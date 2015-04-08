#include "stdafx.h"

#if defined(_DO_NOT_EXPORT)
#define DllExport  
#else
#define DllExport __declspec(dllexport)
#endif

/**
* jacobi logic dll class
*/
class DllExport Jacobi {
private:
	/**
	* return value of iteration
	*/
	int result;
	int i, j, k;
	int maxI, maxJ;
	double max, fi;
	double fault;
	double** rotationMatrix;
	double** temp;

public:
	Jacobi (void);
	~Jacobi (void);
	/**
	* checks if matrix is symmetrical
	*/
	bool isSymmetrical( double **coefficient, int equation );
	/**
	* Jacobi iteration for eigenvectors 
	*/
	int iteration( double **coefficient, int equation, double **solution, double precision );
};
/**
* constructor
*/
Jacobi::Jacobi (void) {
}
/**
* destructor
*/
Jacobi::~Jacobi (void) {
}

bool Jacobi::isSymmetrical( double **coefficient, int equation ){		
	bool result = true;
	int i, j;
	for ( i = 0; i < equation; i++ ) {
		for ( j = i + 1; j < equation; j ++ ) {
			if ( coefficient[i][j] != coefficient[j][i] ) {
				result = false;
				break;}}
		if ( !result ) 
			break;
	}
	return result;
}

int Jacobi::iteration ( double **coefficient, int equation, double **solution, double precision ) {		

	result = 1;
	fault = 0.0;

	rotationMatrix = new double*[equation];
	for ( i = 0; i < equation; i ++ ) {
		rotationMatrix[i] = new double[equation];
	}
	temp = new double*[equation];
	for ( i = 0; i < equation; i ++ ) {
		temp[i] = new double[equation];
	}	
	for ( i = 0; i < equation; i ++ ) {
		for ( j = i + 1; j < equation; j ++ ) {
			fault = fault + coefficient[i][j]*coefficient[i][j];
		}
	}
	fault = sqrt( 2*fault );			  

	while ( fault > precision ) {
		max = 0.0;
		for ( i = 0; i < equation; i ++ ) {
			for ( j = i + 1; j < equation; j ++ ) {
				if ( coefficient[i][j] > 0 && coefficient[i][j] > max ) {
					max = coefficient[i][j];
					maxI = i;
					maxJ = j;
				}
				else if ( coefficient[i][j] < 0 && - coefficient[i][j] > max ) {
					max = - coefficient[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				rotationMatrix[i][j] = 0;
			}
			rotationMatrix[i][i] = 1;
		}
		if ( coefficient[maxI][maxI] == coefficient[maxJ][maxJ] ) {
			rotationMatrix[maxI][maxI] = rotationMatrix[maxJ][maxJ] = 
				rotationMatrix[maxJ][maxI] = sqrt( 2.0 ) / 2.0;
			rotationMatrix[maxI][maxJ] = - sqrt( 2.0 ) / 2.0;
		}
		else {
			fi = 0.5 * atan( ( 2.0 * coefficient[maxI][maxJ] ) /
				( coefficient[maxI][maxI] - coefficient[maxJ][maxJ] ) );
			rotationMatrix[maxI][maxI] = rotationMatrix[maxJ][maxJ] = cos( fi );
			rotationMatrix[maxI][maxJ] = - sin( fi );
			rotationMatrix[maxJ][maxI] = sin( fi );
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				temp[i][j] = 0.0;
			}
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				for ( k = 0; k < equation; k ++ ) {
					temp[i][j] = temp[i][j] + rotationMatrix[k][i] * coefficient[k][j];
				}
			}
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				coefficient[i][j] = 0.0;
			}
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				for ( k = 0; k < equation; k ++ ) {
					coefficient[i][j] = coefficient[i][j] +
						temp[i][k] * rotationMatrix[k][j];
				}
			}
		}
		fault = 0.0;
		for ( i = 0; i < equation; i ++ ) {
			for ( j = i + 1; j < equation; j ++ ) {
				fault = fault + coefficient[i][j]*coefficient[i][j];
			}
		}
		fault = sqrt( 2*fault );
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				temp[i][j] = 0.0;
			}
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				for ( k = 0; k < equation; k ++ ) {
					temp[i][j] = temp[i][j] + solution[i][k] * rotationMatrix[k][j];
				}
			}
		}
		for ( i = 0; i < equation; i ++ ) {
			for ( j = 0; j < equation; j ++ ) {
				solution[i][j] = temp[i][j];
			}
		}
		result++;
	}
	return result;
}
