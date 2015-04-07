winreg_dll: winreg_dll.obj
	cl "winreg_dll.cpp" /link /DLL /out:winreg_dll.dll 		

winreg_dll.obj: winreg_dll.cpp winreg_dll.h
	cl /c winreg_dll.cpp


all: winreg_dll

clean:
	del *.dll *.obj