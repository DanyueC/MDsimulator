// Fill out your copyright notice in the Description page of Project Settings.


#include "CPK.h"

#include <Runtime\Core\Public\HAL\FileManager.h>
#include <Runtime\Core\Public\Misc\Paths.h>

#include <string>
#include <fstream>
#include <math.h>
using namespace std;

void UCPK::CPKArray(int frame, UPARAM(ref)TArray<FVector>& stick, UPARAM(ref)TArray<FVector>& direction)
{
    //Set arrays to store atoms coordinates
    //coord[] for atoms, stick_coord[] for chemical bonds position, angle[] stores direction vectors between two atoms
    Coords* coord = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* stick_coord = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* angle = (Coords*)malloc(10000 * sizeof(Coords));

    //Set counter
    //Count how many 'END' in this pdb file
    int end_count = -1;
    //Index of atoms sequence
    int array_count = 0;
    //Count how many atoms need be display
    int atom_count = 0;

    //Read file
    //Define filename
    string fname;
    fname = "E:/Workspace/UE4/0822/MyProject/Source/MyProject/alaninedipep_trajectory.pdb";
    //Define type of data
    string symbol;
    //Define a string to store useless data
    string temp;
    //Open file
    ifstream filein;


    filein.open(fname);
    while (!filein.eof())
    {
        filein >> symbol;
        while (symbol != "END") {
            //While variable 'symbol' equals 'END' for the first time, we can get how many atoms in each frame
            if (atom_count == 0)
                atom_count = array_count;
            if (array_count == 0)
                filein >> symbol;
            while (symbol == "ATOM")
            {//While variable 'symbol' equals 'ATOM', we can get protein information in this loop
                //In this loop, we don't need to know what atom it is, but only atoms position. So jump to the x,y,z!
                for (int i = 0; i < 5; i++) {
                    filein >> temp;
                }
                //x,y,z value
                filein >> coord[array_count].x;
                filein >> coord[array_count].y;
                filein >> coord[array_count].z;
                //Index plus 1
                array_count++;
                //Drop useless data
                for (int i = 0; i < 3; i++) {
                    filein >> temp;
                }
                filein >> symbol;
            }

        }
        //Counter plus 1
        end_count++;
    }

    filein.close();

    //s is index of sticks array, ang is index of direction vectors array
    int s = 0;
    int ang = 0;

    //Each stick is start from atoms in main chain
    //From PDB file documentation I found that, except for the first residue, the atoms in the main chain are in the array with an index singular position
    //Need to reorder it for every frame
    //j is frame number
    for (int j = 0; j < end_count; j++) {
        //First residue
        //Choose the one at coord[1]
        for (int i = 0; i < 3; i++) {
            stick_coord[s].x = coord[1 + j * atom_count].x;
            stick_coord[s].y = coord[1 + j * atom_count].y;
            stick_coord[s].z = coord[1 + j * atom_count].z;
            s++;
            //Find direction vector from coord[1] to [0],[2],[3]
            if (i == 0)
            {
                angle[ang].x = coord[1 + j * atom_count].x - coord[j * atom_count].x;
                angle[ang].y = coord[1 + j * atom_count].y - coord[j * atom_count].y;
                angle[ang].z = coord[1 + j * atom_count].z - coord[j * atom_count].z;
                ang++;
            }
            else if(i == 1){
                angle[ang].x = coord[1 + j * atom_count].x - coord[2 + j * atom_count].x;
                angle[ang].y = coord[1 + j * atom_count].y - coord[2 + j * atom_count].y;
                angle[ang].z = coord[1 + j * atom_count].z - coord[2 + j * atom_count].z;
                ang++;
            }
            else if (i == 2) {
                angle[ang].x = coord[1 + j * atom_count].x - coord[3 + j * atom_count].x;
                angle[ang].y = coord[1 + j * atom_count].y - coord[3 + j * atom_count].y;
                angle[ang].z = coord[1 + j * atom_count].z - coord[3 + j * atom_count].z;
                ang++;
            }
        }
        //From the second residue
        //Get every singular index position of coord[]
        for (int i = 3; i < atom_count - 1; i = i + 2)
        {
            //As every atom in main chain points to the next atom and the next of next
            //So add two sticks from the same position
            stick_coord[s].x = coord[i + j * atom_count].x;
            stick_coord[s].y = coord[i + j * atom_count].y;
            stick_coord[s].z = coord[i + j * atom_count].z;

            stick_coord[s + 1].x = coord[i + j * atom_count].x;
            stick_coord[s + 1].y = coord[i + j * atom_count].y;
            stick_coord[s + 1].z = coord[i + j * atom_count].z;

            //And then add direction vectors
            angle[ang].x = coord[i + j * atom_count].x - coord[i + 1 + j * atom_count].x;
            angle[ang].y = coord[i + j * atom_count].y - coord[i + 1 + j * atom_count].y;
            angle[ang].z = coord[i + j * atom_count].z - coord[i + 1 + j * atom_count].z;

            angle[ang + 1].x = coord[i + j * atom_count].x - coord[i + 2 + j * atom_count].x;
            angle[ang + 1].y = coord[i + j * atom_count].y - coord[i + 2 + j * atom_count].y;
            angle[ang + 1].z = coord[i + j * atom_count].z - coord[i + 2 + j * atom_count].z;
            
            s += 2;
            ang += 2;
        }
    }
    

    if (frame < 1)
        frame = 1;
    //Since all the coordinates are stored in an array
    //We need to add the frame to index to get the correct data
    int stick_num;
    stick_num = (atom_count-1) * (frame - 1);
    //Due to the density of coordinate data
    //The expansion of 10 times is convenient for display
    for (int i = 0; i < atom_count-1; i++)
    {
        stick.Add(FVector(10 * stick_coord[i + stick_num].x, 10 * stick_coord[i + stick_num].y, 10 * stick_coord[i + stick_num].z));
    }
    //Direction vectory don't need 10 times
    for (int i = 0; i < atom_count - 1; i++)
    {
        direction.Add(FVector(angle[i + stick_num].x, angle[i + stick_num].y, angle[i + stick_num].z));
    }
}


