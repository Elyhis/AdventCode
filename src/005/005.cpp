#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

struct seedMapping{
    int destination;
    int source;
    int offset;
};

struct interval{
    int start;
    int end;
};

void splitInterval(){
    vector<int> before;
    vector<int> intersect;
    vector<int> after;



}

void readFromFile(vector<uint64_t> &seeds, vector<vector<seedMapping*>> &mappings){
    FILE *file = fopen("C:/Users/Ely/Desktop/AdventCode/Input/005.txt","r");

    char buffer[250];
    char c = '\0';
    uint64_t n = 0;
    uint64_t seed;

    while(c != '\n'){
        if(isdigit(c)){
            while(isdigit(c)){
                n *= 10;
                n += c - '0';
                c = fgetc(file);
            }
            seeds.push_back(n);
            n = 0;
        }
    c = fgetc(file);
    }
    
    seedMapping newMap;
    while (fgets(buffer, 250, file)){
        if(buffer[0] == '\n') continue;
        vector<seedMapping*> mapping;
        while (fgets(buffer, 250, file) && buffer[0] != '\n'){
            seedMapping* nMap = new seedMapping;
            sscanf(buffer, "%llu %llu %llu", &(nMap->destination), &(nMap->source), &(nMap->offset));
            mapping.push_back(nMap);
        }
        mappings.push_back(mapping);
    }
}



int main(){
    vector<uint64_t> seeds;
    vector<vector<seedMapping*>> mappings;

    uint64_t minLocation = UINT64_MAX;
    uint64_t mOfSeed;
    readFromFile(seeds, mappings);

    for(uint64_t seed : seeds){
        mOfSeed = seed;
        for(auto map : mappings){
            for(auto m : map){
                if(mOfSeed < m->source + m->offset && mOfSeed >= m->source){
                    mOfSeed = m->destination + mOfSeed - m->source;
                    break;
                }
            }
        }
        minLocation = min(mOfSeed, minLocation);
    }

    printf("minLoc : %llu\n", minLocation);
    
    return 0;
}