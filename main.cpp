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
    int userAce = 0;
    int cpuAce = 0;
    bool userTurn = true;
    bool Called = false;
    bool end = false;
    bool cpuCalled = false;
    bool stayed = false;

    Game() {
        cards = getCards();
        giveCards();
    }

    bool usercall();

    void cpucall();

    void printGame();

    void win();
    void lose();
    void draw();

    bool checkSum(string deck);

    int getSum(string deck);

    void stay();

    void giveCards();

    void checkIfAce(string deck);

    void reset();

    void callLose();
};

void Game::checkIfAce(string deck) {
    if (deck == "user") {
        if ((userDeck[0] == 1 || cpuDeck[1] == 1) && getSum("user") + 10 <= 21) {
            userAce = 10;
        }
        else
            userAce = 0;
        for (int i = 0; i < userCards; i++) {
            if (userCardsCalled[i] == 1 && (getSum("user") + 10) <= 21) {
                userAce = 10;
            }
            else
                userAce = 0;
        }
    }
    else {
        if ((cpuDeck[0] == 1 || cpuDeck[1] == 1) && (getSum("cpu") + 10) <= 21)
            cpuAce = 10;
        else
            cpuAce = 0;
        for (int i = 0; i < cpuCards; i++) {
            if (cpuCardsCalled[i] == 1 && (getSum("cpu") + 10) <= 21) {
                cpuAce = 10;
            }
            else
                cpuAce = 0;
        }
    }
}

void Game::callLose() {
    MessageBoxA(0, "The sum of your cards was higher than 21!", "Lost!", 0);
    reset();
}

void Game::draw() {
    MessageBoxA(0, "Draw", "Draw", 0);
    reset();
}

void Game::win() {
    MessageBoxA(0, "You won", "Win!", 0);
    reset();
}

void Game::cpucall() {
    cpuCardsCalled[cpuCards] = cards[givenCards];
    givenCards++;
    cpuCards++;
    cpuCalled = true;
}

void Game::stay() {
    stayed = true;
    userTurn = false;
    while (getSum("cpu") < 17) {
        cpucall();
        printGame();
    }
    printGame();
    if (getSum("cpu") < getSum("user") || getSum("cpu") > 21) {
        win();
    }
    else if (getSum("cpu") == 21 && getSum("user") == 21)
    {
        draw();
    }

    else if (getSum("cpu") >= getSum("user") && getSum("cpu") <= 21) {
        lose();
    }

}


void Game::lose() {
    MessageBoxA(0, "You lost", "Lost", 0);
    reset();
}

void Game::reset() {
    std::fill_n(userCardsCalled, userCards, 0);
    std::fill_n(cpuCardsCalled, cpuCards, 0);
    userCards = 0;
    userAce = 0;
    cpuAce = 0;
    cpuCards = 0;
    giveCards();
    stayed = false;
    userTurn = true;
    Called = false;
    end = false;
}

int Game::getSum(string deck) {
    int sum = 0;
    if (deck == "user") {
        for (int i = 0; i < userCards; i++) {
            sum += userCardsCalled[i];
        }
        sum = sum + userDeck[0] + userDeck[1] + userAce;
    }
    else {
        for (int i = 0; i < cpuCards; i++) {
            sum += cpuCardsCalled[i];
        }
        sum = sum + cpuDeck[0] + cpuDeck[1] + cpuAce;
    }

    return sum;
}

bool Game::checkSum(string deck) {
    int sum = 0;
    if (deck == "user") {
        for (int i = 0; i < userCards; i++) {
            sum += userCardsCalled[i];
        }
        sum = sum + userDeck[0] + userDeck[1] + userAce;
    }
    else {
        for (int i = 0; i < cpuCards; i++) {
            sum += cpuCardsCalled[i];
        }
        sum = sum + cpuDeck[0] + cpuDeck[1] + cpuAce;
    }


    if (sum > 21)
        return false;

    return true;
}

bool Game::usercall() {
    userCardsCalled[userCards] = cards[givenCards];
    userCards++;
    givenCards++;
    Called = true;
    if (checkSum("user")) {
        return true;
    }
    else
        return false;
}

void Game::printGame() {
    system("cls");
    int choice = 0;
    checkIfAce("user");
    checkIfAce("cpu");
    if (userTurn) {
        cout << " Cpu Cards \n" << "  |*|" << " " << cpuDeck[1] << "\n\n";
        cout << " Your Cards \n" << "   " << userDeck[0] << " " << userDeck[1] << " (" << getSum("user") << ")\n";
        if (Called) {
            cout << "Cards Called: ";
            for (int i = 0; i < userCards; i++) {
               cout << userCardsCalled[i] << " ";
            }
        }
    }
    else {
        cout << " Dealer Cards \n" << "   " << cpuDeck[0] << " " << cpuDeck[1] << " (" << getSum("cpu") << ")\n\n";
        if (cpuCalled) {
            cout << "Dealer Called: ";
            for (int i = 0; i < cpuCards; i++) {
                 cout << cpuCardsCalled[i] << " ";
            }
            cout << "\n\n";
        }
        cout << " Your Cards \n" << "   " << userDeck[0] << " " << userDeck[1] << "(" << getSum("user") << ")\n";
        if (Called) {
            cout << "Cards Called: ";
            for (int i = 0; i < userCards; i++) {
                cout << userCardsCalled[i] << " ";
            }
        }
    }
    if (!stayed) {
        cout << "\n\n1) Call | 2) Stay\n\n>> ";
        cin >> choice;
        do {
            if (choice == 1)
                if (!usercall()) {
                    callLose();
                }
            if (choice == 2)
                stay();
        } while (choice < 0 || choice > 2);
    }
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