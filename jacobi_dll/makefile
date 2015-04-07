jacobi_dll: jacobi_dll.obj
	cl "jacobi_dll.cpp" /link /DLL /out:jacobi_dll.dll 		

winreg_dll.obj: jacobi_dll.cpp jacobi_dll.h
	cl /c jacobi_dll.cpp


all: jacobi_dll

clean:
	del *.dll *.obj