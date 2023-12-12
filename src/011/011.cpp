#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    FILE * file = fopen("../../Input/011.txt","r");

    vector<vector<char>> galaxy;
    vector<int> row;
    vector<int> col;


    char buffer[150];
    char c = '\0';
    int i = 0;

    while (fgets(buffer,150,file)){
        vector<char> line;
        c = buffer[i];
        while (c != '\n' && c !=EOF){
            c = buffer[i];
            line.push_back(c);
            i++;
        }
        line.pop_back();
        i = 0;
        galaxy.push_back(line);
    }

    bool expansion = true;
    for(int i = 0; i < galaxy.size(); i++){
        for(int j = 0; j < galaxy[0].size();j++){
            if (galaxy[i][j] != '.') expansion = false;
        }
        if (expansion){
            row.push_back(i);
        }
        expansion = true;
    }
    
    for(int i = 0; i < galaxy[0].size(); i++){
        int j;
        for(j = 0; j < galaxy.size();j++){
            if (galaxy[j][i] != '.') expansion = false;
        }
        if (expansion){
            col.push_back(i);
        }
        expansion = true;
    }

    vector<pair<int,int>> points;
    for(int i = 0; i < galaxy.size(); i++){
        for(int j = 0; j < galaxy[0].size();j++){
            if (galaxy[i][j] == '#'){
                points.push_back(make_pair(i,j));
            }
        }
    }
    int ratio = 1000000;
    vector<uint64_t> distance;
    for(int i = 0; i < points.size() - 1; i++){
        for(int j = i + 1; j < points.size();j++){
            pair<int,int> current = {points[i].first, points[i].second};
            pair<int,int> B = {points[j].first, points[j].second};
            int d = 0;
            while (current.first != B.first){
                if(current.first > B.first){
                    if(find(row.begin(),row.end(),current.first) != row.end()){
                        d += ratio;
                    }else{
                        d++;
                    }
                    current.first--;
                }
                if(current.first < B.first){
                    if(find(row.begin(),row.end(),current.first) != row.end()){
                        d += ratio;
                    }else{
                        d++;
                    }
                    current.first++;
                }
            }
            while (current.second != B.second){
                if(current.second > B.second){
                    if(find(col.begin(),col.end(),current.second) != col.end()){
                        d += ratio;
                    }else{
                        d++;
                    }
                    current.second--;
                }
                if(current.second < B.second){
                    if(find(col.begin(),col.end(),current.second) != col.end()){
                        d += ratio;
                    }else{
                        d++;
                    }
                    current.second++;
                }
            }
            
            distance.push_back(d);
        }
    }
    uint64_t sum = 0;
    for(auto d : distance){
        sum += d;
    }
    cout << sum;
    return 0;
}