// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBlueprintFunctionLibrary.h"
#include <Runtime\Core\Public\HAL\FileManager.h>
#include <Runtime\Core\Public\Misc\Paths.h>

#include <string>
#include <fstream>
using namespace std;


/*********************************************************/
//This founction is create for testing, not use in project/
/*********************************************************/
void UMyBlueprintFunctionLibrary::TestArray(UPARAM(ref)TArray<FVector>& oxygen, UPARAM(ref)TArray<FVector>& carbon, UPARAM(ref)TArray<FVector>& nitrogen, UPARAM(ref)TArray<FVector>& hydrogen)
{
    Coords* coord = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* coord1 = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* coord2 = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* coord3 = (Coords*)malloc(10000 * sizeof(Coords));

    //set counter
    int oxygen_count = 0;
    int carbon_count = 0;
    int nitrogen_count = 0;
    int hydrogen_count = 0;
    int o_count = 0;
    int c_count = 0;
    int n_count = 0;
    int h_count = 0;
    int end_count = -1;
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
            if (o_count == 0)
                o_count = oxygen_count;
            if (c_count == 0)
                c_count = carbon_count;
            if (n_count == 0)
                n_count = nitrogen_count;
            if (h_count == 0)
                h_count = hydrogen_count;
            if (oxygen_count == 0)
                filein >> symbol;
            while (symbol == "ATOM")
            {
                filein >> temp;
                filein >> temp;
                if (temp == "O") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord[oxygen_count].x;
                    filein >> coord[oxygen_count].y;
                    filein >> coord[oxygen_count].z;

                    oxygen_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                else if(temp == "C" || temp == "CA" || temp == "CB") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord1[carbon_count].x;
                    filein >> coord1[carbon_count].y;
                    filein >> coord1[carbon_count].z;

                    carbon_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                else if (temp == "N") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord2[nitrogen_count].x;
                    filein >> coord2[nitrogen_count].y;
                    filein >> coord2[nitrogen_count].z;

                    nitrogen_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                else if (temp == "H") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord3[hydrogen_count].x;
                    filein >> coord3[hydrogen_count].y;
                    filein >> coord3[hydrogen_count].z;

                    hydrogen_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                else {
                    for (int i = 0; i < 9; i++) {
                        filein >> temp;
                    }
                }
                filein >> symbol;
            }

        }
        end_count++;
    }

    filein.close();
    for (int i = 0; i < o_count; i++)
    {
        oxygen.Add(FVector(10 * coord[i].x, 10 * coord[i].y, 10 * coord[i].z));
    }
    for (int i = 0; i < c_count; i++)
    {
        carbon.Add(FVector(10 * coord1[i].x, 10 * coord1[i].y, 10 * coord1[i].z));
    }
    for (int i = 0; i < n_count; i++)
    {
        nitrogen.Add(FVector(10 * coord2[i].x, 10 * coord2[i].y, 10 * coord2[i].z));
    }
    for (int i = 0; i < h_count; i++)
    {
        hydrogen.Add(FVector(10 * coord3[i].x, 10 * coord3[i].y, 10 * coord3[i].z));
    }
    
    /*int total = 0;
    total = oxygen_count + carbon_count + nitrogen_count + hydrogen_count;
    int frame;
    frame = total / end_count;*/

}

/********************************************************/
//This founction is create for testing, not use in project/
/*********************************************************/
void UMyBlueprintFunctionLibrary::Frames(int frame)
{
    
    int end_count = -1;
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
        while (symbol == "END") {
            end_count++;
        }
        
    }
    filein.close();


}

