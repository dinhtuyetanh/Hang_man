#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector <string> word_list;
int index=-1;
string guess_word;
int max_bad_guess=7;

void wordList(const string &filename);
string update(string &guessed_word, string word, char guess, int &bad_guessed);

int main(){
    string filename;
    cout<<"Please choose the category you want to play.\n";
    cout<<"[Fruits/ Transports/ Animals/ Jobs]\n";
    cin>>filename;
    for (int i=0;i<(int) filename.size();i++) filename[i]=tolower(filename[i]);
    filename+=".txt";
    wordList(filename);
    if((int)word_list.size()==0)  return 0;
    char guess;

    
    int bad_guessed=0;
    cout<<guess_word<<endl;
    while(bad_guessed<max_bad_guess&&word_list[index]!=guess_word){
                cout<<"Guess a character: ";
                cin>>guess;
                guess=tolower(guess);
                cout<<update(guess_word, word_list[index], guess, bad_guessed)<<endl;
                cout<<"So lan doan sai: "<<bad_guessed<<endl;
    }
    if (word_list[index]==guess_word) cout<<"Congratulations! You win."<<endl;
    else {
        cout<<"You lose. The correct word is "<<word_list[index];
    }
}
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
    guess_word=x;
}
string update(string &guessed_word, string word, char guess, int &bad_guessed){
    bool check=false;
    for (int i=0;i<(int)word.size();i++){
        if (guess==word[i]) {
                guessed_word[i]=guess;
                check=true;
        }
    }
    if (check==false) bad_guessed++;
    return guessed_word;
}
