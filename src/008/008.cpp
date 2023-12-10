#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <vector>
#include <numeric>
using namespace std;


int calcDistance(string elm, string path, unordered_map<string,tuple<string,string>> map){
    int i = 0;
    while(elm != "ZZZ"){
        if(path[i % path.size()] == 'L'){
            elm = get<0>(map.find(elm)->second);
        }else{
            elm = get<1>(map.find(elm)->second);
        }
        i++;
    }
    return i;
}

int main(){
    FILE * file = fopen("../../Input/008.txt","r");
    string path = "";
    unordered_map<string,tuple<string,string>> map;
    char buffer[280];

    fgets(buffer, 280, file);
    path = buffer;
    path.pop_back();

    fgetc(file);
    char base[5];
    char left[5];
    char right[5];

    while(fgets(buffer, 50, file)){
        sscanf(buffer, "%[^ ]"" = ""(""%[^,]"", ""%[^)]"")", &base, &left, &right);
        map.insert(make_pair(base,make_tuple(left,right)));
    }

    uint64_t i = calcDistance("AAA",path,map);
    
    vector<string> currentElms;

    for(auto m : map){
        if(m.first[2] == 'A') currentElms.push_back(m.first);
    }

    uint64_t sum = 0;
    uint64_t step = 0;
    for(int i = 0; i < currentElms.size(); i++){
        while(currentElms[i][2] != 'Z'){
            if(path[i % path.size()] == 'L'){
                currentElms[i] = get<0>(map.find(currentElms[i])->second);
            }else{
                currentElms[i] = get<1>(map.find(currentElms[i])->second);
            }
            step++;
            printf("\r%llu",step);
        }
        sum+= step;
        printf("\r%llu\n",step);

        step = 0;
    }

    printf("%d\n",i);
    uint64_t ppcm = lcm(1, sum);
    cout << ppcm << endl;
    return 0;
}