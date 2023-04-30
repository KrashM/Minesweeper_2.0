@echo off

g++ Program.cpp -I C:/Libraries/SFML/include -L C:/Libraries/SFML/lib -l sfml-graphics-s -l sfml-window-s -l sfml-system-s -l opengl32 -l freetype -l winmm -l gdi32 -D SFML_STATIC -o main.exe
main.exe
del main.exe