@echo off
g++ -o main.exe Program.cpp src/*.cpp
main.exe
del main.exe