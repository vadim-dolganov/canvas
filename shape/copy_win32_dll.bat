@echo off

IF NOT EXIST "..\Debug\glew32.dll" (
  xcopy libs\glew\bin\Release\Win32\glew32.dll ..\Debug\ 
) 
IF NOT EXIST "..\Debug\SDL2.dll" (
  xcopy libs\SDL2\lib\x86\SDL2.dll ..\Debug\ 
) 