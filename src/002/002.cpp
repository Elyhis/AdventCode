#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;


int main(){
    FILE* file = fopen("C:/Users/Ely/Desktop/AdventCode/Input/002.txt","r");

    char color[6];
    int currentIDgame = 0;
    int sumIDGame = 0;
    int sumPowerSets = 0;
    int nbCube = 0;
    //Colors come in Red/Green/Blue
    int nbMinCubes[3] = {0,0,0};
    int maxCubes[3] = {12,13,14};
    bool validGame = true;
    
    char delimiter = '\0';


    while(fgetc(file) != EOF){
        fscanf(file, "%*s %d", &currentIDgame);
        fgetc(file);
        //cout << currentIDgame << endl;

        while(delimiter != '\n'){
            fscanf(file, "%d %[a-z]s", &nbCube, color);
            delimiter = fgetc(file);
            //cout << nbCube << " " << color << endl;
            if(color[0] == 'r'){
                validGame &= nbCube <= maxCubes[0];
                nbMinCubes[0] = max(nbMinCubes[0], nbCube);
            }
            if(color[0] == 'g'){
                validGame &= nbCube <= maxCubes[1];
                nbMinCubes[1] = max(nbMinCubes[1], nbCube);
            }
            if(color[0] == 'b'){
                validGame &= nbCube <= maxCubes[2];
                nbMinCubes[2] = max(nbMinCubes[2], nbCube);
            }
        }
        if (validGame)sumIDGame += currentIDgame;
        sumPowerSets += nbMinCubes[0]*nbMinCubes[1]*nbMinCubes[2];
        nbMinCubes[0] = 0;
        nbMinCubes[1] = 0;
        nbMinCubes[2] = 0;
        validGame = true;
        delimiter = '\0';
    }
    fclose(file);
    printf("%d : %d", sumIDGame, sumPowerSets);
    return 0;
}