//This founction is used to create atoms
void UMyBlueprintFunctionLibrary::VWDArray(int frame, UPARAM(ref)TArray<FVector>& oxygen, UPARAM(ref)TArray<FVector>& carbon, UPARAM(ref)TArray<FVector>& nitrogen, UPARAM(ref)TArray<FVector>& hydrogen)
{
    //Set arrays to store atoms coordinates
    //coord[] for Oxygen, coord1[] for Carbon, coord2[] for Nitrogen, coord3[] for Hydrogen, 
    Coords* coord = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* coord1 = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* coord2 = (Coords*)malloc(10000 * sizeof(Coords));
    Coords* coord3 = (Coords*)malloc(10000 * sizeof(Coords));

    //set counter for each atom
    //These are array index counter
    int oxygen_count = 0;
    int carbon_count = 0;
    int nitrogen_count = 0;
    int hydrogen_count = 0;
    //These record how many atoms are in each frame
    int o_count = 0;
    int c_count = 0;
    int n_count = 0;
    int h_count = 0;
    //These record how many END
    int end_count = -1;
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
            //While variable 'symbol' equals 'END' for the first time, we can get how many atoms in each frame
            if (o_count == 0)
                o_count = oxygen_count;
            if (c_count == 0)
                c_count = carbon_count;
            if (n_count == 0)
                n_count = nitrogen_count;
            if (h_count == 0)
                h_count = hydrogen_count;
            if (oxygen_count == 0)
                filein >> symbol;
            while (symbol == "ATOM")
            {//While variable 'symbol' equals 'ATOM', we can get protein information in this loop
                filein >> temp;
                filein >> temp;
                //Find Oxygen atom
                if (temp == "O" || temp == "OZ" || temp == "OH" || temp == "OH1" || temp == "OH2" || temp == "OD1" || temp == "OD2" || temp == "OG" || temp == "OG1" || temp == "OG2" || temp == "OE" || temp == "OE1" || temp == "OE2") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord[oxygen_count].x;
                    filein >> coord[oxygen_count].y;
                    filein >> coord[oxygen_count].z;

                    oxygen_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                //Find Carbon
                else if (temp == "C" || temp == "CA" || temp == "CB" || temp == "CG1" || temp == "CG2" || temp == "CD" || temp == "CZ" || temp == "CE" || temp == "CE1" || temp == "CE2") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord1[carbon_count].x;
                    filein >> coord1[carbon_count].y;
                    filein >> coord1[carbon_count].z;

                    carbon_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                //Find Nitrogen
                else if (temp == "N" || temp == "NE" || temp == "NE1" || temp == "NE2" || temp == "NH1" || temp == "NH2" || temp == "ND" || temp == "ND1" || temp == "ND2") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord2[nitrogen_count].x;
                    filein >> coord2[nitrogen_count].y;
                    filein >> coord2[nitrogen_count].z;

                    nitrogen_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                //Find Hydrogen
                else if (temp == "H") {
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }

                    filein >> coord3[hydrogen_count].x;
                    filein >> coord3[hydrogen_count].y;
                    filein >> coord3[hydrogen_count].z;

                    hydrogen_count++;
                    for (int i = 0; i < 3; i++) {
                        filein >> temp;
                    }
                }
                //Drop other atoms
                //Because other atoms are much less than these four atoms in protein
                //This software does not consider other types of atoms at present stage
                else {
                    for (int i = 0; i < 9; i++) {
                        filein >> temp;
                    }
                }
                filein >> symbol;
            }

        }
        end_count++;
    }

    filein.close();

    int total = 0;
    total = oxygen_count + carbon_count + nitrogen_count + hydrogen_count;
    int frames;
    frames = total / end_count;

    //Set default value
    if (frame < 1)
        frame = 1;
    //Since all the coordinates are stored in an array
    //We need to add the frame to index to get the correct data
    int O_num, C_num, N_num, H_num;
    O_num = o_count * (frame - 1);
    C_num = c_count * (frame - 1);
    N_num = n_count * (frame - 1);
    H_num = h_count * (frame - 1);

    //Due to the density of coordinate data
    //The expansion of 10 times is convenient for display
    for (int i = 0; i < o_count; i++)
    {
        oxygen.Add(FVector(10 * coord[i + O_num].x, 10 * coord[i + O_num].y, 10 * coord[i + O_num].z));
    }
    for (int i = 0; i < c_count; i++)
    {
        carbon.Add(FVector(10 * coord1[i + C_num].x, 10 * coord1[i + C_num].y, 10 * coord1[i + C_num].z));
    }
    for (int i = 0; i < n_count; i++)
    {
        nitrogen.Add(FVector(10 * coord2[i + N_num].x, 10 * coord2[i + N_num].y, 10 * coord2[i + N_num].z));
    }
    for (int i = 0; i < h_count; i++)
    {
        hydrogen.Add(FVector(10 * coord3[i + H_num].x, 10 * coord3[i + H_num].y, 10 * coord3[i + H_num].z));
    }

}