//This founction is not used, this is future work
//This founction is not used, this is future work
//This founction is not used, this is future work
void UCPK::NewArray(int frame, UPARAM(ref)TArray<FVector>& newpoint)
{
    Coords* coord = (Coords*)malloc(10000 * sizeof(Coords));

    //set counter
    int end_count = -1;
    int array_count = 0;
    int atom_count = 0;
    //define filename
    string fname;
    fname = "E:/Workspace/UE4/0822/MyProject/Source/MyProject/alaninedipep_trajectory.pdb";
    //define type of data
    string symbol;
    //define a string to store useless data
    string temp;
    //open file
    ifstream filein;


    filein.open(fname);
    while (!filein.eof())
    {
        filein >> symbol;
        while (symbol != "END") {
            if (atom_count == 0)
                atom_count = array_count;
            if (array_count == 0)
                filein >> symbol;
            while (symbol == "ATOM")
            {
                for (int i = 0; i < 5; i++) {
                    filein >> temp;
                }

                filein >> coord[array_count].x;
                filein >> coord[array_count].y;
                filein >> coord[array_count].z;

                array_count++;
                for (int i = 0; i < 3; i++) {
                    filein >> temp;
                }
                filein >> symbol;
            }

        }
        end_count++;
    }

    filein.close();

    if (frame < 1)
        frame = 1;

    //frame = 3;

    newpoint.Add(FVector(10 * coord[frame * atom_count].x, 10 * coord[frame * atom_count].y, 10 * coord[frame * atom_count].z));
    for (int i = 3; i < atom_count; i+=2)
    {
        newpoint.Add(FVector(10 * coord[i + frame * atom_count].x, 10 * coord[i + frame * atom_count].y, 10 * coord[i + frame * atom_count].z));
    }
}
