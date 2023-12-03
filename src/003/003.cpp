#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;


// void printTab(vector<vector<char>> mat){
//     for (int i = 0; i <= 140; i++){
//         for (int j = 0; j <= 140; j++){
//             cout << mat[i][j] << "|";
//         }
//         cout << endl;
//     }
// }

bool lookNeighbors(vector<vector<char>> &mat, int size, int i, int j,unordered_map<int,vector<int>*> &map, int n){
    bool isPartNumber= false;
    vector<int>* tempVec;

    
    for(int x = j-(j!=0); x <= j + size && x < mat.size(); x++){
        if(i >= 1){
            isPartNumber |= mat[i-1][x] != '.' && !isdigit(mat[i-1][x]);
            if(mat[i-1][x] == '*'){
                auto temp = map.find(i-1 + x * 1000);
                if(temp == map.end()){
                    tempVec =new vector<int>();
                    tempVec->push_back(n);
                    map.insert({i-1 + x * 1000,tempVec});
                }else{
                    temp->second->push_back(n);
                }
            }
        }
        if(i + 1 < mat.size()){
            isPartNumber |= mat[i+1][x] != '.' && !isdigit(mat[i+1][x]);
            if(mat[i+1][x] == '*'){
                auto temp = map.find(i+1 + x * 1000);
                if(temp == map.end()){
                    tempVec =new vector<int>();
                    tempVec->push_back(n);
                    map.insert({i+1 + x * 1000,tempVec});
                }else{
                    temp->second->push_back(n);
                }
            }
        } 
    }
    if(j >= 1){
        isPartNumber |= mat[i][j-1] != '.' && !isdigit(mat[i][j-1]);
        if(mat[i][j-1] == '*'){
                auto temp = map.find(i + (j-1) *1000);
                if(temp == map.end()){
                    tempVec =new vector<int>();
                    tempVec->push_back(n);
                    map.insert({i + (j-1) *1000,tempVec});
                }else{
                    temp->second->push_back(n);
                }
            }
    }
    if(j + size< mat[0].size()){
        isPartNumber |= mat[i][j+size] != '.' && !isdigit(mat[i][j+size]);
        if(mat[i][j+size] == '*'){
                auto temp = map.find(i+(j+size)*1000);
                if(temp == map.end()){
                    tempVec =new vector<int>();
                    tempVec->push_back(n);
                    map.insert({i+(j+size)*1000,tempVec});
                }else{
                    temp->second->push_back(n);
                }
            }
    }
    return isPartNumber;
}


int main(){
    vector<vector<char>> matrice;
    FILE *file = fopen("C:/Users/Ely/Desktop/AdventCode/Input/003.txt","r");
    char c = '\0';
    unordered_map<int,vector<int>*> map;

    for (int i = 0; i < 140; i++){
        vector<char> line;
        for (int j = 0; j <= 140; j++){
            c = fgetc(file);
            if (c != '\n' && c !=EOF){
                line.push_back(c);
            }
        } 
        matrice.push_back(line);
    }

    int length = 0;
    int n = 0;
    int sum = 0;
    int sum2 = 0;
    int j = 0; 

    for (int i = 0; i < matrice.size(); i++){
        while (j < matrice[0].size()){
            if (isdigit(matrice[i][j])){
                while (j + length < matrice[0].size() && isdigit(matrice[i][j+length])){
                    n*=10;
                    n+= matrice[i][j+length] - '0';
                    length++;
                }
                if(lookNeighbors(matrice, length, i, j, map, n)) sum += n;
                n= 0;
                j+=length;
                length = 0;
            }else{
                j++;
            }
        }
        j =0 ;
    }
    for(auto p : map){
        if(p.second->size() == 2){
            sum2 += p.second->at(0) * p.second->at(1);
        }
        delete(p.second);
    }
    printf("%d\n",sum);
    printf("%d\n",sum2);
    return 0;
}