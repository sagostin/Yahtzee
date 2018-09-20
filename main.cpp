#include <random>
#include <iostream>
#include <array>

using namespace std;

array<int, 5> dice;

//https://considerable.com/yahtzee/

int rollAllDice(){
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(1, 6);

    for (int n=0; n<5; ++n){
        dice[n] = dis(gen);
    }

    return 0;
}

void questionBuilder(char *question, int method){
    char answer;
    cout << question << "[Y/N]";
    cin >> answer;

    while(answer != 'y' || answer != 'Y' || answer != 'n' || answer != 'N') {
        cout << "You entered an invalid option.\n";
        cout << question << "[Y/N]";
        cin >> answer;
    }

    if(answer == 'y' || answer == 'Y'){
        method;
    }else{
        cout << "You chose no.";
    }
}

int main() {
    questionBuilder("Would you like to roll the dice?", rollAllDice());

    int size = dice.size();

    for(int i = 0; i<size; i++){
        cout << dice[i] << " ";
    }

    return 0;
}