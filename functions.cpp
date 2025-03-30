#include "functions.h"
vector <string> word_list;
vector <char> correctChars;
vector <char> incorrectChars;
int index=-1;
string secret_word;
int max_bad_guess=7;

void wordList(const string& filename){
    ifstream file(filename);
    if (!file.is_open()){
        cout<<"Category does not exist\n";
        return;
    }
    string s;
    while (file>>s){
        word_list.push_back(s);
    }
    srand(time(0));
    if (!word_list.empty()) index=rand()%(int)word_list.size();
    string x(word_list[index].size(),'-');
    secret_word=x;
}

bool isCharInWord(char guess, const string word){
    for (int i=0;i<(int)word.size();i++){
        if (guess==word[i]) return true;
    }
    return false;
}
void updateIncorrectGuess(char guess, int &bad_guessed, vector <char> &incorrectChars){
    bad_guessed++;
    incorrectChars.push_back(guess);
}
void updateCorectGuess(string &secret_word, string word, char guess, vector <char> correctChars){
    for (int i=0;i<(int)word.size();i++){
        if (guess==word[i]) {
                secret_word[i]=guess;
        }
    }
    correctChars.push_back(guess);
}
string chooseCategory(string &filename){
    cout<<"Please choose the category you want to play.\n";
    cout<<"[Fruits/ Transports/ Animals/ Jobs]\n";
    cin>>filename;
    for (int i=0;i<(int) filename.size();i++) filename[i]=tolower(filename[i]);
    if (filename[0]=='f') filename="fruits";
    else if (filename[0]=='t') filename="transports";
    else if (filename[0]=='a') filename="animals";
    else if (filename[0]=='j') filename="jobs";
    return filename;
}
char guessAChar(char &guess){
    cout<<"Guess a character: ";
    cin>>guess;
    guess=tolower(guess);
    return guess;
}
