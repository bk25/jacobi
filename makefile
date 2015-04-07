

JacobiApp: JacobiApp.obj 
	cl /o JacobiApp.exe JacobiApp.obj   

JacobiApp.obj: JacobiApp.cpp JacobiApp.h 
	cl /c JacobiApp.cpp

all: JacobiApp 

clean:
	del  *.exe *.obj