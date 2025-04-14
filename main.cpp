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
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
