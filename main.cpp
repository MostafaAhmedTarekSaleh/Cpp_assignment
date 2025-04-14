#include <iostream>
using namespace std;
//class flash cards
class FlashCard{
public:
   string questions;
   string answer;
   int difficulty;

   FlashCard(string q, string a){
       questions = q;
       answer = a;
       difficulty = 1;
   }

   void FlashCard::show(){
    cout << "Q: "<< questions << endl;
   }

   bool FlashCard::checkAns(string userAns) {
    return userAns == answer;
   }


   void updateDiff(bool correct){
    if (correct && difficulty > 1)
       difficulty--;
    else if (! correct && difficulty < 5)
       difficulty++;   
   }
};

// FlashCardDeck Class: Manage and store flash cards
class FlashCardsDeck{
private:
    vector<FlashCard> cards;

public://add new cards to the deck
    void addCard(string q, string a){
        cards.push_back(FlashCard(q, a));
    }    
    
    vector<FlashCard> &getCards(){
        return cards;
    }//list of flash cards
//track user's score
class User{
public:
    string name;
    int score;
    
    User(string n){
        name = n;
        score = 0;
    }

    void ShowScore(){
        cout<< name << "' score: "<<score << endl;
    }
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
