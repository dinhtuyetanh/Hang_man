#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
extern vector <string> word_list;
extern vector <char> correctChars;
extern vector <char> incorrectChars;
extern int index;
extern string secret_word;
extern int max_bad_guess;

void wordList(const string &filename);
bool isCharInWord(char guess, const string word);
void updateIncorrectGuess(char guess, int &bad_guessed, vector <char> &incorrectChars);
void updateCorectGuess(string &secret_word, string word, char guess, vector <char> correctChars);
string chooseCategory(string &filename);
char guessAChar(char &guess);

#endif
