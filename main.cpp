#include "functions.h"
using namespace std;

int main(){
    string filename;
    char guess;
    int bad_guessed=0;
    char level='1';
    bool continuePlay=true;

    chooseCategory(filename);

    while (continuePlay){
            string filename1=filename+level+".txt";
            wordList(filename1);
            if((int)word_list.size()==0)  return 0;

            cout<<secret_word<<endl;
            while(bad_guessed<max_bad_guess&&word_list[index]!=secret_word){
                    guessAChar(guess);
                    if (isCharInWord(guess,word_list[index])) {
                            updateCorectGuess(secret_word, word_list[index], guess, correctChars);
                            cout<<secret_word<<endl;
                    }
                    else updateIncorrectGuess(guess, bad_guessed, incorrectChars);
                    cout<<"Incorrect guess: "<<bad_guessed<<endl;
            }
            if (word_list[index]==secret_word) {
                    cout<<"Congratulations! You win"<<endl;
                    cout<<"Next level? [Yes/ No] ";
                    string s; cin>>s;
                    if ((s[0]=='y'||s[0]=='Y')&&level<'3') {
                            continuePlay=true;
                            level++;
                            bad_guessed=0;
                    }
                    else continuePlay=false;
            }
            else {
                    cout<<"You lose. The correct word is "<<word_list[index]<<endl;
                    cout<<"Do you want to play again? [Yes/ No] ";
                    string s; cin>>s;
                    if (s[0]=='y'||s[0]=='Y') {
                            continuePlay=true;
                            bad_guessed=0;
                    }
                    else continuePlay=false;
            }
    }
}

