#include "stdafx.h"
/**
* windows registry dll class
*/

#if defined(_DO_NOT_EXPORT)
#define DllExport  
#else
#define DllExport __declspec(dllexport)
#endif

class DllExport Winreg {
private:

	HKEY key;

public:
	Winreg (LPCSTR lpSubKey);
	~Winreg ();

	char readdata(LPCSTR lpSubKey);
	int writedata(LPCSTR lpSubKey, char value[1024]);
};

/**
* constructor. establishes registry access
*/
Winreg::Winreg (LPCSTR lpSubKey) {
	if (RegOpenKeyA(HKEY_CURRENT_USER, lpSubKey, &key) != ERROR_SUCCESS)
		cout << "Unable to open registry key" << endl;
	else 
		cout << "Registry access established" << endl;

}

/**
* desctructor
*/
Winreg::~Winreg () {
	RegCloseKey(key);
}

/**
* reading data from registry. cout'ing values
*/
char Winreg::readdata(LPCSTR lpSubKey) {
	char value[1024];
	DWORD value_length = 1024;
	if(RegQueryValueExA(key, lpSubKey, NULL, NULL, (LPBYTE)&value, &value_length) != ERROR_SUCCESS ) {
		cout << "Unable to read key value";
	} else {
		cout << "Last selected value of " << lpSubKey << ": " << value << endl;
	}
	return *value;
}

/**
* writing data to registry
*/
int Winreg::writedata(LPCSTR lpSubKey, char value[1024]) {
	if (RegSetValueExA(key, lpSubKey, 0, REG_SZ, (LPBYTE)value, strlen(value)*sizeof(char)) != ERROR_SUCCESS)
	{
		cout <<"Unable to set key value";
	}
	return 0;
}