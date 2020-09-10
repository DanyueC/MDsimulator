# MSc-project
MSc project

Blueprint-CPK.uasset and Blueprint-VDW.uasset contains blueprint scripts of VDW and CPK modelling method

A demonstration video
- Demo.mp4

A trajectory file for demo
- alaninedipep_trajectory.pdb

Blueprint function C++ Class
- ATOM.h              // load atoms position array
- ATOM.cpp
- CPK.h	    // load sticks position and direction vector array
- CPK.cpp

 A logo for this software
- Logo.png

Important:
The software cannot load files chose by users. If users want to change the simulated file, they have to modify the file path in the code.
They are located in CPK.cpp line 33 and ATOM.cpp line 211
