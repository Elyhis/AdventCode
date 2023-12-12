#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const vector<char> valueCard = {'A','K','Q','J','T','9','8','7','6','5','4','3','2'};

struct Player{
    string hand;
    int bid;
    int strength;
};

int getIndex(char c){
    int i = 0;
    while(c != valueCard[i]){
        i++;
    }
    if(i > 12) return -1;
    return i;
}

bool comp(Player* p1, Player* p2){
    if(p1->strength != p2->strength) return p1->strength < p2->strength;
    for(int i = 0; i < p1->hand.size(); i++){
        if(p1->hand[i] != p2->hand[i]) return getIndex(p1->hand[i]) > getIndex(p2->hand[i]);  
    }
    return false;
}

void setStrength(Player &p){
    int counter = 1;
    for(int i = 0; i < p.hand.size()-1; i++){
        for(int j = i + 1; j < p.hand.size(); j++){
            if(p.hand[i] == p.hand[j]) counter++;
        }
        switch (counter){
        case 5:
            //Five of a kind
            p.strength = 6;
            break;
        
        case 4:
            //Four of a kind
            p.strength = 5;
            break;
        case 3:
            if(p.strength == 1){
                //Full house
                p.strength = max(p.strength,4);
            }else{
                //Three of a kind
                p.strength = max(p.strength,3);
            }
            break;
        case 2:
            if(p.strength == 1){
                //Two Pair
                p.strength = max(p.strength,2);
            } else{
                //Pair
                p.strength = max(p.strength,1);
            }
            break;
        case 1:
            //Highest Value
            p.strength = max(p.strength,0);
            break;
        }
        counter = 1;
    }
}

int main(){
    FILE* file = fopen("../../Input/007.txt","r");
    char buffer[100];
    vector<Player*> players;
    char cards[6];
    int temp;


    while (fgets(buffer,100, file)){
        Player* p = new Player;
        sscanf(buffer,"%s %d", &cards, &temp);
        p->hand = cards;
        p->bid = temp;
        players.push_back(p);
    }
    
    for(auto player : players){
        setStrength(*player);
    }
    sort(players.begin(), players.end(), comp);
    uint64_t sum = 0;
    for(int i = 0; i < players.size();i++){
        sum += players[i]->bid * (i+1);
    }
    cout << sum;
    return 0;
}