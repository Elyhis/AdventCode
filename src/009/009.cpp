#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

vector<int> diff(vector<int> val){
    vector<int> temp;
    for(int i = 0; i < val.size() - 1; i++){
        temp.push_back(val[i+1] - val[i]);
    }
    return temp;
}

bool allZero(vector<int> val){
    for(int i = 0; i < val.size(); i++){
        if(val[i] != 0) return false;
    }
    return true;
}

int main(){
    FILE * file = fopen("../../Input/009.txt","r");
    vector<vector<int>> sequences;
    char buffer[150];
    string str;


    int n = 0;
    char c = '\0';
    size_t pos = 0;
    string token;

    while (fgets(buffer,150,file)){
        str = buffer;
        str.pop_back();
        vector<int> temp;
        while ((pos = str.find(" ")) != string::npos){
            token = str.substr(0,pos);
            str.erase(0,pos + 1);
            n = stoi(token);
            temp.push_back(n);
        }
        pos = str.find('\n');
        token = str.substr(0,pos);
        str.erase(0,pos + 1);
        n = stoi(token);
        temp.push_back(n);
        sequences.push_back(temp);
    }

    int j = 0 ;
    for(int i= 0; i < sequences.size();i++){
        vector<vector<int>> differences;
        differences.push_back(diff(sequences[i]));
        j = 0;
        while (!allZero(differences[j])){
            differences.push_back(diff(differences[j]));
            j++;
        }
        int rightValue;
        int leftValue;
        while(j > 0){
            rightValue = differences[j][differences[j].size()-1] + differences[j-1][differences[j-1].size()-1];
            leftValue = differences[j-1][0] - differences[j][0]; 
            differences[j-1].push_back(rightValue);
            differences[j-1][0] = leftValue;
            j--;
        }
        sequences[i].push_back(rightValue + sequences[i][sequences[i].size()-1]);
        sequences[i][0] = sequences[i][0] - leftValue;
        differences.clear();
    }
    uint64_t rightSum = 0;
    uint64_t leftSum = 0;
    for(auto s : sequences){
        rightSum += s[s.size()-1];
        leftSum += s[0];
    }
    cout << rightSum << endl;
    cout << leftSum << endl;
    return 0;
}