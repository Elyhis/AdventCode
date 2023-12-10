#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;




int main(){
    FILE * file = fopen("../../Input/006.txt","r");


    char buffer[100];
    vector<int> times;
    vector<int> dist;
    int value0, value1, value2, value3;

    fgets(buffer, 100, file);
    sscanf(buffer, "Time: %d %d %d %d", &value0, &value1, &value2, &value3);

    times.push_back(value0);
    times.push_back(value1);
    times.push_back(value2);
    times.push_back(value3);

    fgets(buffer, 100, file);
    sscanf(buffer, "Distance: %d %d %d %d", &value0, &value1, &value2, &value3);
    dist.push_back(value0);
    dist.push_back(value1);
    dist.push_back(value2);
    dist.push_back(value3);

    int counter = 0;
    int product = 1;

    for(int i = 0; i < times.size(); i++){
        for(int j = 0; j < times[i]; j++){
            if(j * (times[i] - j) > dist[i]){
                counter++;
            }
        }
        product *=counter;
        counter = 0;
    }
    cout <<" partie 1 : " << product << endl;

    uint64_t time = 0;

    for(int t : times){
        time *= 100;
        time += t; 
    }

    uint64_t distance = 0;
    int sizeNb =0;
    int n;

    for(int d : dist){
        n = d;
        while(n != 0){
            n = n /10;
            sizeNb++;
        }
        for(int i = 0; i < sizeNb;i++){
            distance *= 10;
        }
        distance += d; 
        printf("distance : %d taille du nb: %d distance totale: %llu\n",d, sizeNb, distance);
        sizeNb = 0;
    }

    for(int i = 0; i < time; i++){
        if(i * (time - i) > distance){
            counter++;
        }
    }

    cout << "partie 2 : " << counter << endl;
    return 0;
}