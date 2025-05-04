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

class UserList {
    private:
        vector<User> users;
    
    public:
        // Returns a reference to a User object (existing or new)
        User& getUser(const string& name) {
            for (auto& user : users) {
                if (user.name == name) {
                    return user; // Return existing user
                }
            }
    
            // If not found, add new user
            users.push_back(User(name));
            return users.back(); // Return reference to the newly added user
        }
        void showUsers(){
            cout << "\nList of users:"<<endl;

            for (size_t i=0;i<users.size();i++){
               
                cout << i+1 << ") " << users[i].name << "| SCORE: " << users[i].score << endl;
            }
        
    };
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

    //please implement this under feature 4 
//added  more lines 
    void saveCardsToFile(string filename){
        ofstream file(filename);
        if(file.is_open()){
            for(const FlashCard& card : cards){
                file << card.question << "|" << card.answer << endl;  // Use 'file' instead of 'outFile'
            }
            file.close();
            cout << "Flashcards successfully saved to [" << filename << "]" << endl;
        } else {
            cerr << "Error: Unable to open file " << filename << " for saving." << endl;
        }
    }

// Load flashcards from a file
//improved this part a bit
     void loadQuestionsFromFile(string filename) {
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            cards.clear();  // Clear existing cards before loading new ones

            int count = 0;
            while (getline(file, line)) {
                line.erase(0, line.find_first_not_of("\t\n\r\f\v"));
                line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

                if (line.empty()) continue;  // Skip empty lines

                size_t sep = line.find('|');  // Find separator between question and answer

                if (sep != string::npos) {
                    string question = line.substr(0, sep);
                    string answer = line.substr(sep + 1);

                    // Clean extra spaces around q&a
                    question.erase(question.find_last_not_of(" \t") + 1);
                    answer.erase(0, answer.find_first_not_of("\t"));

                    cards.push_back(FlashCard(question, answer));
                    count++;
                } else {
                    cerr << "Warning: Skipping invalid line in " << filename << ": " << line << endl;
                }
            }
            file.close();
            if (count > 0) {
                cout << "Flashcards loaded from [" << filename << "] successfully...\n" << endl;
            } else {
                cout << "No valid flashcards found in [" << filename << "].\n" << endl;
            }
        } else {
            cout << "Info: Could not open '" << filename << "'. Starting with an empty deck. You can add cards manually or save later." << endl;
        }
    }
};

// ====================== MAIN =========================
int main() {
    FlashCardsDeck deck;
    UserList user_list; 
    string name;

    deck.loadQuestionsFromFile("sourcetext.txt");


    cout << "| Welcome to the MMU digital flashcard interface |\n\n";

    cout << "Enter your name: ";
    getline(cin, name);

    User& user = user_list.getUser(name);

    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Flashcard\n";
        cout << "2. Review Flashcards\n";
        cout << "3. Show Score\n";
        cout << "4. Edit source (Q&A) files\n";
        cout << "5. Access other users\n";
        cout << "6. Exit\n\n";
        
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

//changed the if,else-if statements into a switch,case statement
        switch(choice) {

        case 1:
            {string q, a;
            cout << "Enter question: ";
            getline(cin, q);
            cout << "Enter answer: ";
            getline(cin, a);
            deck.addCard(q, a);
            cout << "Flashcard added.\n";
            }break;

        case 2:
            {if (deck.getCards().empty()) {
                cout << "No flashcards to review.\n";
            } else {
                deck.review(user);
            }
            }break;

        case 3:
            {user.showScore();
            }break;

        case 4:
            {deck.saveCardsToFile("sourcetext.txt");
            }break;

        case 5:
            {user_list.showUsers();
                char add;

                while (true) {
                    cout << "\nPress '+' to add new user: ";
                    cin >> add;
            
                    if (add == '+') {
                        string username;
                        cout << "Enter the username: ";
                        getline(cin, username);
                       user_list.getUser(username);
                       user_list.showUsers();
                    } else {
                        break;
                    }
                }
            
                

            }break;   

        case 6:
            {cout << "Goodbye!\n";
             return 0;
            };

        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
