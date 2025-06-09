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
    string password;
    int score;

    User(string n, string p) {
        name = n;
        password = p;
        score = 0;
    }

    bool checkPassword(const string& p) const {
        return p == password;
    }

    void showScore() const {
        cout << name << "'s score: " << score << endl;
    }
};

class UserList {
    private:
        vector<User> users;
    
    public:
        bool userExists(const string& name) {
            for (const auto& user : users) {
                if (user.name == name) {
                    return true;
                }
            }
            return false;
        }
        
        User* authenticateUser(const string& name, const string& password) {
            for (auto& user : users) {
                if (user.name == name && user.checkPassword(password)) {
                    return &user;
                }
            }
            return nullptr;
        }
        User& createUser(const string& name, const string& password) {
            users.push_back(User(name, password));
            return users.back();
        }
        
        void showUsers(){
            cout << "\nList of users:"<<endl;
            for (size_t i=0;i<users.size();i++){
                cout << i+1 << ") " << users[i].name << "| SCORE: " << users[i].score << endl;
            }
        }
};

// ====================== FlashCard CLASS =========================
class FlashCard {
public:
    string question;
    string answer;
    int difficulty;
    int correctAns;

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
            correctAns++;
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
        cout << "Card added successfully! Total cards: " << cards.size() << endl;
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

    // FIXED: Better error handling and debugging
    void saveCardsToFile(string filename){
        cout << "Attempting to save " << cards.size() << " cards to file: " << filename << endl;
        
        if (cards.empty()) {
            cout << "Warning: No cards to save!" << endl;
            return;
        }
        
        ofstream file(filename);
        if(file.is_open()){
            int savedCount = 0;
            for(const FlashCard& card : cards){
                file << card.question << "|" << card.answer << endl;
                savedCount++;
            }
            file.close();
            cout << "Successfully saved " << savedCount << " flashcards to [" << filename << "]" << endl;
        } else {
            cerr << "Error: Unable to open file " << filename << " for saving." << endl;
            cerr << "Make sure you have write permissions in the current directory." << endl;
        }
    }

    // Better error handling
    void loadQuestionsFromFile(string filename) {
        ifstream file(filename);
        string line;

        if (file.is_open()) {
            cards.clear();
            int count = 0;
            
            while (getline(file, line)) {
                // Remove leading and trailing whitespace
                line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
                line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

                if (line.empty()) continue;

                size_t sep = line.find('|');
                if (sep != string::npos) {
                    string question = line.substr(0, sep);
                    string answer = line.substr(sep + 1);

                    // Clean extra spaces
                    question.erase(question.find_last_not_of(" \t") + 1);
                    answer.erase(0, answer.find_first_not_of(" \t"));

                    cards.push_back(FlashCard(question, answer));
                    count++;
                } else {
                    cerr << "Warning: Skipping invalid line: " << line << endl;
                }
            }
            file.close();
            
            if (count > 0) {
                cout << "Loaded " << count << " flashcards from [" << filename << "] successfully.\n" << endl;
            } else {
                cout << "No valid flashcards found in [" << filename << "].\n" << endl;
            }
        } else {
            cout << "Info: Could not open '" << filename << "'. Starting with an empty deck." << endl;
        }
    }
    
    // Function to display all cards for debugging
    void showAllCards() {
        if (cards.empty()) {
            cout << "No cards in deck." << endl;
            return;
        }
        
        cout << "Current flashcards in deck (" << cards.size() << " total):" << endl;
        for (size_t i = 0; i < cards.size(); i++) {
            cout << i + 1 << ". Q: " << cards[i].question << " | A: " << cards[i].answer << endl;
        }
    }
};

// ====================== AUTHENTICATION FUNCTIONS =========================
User* loginUser(UserList& user_list) {
    string name, password;
    
    cout << "Enter your name: ";
    getline(cin, name);
    
    if (user_list.userExists(name)) {
        cout << "What is your password? ";
        getline(cin, password);
        
        User* user = user_list.authenticateUser(name, password);
        if (user != nullptr) {
            cout << "Logged in successfully!" << endl;
            return user;
        } else {
            cout << "Incorrect password!" << endl;
            return nullptr;
        }
    } else {
        cout << "New user detected. Set your password: ";
        getline(cin, password);
        cout << "Account created successfully!" << endl;
        return &user_list.createUser(name, password);
    }
}

// ====================== MAIN =========================
int main() {
    FlashCardsDeck deck;
    UserList user_list; 

    deck.loadQuestionsFromFile("sourcetext.txt");

    cout << "| Welcome to the MMU digital flashcard interface |\n\n";
    User* currentUser = nullptr;
    
    while (currentUser == nullptr) {
        currentUser = loginUser(user_list);
        if (currentUser == nullptr) {
            cout << "Login failed. Please try again.\n\n";
        }
    }

    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Flashcard\n";
        cout << "2. Review Flashcards\n";
        cout << "3. Show Score\n";
        cout << "4. Save flashcards to file\n";
        cout << "5. Access other users\n";
        cout << "6. Show all cards\n";  // NEW: Debug option
        cout << "7. Exit\n\n";
        
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                string q, a;
                cout << "Enter question: ";
                getline(cin, q);
                cout << "Enter answer: ";
                getline(cin, a);
                deck.addCard(q, a);
                break;
            }

            case 2: {
                if (deck.getCards().empty()) {
                    cout << "No flashcards to review.\n";
                } else {
                    deck.review(*currentUser);
                }
                break;
            }

            case 3: {
                currentUser->showScore();
                break;
            }

            case 4: {
                deck.saveCardsToFile("sourcetext.txt");
                break;
            }

            case 5: {
                user_list.showUsers();
                char add;
                while (true) {
                    cout << "\nPress '+' to add new user (or any other key to return): ";
                    cin >> add;
                    cin.ignore();
                    if (add == '+') {
                        string username, userpassword;
                        cout << "Enter the username: ";
                        getline(cin, username);
                        cout << "Set password for " << username << ": ";
                        getline(cin, userpassword);
                        User& temp = user_list.createUser(username, userpassword);
                        currentUser = &temp;
                        cout << "User created successfully!" << endl;
                        user_list.showUsers();
                    } else {
                        cout << "Returning to main menu..." << endl;
                        break;
                    }
                }
                break;
            }

            case 6: {  // NEW: Debug option
                deck.showAllCards();
                break;
            }

            case 7: {
                cout << "Goodbye!\n";
                return 0;
            }

            default:
                cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}