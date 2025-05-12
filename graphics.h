#pragma once
#include "functions.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;

enum GameState {
    INTRO,
    CHOOSE_CATEGORY,
    SHOW_CATEGORY,

};
extern const char* w_title;
extern const int w_width , w_height;
extern GameState state;

void StartVideo(SDL_Renderer *renderer, SDL_Window* window);
void drawText(SDL_Renderer* renderer, const string &word, TTF_Font* font,
            const SDL_Color color, SDL_Rect dstRect, const bool can_giua=1);
void warningText(SDL_Renderer* renderer, SDL_Rect rect,
                 const int& bad_guess, TTF_Font* font, SDL_Color color);
void drawRectangle(SDL_Renderer* renderer, SDL_Rect rect);
SDL_Texture* loadTexture(const char* path, SDL_Renderer *renderer);
void updateScore(SDL_Renderer* renderer, SDL_Rect s_Rect, TTF_Font* score, SDL_Color white);
