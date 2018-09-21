#include <random>
#include <iostream>
#include <array>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iterator>

using namespace std;

array<int, 5> dice;
array<int, 5> heldDice;
array<int, 14> scoreCard;

//Held Dice
int held = 0;

//Roll counter
int roll = 0;

//Turn counter
int turn = 0;

//https://considerable.com/yahtzee/

void rollAndHold(){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 6);

    int answer;

    cout<<"Rolled Numbers: ";
    for (int n = 0; n < 5; ++n) {
        dice[n] = dis(gen);
        cout<<dice[n]<<" ";
    }
    cout<<"\n";

    roll++;


    cout<<"Is there dice that you would like to hold? [1=yes, 2=no]";
    cin>>answer;

    if( answer == 1 )
    {
        for( int k=0; k<5; k++ )
        {
            cout << "Would you like to keep dice #" << k+1 << "(" << dice[k] << ")? " << endl;
            cout << " Press '1' for yes or '2' for no: " << endl;
            cin >> answer;

            if( answer == 1 )
            {
                heldDice[held] = dice[k];
                held++;
            }
        }
    }
}

void score(){
    int answer;
    cout<<"\n1) 1s: "<<scoreCard[0]<<"\n2) 2s: "<<scoreCard[1]<<"\n3) 3s: "<<scoreCard[2]<<"\n4) 4s: "<<scoreCard[3]<<"\n5) 5s: "<<scoreCard[4]<<"\n6) 6s: "<<scoreCard[5]<<"\n7) 3-of-a-kind: "<<scoreCard[6]<<"\n8) 4-of-a-kind: "<<scoreCard[7]<<"\n9) full house: "<<scoreCard[8]<<"\n10) small straight: "<<scoreCard[9]<<"\n11) large straight: "<<scoreCard[10]<<"\n12) extra: "<<scoreCard[11]<<"\n13) YAHTZEE: "<<scoreCard[12]<<"\n";
    cout<<"\n\nChoose where to apply your points: ";
    cin>>answer;
    int points;

    while(scoreCard[answer-1] != -1){
        cout<<"You have already set your score for that slot.";
        cout<<"\n1) 1s: "<<scoreCard[0]<<"\n2) 2s: "<<scoreCard[1]<<"\n3) 3s: "<<scoreCard[2]<<"\n4) 4s: "<<scoreCard[3]<<"\n5) 5s: "<<scoreCard[4]<<"\n6) 6s: "<<scoreCard[5]<<"\n7) 3-of-a-kind: "<<scoreCard[6]<<"\n8) 4-of-a-kind: "<<scoreCard[7]<<"\n9) full house: "<<scoreCard[8]<<"\n10) small straight: "<<scoreCard[9]<<"\n11) large straight: "<<scoreCard[10]<<"\n12) extra: "<<scoreCard[11]<<"\n13) YAHTZEE: "<<scoreCard[12]<<"\n";
        cout<<"\n\nChoose where to apply your points: ";
        cin>>answer;
    }

    cout<<"Count points: ";
    cin>>points;
    scoreCard[answer-1] = points;
}

int main() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 6);

    scoreCard.fill(-1);

    scoreCard[13] = 0;

    while(turn < 13) {
        rollAndHold();

        if(held<5 && held > 0){
            cout<<"Held Dice: ";
            for(int i = 0; i < held; i++){
                cout<<heldDice[i]<<" ";
            }
            cout<<"New Rolled Numbers: ";
            for (int n = held; n < 5; ++n) {
                heldDice[n] = dis(gen);
                cout<<heldDice[n]<<" ";
            }
            cout<<"\n";

        }else if(held == 5) {
            score();
        }else if(held == 0){
            if(roll == 3){
                cout<<"You're on your last roll. Either put a 0 somewhere or fill in your points.";
                score();
            }
            rollAndHold();
        }
        held = 0;
        turn++;

    }

    for(int i = 0; i < 13; i++){
        scoreCard[13]+= scoreCard[i];
    }

    cout<<"-----\nTotal: " << scoreCard[13]<<"\n-----";



    return 0;
}