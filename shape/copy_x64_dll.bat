@echo off

IF NOT EXIST "..\x64\Debug\glew32.dll" (
  xcopy libs\glew\bin\Release\x64\glew32.dll ..\x64\Debug\ 
) 
IF NOT EXIST "..\x64\Debug\SDL2.dll" (
  xcopy libs\SDL2\lib\x64\SDL2.dll ..\x64\Debug\ 
) 