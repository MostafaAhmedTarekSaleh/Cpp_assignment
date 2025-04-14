#include <iostream>
#include <vector>
using namespace std;


class FlashCard {
public:
    string question;
    string answer;
    int difficulty;

    FlashCard(string q, string a) {
        question = q;
        answer = a;
        difficulty = 1; 
    }

    
    void show() {
        cout << "Q: " << question << endl;
    }

    bool checkAnswer(string userAns) {
        return userAns == answer;
    }

    void updateDiff(bool correct) {
        if (correct && difficulty > 1)
            difficulty--;
        else if (!correct && difficulty < 5)
            difficulty++;
    }
};

// FlashCardDeck Class: Manage and store flash cards
class FlashCardsDeck {
private:
    vector<FlashCard> cards;

public:
    // Add new cards to the deck and store
    void addCard(string q, string a) {
        cards.push_back(FlashCard(q, a));
    }

    // Get the list of flash cards
    vector<FlashCard>& getCards() {
        return cards;
    }
};

// User Class: Tracks the user's name and score
class User {
public:
    string name;
    int score;

    User(string n) {
        name = n;
        score = 0;
    }

    // user's score
    void showScore() {
        cout << name << "'s score: " << score << endl;
    }
};

int main() {
  
    return 0;
}
