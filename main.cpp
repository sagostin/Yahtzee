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

void rll(){

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
}

void hold(){
    int answer;

    cout<<"Is there dice that you would like to hold? [1=yes, 2=no]";
    cin>>answer;

    if( answer == 1 )
    {

            for (int k = 0; k < 5; k++) {
                if (dice[k] != 0) {
                    cout << "Would you like to keep dice #" << k + 1 << "(" << dice[k] << ")? " << endl;
                    cout << " Press '1' for yes or '2' for no: " << endl;
                    cin >> answer;

                    if (answer == 1) {
                        heldDice[held] = dice[k];
                        held++;
                    }
                }
        }
    }
}

bool calculateScore(int scoreCardSlot){
    int diceNum = scoreCardSlot + 1;
    bool success = false;
    if(scoreCardSlot < 6) {

        if(held == 0 && roll == 3) {
            scoreCard[scoreCardSlot] = 0;
            success = true;
        }else {
            map<int, int> upper;
            for (auto const &f : heldDice) {
                upper[f]++;
            }

            for (auto const &b : upper) {
                if (b.first == diceNum) {
                    scoreCard[scoreCardSlot] = b.first * b.second;
                    success = true;
                }
            }
        }
    }else{
        cout<<"you smell - debug\n";
    }

    if(!success){
        cout<<"\nYou entered an invalid dice number. You do not have those in your held die.\n";
    }

    return success;

}

void score(){
    bool success = false;
    while(!success) {
        int answer;
        cout<<"Held Dice: ";
        for(int i = 0; i < held; i++){
            cout<<heldDice[i]<<" ";
        }
        cout<<"\n";

        cout << "\n1) 1s: " << scoreCard[0] << "\n2) 2s: " << scoreCard[1] << "\n3) 3s: " << scoreCard[2] << "\n4) 4s: "
             << scoreCard[3] << "\n5) 5s: " << scoreCard[4] << "\n6) 6s: " << scoreCard[5] << "\n7) 3-of-a-kind: "
             << scoreCard[6] << "\n8) 4-of-a-kind: " << scoreCard[7] << "\n9) full house: " << scoreCard[8]
             << "\n10) small straight: " << scoreCard[9] << "\n11) large straight: " << scoreCard[10] << "\n12) extra: "
             << scoreCard[11] << "\n13) YAHTZEE: " << scoreCard[12] << "\n";
        cout << "\n\nChoose where to apply your points: ";
        cin >> answer;

        while (scoreCard[answer - 1] != -1) {
            cout<<"Held Dice: ";
            for(int i = 0; i < held; i++){
                cout<<heldDice[i]<<" ";
            }
            cout<<"\n";

            cout << "You have already set your score for that slot.";
            cout << "\n1) 1s: " << scoreCard[0] << "\n2) 2s: " << scoreCard[1] << "\n3) 3s: " << scoreCard[2]
                 << "\n4) 4s: " << scoreCard[3] << "\n5) 5s: " << scoreCard[4] << "\n6) 6s: " << scoreCard[5]
                 << "\n7) 3-of-a-kind: " << scoreCard[6] << "\n8) 4-of-a-kind: " << scoreCard[7] << "\n9) full house: "
                 << scoreCard[8] << "\n10) small straight: " << scoreCard[9] << "\n11) large straight: "
                 << scoreCard[10] << "\n12) extra: " << scoreCard[11] << "\n13) YAHTZEE: " << scoreCard[12] << "\n";
            cout << "\n\nChoose where to apply your points: ";
            cin >> answer;
        }

        int scorecardSlot = answer - 1;
        success = calculateScore(scorecardSlot);
    }
}

int main() {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 6);

    scoreCard.fill(-1);

    scoreCard[13] = 0;

    while(turn < 13) {
        while(held<5 || held == 0){
            if(held == 0){
                if(roll == 3){
                    cout<<"You're on your last roll and have not held any. Please choose a slot to put a 0.\n";
                    score();
                    break;
                }else{
                    rll();
                    hold();
                }
            }else{
                hold();
                cout << "Held Dice: ";
                for (int i = 0; i < held; i++) {
                    cout << heldDice[i] << " ";
                }

                cout << "\n";
                cout << "New Rolled Numbers: ";

                dice.fill(0);
                for (int n = 0; n < 5 - held; ++n) {
                    dice[n] = dis(gen);
                    cout << dice[n] << " ";
                }
                cout << "\n";
                roll++;

                if(roll == 3){
                    cout<<"You're on your last roll.\n";
                    if(roll == 3 && held < 5){
                        cout<< "Holding the other dice. You don't have anymore rolls.\n";
                        // TODO. FIX THIS HERE IT ONLY SAVES ONE LESS THAT IT SHOULD WHEN YOU RUN OUT OF ROLLS.
                        for( int k=0; k<6-held; k++ )
                        {
                            if(dice[k] != 0) {
                                heldDice[held] = dice[k];
                                held++;
                            }
                        }
                        score();
                        break;
                    }
                }
            }
        }

        if(held == 5) {
            score();
        }

        held = 0;
        roll= 0;
        turn++;

    }

    for(int i = 0; i < 13; i++){
        scoreCard[13]+= scoreCard[i];
    }

    cout<<"-----\nTotal: " << scoreCard[13]<<"\n-----";



    return 0;
}