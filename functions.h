
#pragma once
#include "graphics.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;
extern string filename;
extern char level;
extern vector <string> word_list;
extern int max_bad_guess;
extern int hint, maxhint, hint1;
extern vector <char> chars;
extern float totalScore, Score;
extern int x;
void chooseCategory(SDL_Event event);

void createSecretWord(string &s);
void createWordList(const string& filename);
string createHiddenWord(const string &s);
void updateIncorrectGuess(char guess, int &bad_guessed);
void updateCorrectGuess(string &secret_word, string word, char guess);

template <class T>
bool isCharInWord(char guess, T word, int&dem){
    bool ch=0;
    dem=0;
    for (int i=0;i<(int)word.size();i++){
        if (guess==word[i]){
            dem++;
            ch=1;
        }
    }
    return ch;
}
char guessAChar(SDL_Renderer* renderer,  TTF_Font* font, TTF_Font* font1, SDL_Color color,
                int& hint,const string &secret_word, string& hidden_word, bool &useHint );
void updateWin(SDL_Renderer* renderer, int &bad_guess, bool &running, const int&Score, const int&hint1);
void updateLose(SDL_Renderer *renderer, int &bad_guess, bool &running);
