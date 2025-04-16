#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

// ====================== User CLASS =========================
class User {
public:
    string name;
    int score;

    User(string n) {
        name = n;
        score = 0;
    }

    void showScore() {
        cout << name << "'s score: " << score << endl;
    }
};

// ====================== FlashCard CLASS =========================
class FlashCard {
public:
    string question;
    string answer;
    int difficulty;
    int correctAns; //track how many times user answered particular flashcards correct

    FlashCard(string q, string a) {
        question = q;
        answer = a;
        difficulty = 3;
        correctAns = 0;
    }

    void show() {
        cout << "Q: " << question << endl;
    }

    bool checkAnswer(string userAns) {
        return userAns == answer;
    }

    void updateDiff(bool correct) {
        if (correct && difficulty > 1){
            difficulty--;
            correctAns++;//when user answer correct, difficulty decreases
        }else if (!correct && difficulty < 5) {
            difficulty++;
        }    
    }
};

// ====================== FlashCardsDeck CLASS =========================
class FlashCardsDeck {
private:
    vector<FlashCard> cards;

public:
    void addCard(string q, string a) {
        cards.push_back(FlashCard(q, a));
    }

    vector<FlashCard>& getCards() {
        return cards;
    }

    void review(User& user) {
        sort(cards.begin(), cards.end(), [](FlashCard& a, FlashCard& b) {
            return a.difficulty > b.difficulty;
        });

        for (auto& card : cards) {
            card.show();
            cout << "Your Answer: ";
            string ans;
            getline(cin, ans);

            bool correct = card.checkAnswer(ans);
            card.updateDiff(correct);

            if (correct) {
                cout << " Correct!\n";
                user.score++;
            } else {
                cout << " Wrong! Correct answer: " << card.answer << "\n";
            }

            cout << "-------------------------\n";
        }
    }
    
    void saveCardsToFile(string filename){
        ofstream file(filename);
        if(file.is_open()){
            for(const auto&card : cards){
                file<< card.question << "|" << card.answer << "|" << card.difficulty << "|" << card.correctAns << endl;
            }} else {
            cout << "Unable to open file for saving." << endl;
        }
    }

    void loadCardsFromFile(string filename) {
        ifstream file(filename);
        string line;
        
        //I'll compelete this one later 
    cards.push_back(FlashCard(question, answer));
            cards.back().difficulty = difficulty;
            cards.back().correctAns = correctAns;
        }
        cout << "Flashcards loaded from " << filename << endl;
    }
 };


// ====================== MAIN =========================
int main() {
    FlashCardsDeck deck;
    string name;
    cout << "| Welcome to the MMU digital flashcard interface |\n\n";
    cout << "Enter your name: ";
    getline(cin, name);
    User user(name);

    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Flashcard\n";
        cout << "2. Review Flashcards\n";
        cout << "3. Show Score\n";
        cout << "4. Exit\n\n";
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string q, a;
            cout << "Enter question: ";
            getline(cin, q);
            cout << "Enter answer: ";
            getline(cin, a);
            deck.addCard(q, a);
            cout << "Flashcard added.\n";
        } else if (choice == 2) {
            if (deck.getCards().empty()) {
                cout << "No flashcards to review.\n";
            } else {
                deck.review(user);
            }
        } else if (choice == 3) {
            user.showScore();
        } else if (choice == 4) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
