#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;



int main(){
    vector<int> winningNumber;
    vector<int> myCard;
    vector<int> cardNumber(202,1);
    FILE *file = fopen("C:/Users/Ely/Desktop/AdventCode/Input/004.txt","r");
    char c = '\0';

    int n = 0;

    int worth = 0;
    int sum = 0;
    int counter = 0;

    for (int i = 0; i < 202; i++){
        fscanf(file, "%*s %*d");
        fgetc(file);

        while(c !='|'){
            c = fgetc(file);
            if (c != '\n' && c !=EOF){
                if(isdigit(c)){
                    while(isdigit(c)){
                        n *= 10;
                        n += c - '0';
                        c = fgetc(file);
                    }
                    winningNumber.push_back(n);
                    n= 0;
                }
            }
        }
        while (c != '\n' && c !=EOF){
            c = fgetc(file);
            if (c != '\n'){
                if(isdigit(c)){
                    while(isdigit(c)){
                        n *= 10;
                        n += c - '0';
                        c = fgetc(file);
                    }
                    myCard.push_back(n);
                    n= 0;
                }
            }
        }
        for(int n : myCard){
            for(int winningN : winningNumber){
                if(n == winningN){
                    counter++;
                    if(worth == 0){
                        worth = 1;
                    } else {
                        worth*=2;
                    }
                }
            }
        }
        sum +=worth;
        worth = 0;
        for(int j = 1; j <= counter; j++){
            if(i+j < cardNumber.size()){
                cardNumber[i+j]+= cardNumber[i]; 
            }
        }
        counter = 0;
        winningNumber.clear();
        myCard.clear();
    }
    for(int i = 0; i < cardNumber.size();i++){
        counter+= cardNumber[i];
    }
    cout << sum << endl;
    cout << counter << endl;
    return 0;
}