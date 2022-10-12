#include <iostream>
#include <Windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class BlackJack {
private:
    int* cards = new int[416];
public:
    int givenCards; //Cards given
    int cc = 0; //Card Counter
    void init(); //Initialize the vector cards with 8 decks of 52 cards for a total of 416 cards;
    void printCards(); //Print all the cards in the 8 decks;
    void mesh(); //Mesh the 8 decks of cards together;
    int* getCards() { return cards; } //Return the array which contains the cards;

    BlackJack() {
        givenCards = 0;
        init();
        mesh();
    }
};

class Game : public BlackJack {
private:
    int* userDeck = new int[2];
    int* cpuDeck = new int[2];
    int* cards = new int[416];
    int* userCardsCalled = new int[10];
    int* cpuCardsCalled = new int[10];
public:
    int userCards = 0;
    int cpuCards = 0;
    bool userTurn = true;
    bool Called = false;
    bool end = false;

    Game() {
        cards = getCards();
        giveCards();
    }

    bool usercall();

    //void cpucall();

    void printGame();

    void win() {

    }
    void lose() {
        MessageBoxA(0, "You lost", "Lost", 0);
        reset();
        //exit(-1);
    }

    bool checkSum();

    int getSum();

    void checkWhoWon() {

    }
    void giveCards();

    void checkIfAce() {
    }

    void reset();
};

void Game::reset() {
    std::fill_n(userCardsCalled, userCards, 0);
    std::fill_n(cpuCardsCalled, cpuCards, 0);
    userCards = 0;
    cpuCards = 0;
    giveCards();
    userTurn = true;
    Called = false;
    end = false;
}

int Game::getSum() {
    int sum = 0;
    for (int i = 0; i < userCards; i++) {
        sum += userCardsCalled[i];
    }
    sum = sum + userDeck[0] + userDeck[1];

    return sum;
}

bool Game::checkSum() {
    int sum = 0;
    for (int i = 0; i < userCards; i++) {
        sum += userCardsCalled[i];
    }
    sum = sum + userDeck[0] + userDeck[1];

    if (sum > 21)
        return false;

    return true;
}

bool Game::usercall() {
    userCardsCalled[userCards] = cards[givenCards];
    userCards++;
    givenCards++;
    Called = true;
    if (checkSum()) {
        return true;
    }
    else
        return false;
}

void Game::printGame() {
    system("cls");
    int choice = 0;
    if (userTurn) {
        cout << " Cpu Cards \n" << "  |*|" << " " << cpuDeck[1] << "\n\n";
        cout << " Your Cards \n" << "   " << userDeck[0] << " " << userDeck[1] << " (" << getSum() << ")\n";
        if (Called) {
            for (int i = 0; i < userCards; i++) {
                cout << "Cards Called: " << userCardsCalled[i] << " " << "\n";
            }
        }
    }
    else {
        cout << " Cpu Cards \n" << "   " << cpuDeck[0] << " " << cpuDeck[1] << "\n\n";
        cout << " Your Cards \n" << "   " << userDeck[0] << " " << userDeck[1] << "(" << getSum() << ")\n";
        if (Called) {
            for (int i = 0; i < userCards; i++) {
                cout << "Cards Called: " << userCardsCalled[i] << " " << "\n";
            }
        }
    }

    cout << "\n\n1) Call | 2) Stay | 3) Double \n\n>> ";
    cin >> choice;
    do {
        if (choice == 1)
            if (!usercall())
                lose();
        //else if (choice == 2)
    //else if (choice == 3)
    } while (choice < 0 || choice > 3);
}

void Game::giveCards() {
    for (int i = 0; i < 2; i++) {
        userDeck[i] = cards[givenCards];
        givenCards++;
    }
    for (int i = 0; i < 2; i++) {
        cpuDeck[i] = cards[givenCards];
        givenCards++;
    }
}

void BlackJack::mesh() {
    srand(time(0));
    int r, r1, temp;
    for (int i = 0; i < 10000; i++) {
        r = rand() % 416;
        r1 = rand() % 416;
        temp = cards[r];
        cards[r] = cards[r1];
        cards[r1] = temp;
    }
}

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
    Game game;
    while (!game.end)
        game.printGame();

}