#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


const vector<string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

vector<string> readFromFile(fstream &f){
    vector<string> values;
    string line;
    while (f){
        f >> line;
        values.push_back(line);
    }
    values.pop_back();
    return values;
}

vector<string> calibrationValues(vector<string> val){
    vector<string> res;
    string firstNumber = "";
    string lastNumber = "";

    for(int i = 0; i < val.size(); i++){
        for(int j = 0; j < val[i].size(); j++){
            if(isdigit(val[i][j])){
                if(firstNumber == ""){
                    firstNumber = val[i][j];
                }else{
                    lastNumber = val[i][j];
                }
            }else{
                for(int k = 0; k < 9;k++ ){
                    if(val[i].substr(j).rfind(numbers[k],0) == 0){
                        if(firstNumber == ""){
                            firstNumber =  to_string(k+1);
                        }else{
                            lastNumber = to_string(k+1);
                        }
                        j += numbers[k].size() - 2;
                        break;
                    }
                }
            }
        }
        if(lastNumber == ""){
            res.push_back(firstNumber + firstNumber);
        }else{
            res.push_back(firstNumber + lastNumber);
        }
        firstNumber = "";
        lastNumber = "";
    }
    return res;
}

int main(){
    
    fstream file;

    file.open("../../Input/001.txt",ios_base::in);
    vector<string> values = readFromFile(file);
    file.close();

    values = calibrationValues(values);

    int sum = 0;
    for(int i = 0; i < values.size(); i++){
        sum += stoi(values[i]);
    }
    cout << sum << endl;
    return 0;
}