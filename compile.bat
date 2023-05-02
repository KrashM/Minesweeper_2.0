@echo off

set batch_dir=%~dp0
g++ %batch_dir%\Program.cpp %batch_dir%\src\*.cpp -I C:\Libraries\SFML\include -L C:\Libraries\SFML\lib -l sfml-graphics-s -l sfml-window-s -l sfml-system-s -l opengl32 -l freetype -l winmm -l gdi32 -D SFML_STATIC -o %batch_dir%\main.exe
%batch_dir%\main.exe
del %batch_dir%\main.exe