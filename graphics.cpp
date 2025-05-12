#include "graphics.h"
#include "functions.h"

const char* w_title="Hang man";
const int w_width =800, w_height=600;

GameState state = INTRO;
void updateScore(SDL_Renderer* renderer, SDL_Rect s_Rect, TTF_Font* score,
                  SDL_Color white ){
    SDL_Delay(600);

    ostringstream ss;
    ss <<fixed <<setprecision(1) << totalScore;
    string scoreText = ss.str();
    SDL_SetRenderDrawColor(renderer, 91, 130, 93, 255);
    drawRectangle(renderer, s_Rect);
    drawText(renderer, scoreText.c_str(), score, white, s_Rect,0);
    SDL_Delay(600);
}

void StartVideo(SDL_Renderer *renderer, SDL_Window* window){
    const int NUM_FRAMES = 35;
    SDL_Texture* frames[NUM_FRAMES];

    for (int i = 0; i < NUM_FRAMES; ++i) {
        string file_name = "image/Hangman_";
        if (i<10) file_name+="00" + to_string(i) + ".jpg";
        else file_name+="0"+to_string(i)+".jpg";
        SDL_Surface* surface = IMG_Load(file_name.c_str());
        if (!surface) {
            std::cerr << "Failed to load " << file_name << ": " << IMG_GetError() << "\n";
            continue;
        }
        frames[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }


    Uint32 lastFrameTime = SDL_GetTicks();
    const Uint32 FRAME_DURATION = 33;

    int currentFrame = 0;
    bool videoEnded = 0;

    while (!videoEnded) {
        Uint32 now = SDL_GetTicks();
        if (now - lastFrameTime >= FRAME_DURATION) {
            currentFrame++;
            lastFrameTime = now;
            if (currentFrame >= NUM_FRAMES) {
                videoEnded = 1; // hoặc lặp lại, hoặc chuyển sang menu
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[currentFrame], nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, frames[--currentFrame], nullptr, nullptr);
    SDL_RenderPresent(renderer);
    for (int i=0;i<NUM_FRAMES;i++){
        SDL_DestroyTexture(frames[i]);
    }

}
void drawText(SDL_Renderer* renderer, const string &word, TTF_Font* font, const SDL_Color color, SDL_Rect dstRect, const bool can_giua){
    SDL_Surface* surface = TTF_RenderText_Solid(font, word.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    dstRect.w= surface->w;
    dstRect.h= surface->h;
    if (can_giua) dstRect.x=(w_width  - dstRect.w) / 2;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_RenderPresent(renderer);
}
void drawRectangle(SDL_Renderer* renderer, SDL_Rect rect){
    SDL_RenderFillRect(renderer, &rect);
    if (SDL_RenderFillRect(renderer, &rect) != 0) {
        std::cout << "Failed to draw rectangle! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_RenderPresent(renderer);
}
void warningText(SDL_Renderer* renderer, SDL_Rect rect, const int& bad_guess, TTF_Font* font, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, 74, 106, 80, 105);
    drawRectangle(renderer, rect);
    string warning="Try again! You've made " +to_string(bad_guess);
    if (bad_guess<=1) warning+=" mistake.";
    else warning+=" mistakes.";
    SDL_Rect _rect; _rect.y=270;
    drawText(renderer, warning, font, color, _rect );
    SDL_Delay(600);
    SDL_SetRenderDrawColor(renderer, 91, 130, 93, 255);
    drawRectangle(renderer, rect);
    SDL_RenderPresent(renderer);
}
SDL_Texture* loadTexture(const char* path, SDL_Renderer *renderer){

    SDL_Surface* loadedSurface=IMG_Load(path);

    if (!loadedSurface) {
        SDL_Log("IMG_Load failed: %s", IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Load texture %s", IMG_GetError());
      }
    return texture;
}
