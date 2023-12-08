call premake5.exe vs2022

@echo off
if not exist "./include" (
  mkdir include
)

if exist "./lib" (
  mkdir lib
)

@echo on

pause