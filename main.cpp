#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

class BlackJack {
private:
    int* cards = new int[416];
public:
    int cc = 0; //Card Counter

    void init(); //Initialize the vector cards with 8 decks of 52 cards for a total of 416 cards;

    void printCards(); //Print all the cards in the 8 decks;

    int* getCards() { return cards; }

    BlackJack() {
        init();
    }

};

void BlackJack::init() {                                
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 13; j++) {
            for (int k = 0; k < 4; k++) {
                if (j >= 10) {
                    cards[cc] = 10;
                }
                else
                    cards[cc] = j + 1;
                cc++;
            }
        }
    }
}

void BlackJack::printCards() {
    int c = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 13; j++) {
            cout << "\n";
            for (int k = 0; k < 4; k++) {
                cout << cards[c] << " ";
                c++;
            }
        }
    }
}


int main() {
    BlackJack bj;
    bj.printCards();
}