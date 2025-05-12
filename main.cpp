<<<<<<< HEAD
#include "functions.h"
#include "graphics.h"

using namespace std;



int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    vector<char> c_hint;

    //FONT
    TTF_Font* font = TTF_OpenFont("Schoolbell-Regular.ttf", 25);
    TTF_Font* font1= TTF_OpenFont("ComicNeue-Bold.ttf", 55);
    TTF_Font* score=TTF_OpenFont("Schoolbell-Regular.ttf", 38);

    SDL_Color white={255,255,255};
    SDL_Rect rectHiddenText = {160, 350, 500, 60}, rectMistakes = {215, 265,365,45};

    if (!font1) {
        SDL_Log("Font load error: %s", TTF_GetError());
    }

    SDL_Window *window=SDL_CreateWindow(w_title,
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                        w_width, w_height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect dstRect;
    //INTRO
    StartVideo(renderer, window);

    //Load Texture
    SDL_Texture *choose_bg=loadTexture("image/Choose.png", renderer);
    SDL_Texture* intro = loadTexture("image/Hangman_034.jpg", renderer);
    SDL_Texture *gia_treo=loadTexture("image/gia_treo.png", renderer);

    SDL_Texture *wrong[max_bad_guess];
    for (int i=0; i< max_bad_guess;i++){
        const char* path= ("image/wrong"+to_string(i+1)+".png").c_str();
        wrong[i]=loadTexture(path, renderer);
    }

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                exit(0);

            if (event.type == SDL_KEYDOWN) {
                if (state == INTRO) {
                    state = CHOOSE_CATEGORY;
                }
                chooseCategory (event);
            }
            if (!filename.empty()) {
                state = SHOW_CATEGORY;
            }
            SDL_FlushEvent(SDL_KEYDOWN);
        }

        SDL_RenderClear(renderer);

       if (state == INTRO) {
            SDL_RenderCopy(renderer, intro, nullptr, nullptr);
        }
         else if (state == CHOOSE_CATEGORY) {
            SDL_RenderCopy(renderer, choose_bg, nullptr, nullptr);
        }
        else if (state == SHOW_CATEGORY) {
            const char* path = ("image/"+filename + ".png").c_str();
            SDL_Texture* img = loadTexture(path, renderer);
            if (!img) cerr << "Can not load image: " << path << "\n";
            else {

                bool running=1;
                while (running){
                    SDL_RenderCopy(renderer, img, nullptr, nullptr);
                    SDL_RenderCopy(renderer, gia_treo, nullptr, nullptr);
                    SDL_RenderPresent(renderer);

                    string filename1="_txt/"+filename+level+".txt";
                    createWordList(filename1);

                    if((int)word_list.size()==0) {
                            cout<<"Can not load file\n";
                            return 0;
                    }

                    int bad_guess=0;
                    string secret_word, hidden_word;

                    createSecrectWord(secret_word);
                    hidden_word=createHiddenWord(secret_word);
                    SDL_Rect s_Rect={535,165,125,100};
                    SDL_Rect scoreRect; scoreRect.y=165; scoreRect.x=410;
                    drawText(renderer, "Score: ", score, white, scoreRect, 0);
                    SDL_Rect h_Rect={490, 220, 40, 40};
                    SDL_Rect hintRect; hintRect.x=410; hintRect.y=215;
                    drawText(renderer, "Hint: ", score, white, hintRect, 0);
                    SDL_SetRenderDrawColor(renderer, 74, 106, 80, 255);
                    drawRectangle(renderer, h_Rect);
                    SDL_Rect h_Rect1; h_Rect1.x=500; h_Rect1.y=215;
                    drawText(renderer, to_string(hint), score, white, h_Rect1,0);
                    Score=totalScore;
                    hint1=hint;
                    updateScore(renderer, s_Rect, score, white);

                    while(bad_guess<max_bad_guess&&secret_word!=hidden_word){

                        dstRect.y= 350;
                        drawText(renderer, hidden_word, font1, white, dstRect);
                        bool useHint=0;
                        char guess= guessAChar(renderer, font, score, white, hint, secret_word, hidden_word, useHint);
                        if (useHint){
                                int dem1=0, dem2=0;
                                isCharInWord(guess, secret_word, dem1);
                                if (isCharInWord(guess, c_hint, dem2)) dem1-=dem2;;
                                if (dem1>1&&totalScore>0) totalScore-=40.0/((int)secret_word.size());
                                c_hint.push_back(guess);
                                if (dem1<=1) chars.push_back(guess);
                                SDL_SetRenderDrawColor(renderer, 91, 130, 93, 255);
                                drawRectangle(renderer, rectHiddenText);
                                drawText(renderer, hidden_word, font1, white, dstRect);
                        }
                        if (isCharInWord(guess,secret_word, x)&&(!useHint)) {
                                updateCorrectGuess(hidden_word, secret_word, guess);
                                SDL_SetRenderDrawColor(renderer, 91, 130, 93, 255);
                                drawRectangle(renderer, rectHiddenText);
                                drawText(renderer, hidden_word, font1, white, dstRect);
                        }
                        if (!isCharInWord(guess, secret_word,x)) {
                                updateIncorrectGuess(guess, bad_guess);
                                warningText(renderer, rectMistakes, bad_guess, font, white);
                                SDL_RenderCopy(renderer, wrong[bad_guess-1], nullptr, nullptr);
                                SDL_RenderPresent(renderer);
                        }
                        //hiện điểm

                        updateScore(renderer, s_Rect, score, white);

                    }
                    chars.clear();
                    if (hidden_word ==secret_word) {
                            totalScore+=30.0*(1-1.0*bad_guess/(int)secret_word.size())+20.0*hint/maxhint+10;

                            updateScore(renderer, s_Rect, score,white);

                            updateWin(renderer, bad_guess, running, Score, hint1);
                            if (level>'3'){
                                level='1';
                                hint=maxhint;
                                state=INTRO;
                                break;
                            }
                    }
                    else {
                            SDL_SetRenderDrawColor(renderer, 91, 130, 93, 255);
                            SDL_Rect r; r.y=310;
                            drawText(renderer, "The secret word is: ", font, white, r);
                            drawRectangle(renderer, rectHiddenText);
                            drawText(renderer, secret_word, font1, white, dstRect);
                            SDL_Delay(1000);
                            updateLose(renderer, bad_guess, running);
                    }

                }

            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_DestroyTexture(choose_bg);
    SDL_DestroyTexture(intro);
    for (int i=0; i< max_bad_guess;i++){
        SDL_DestroyTexture(wrong[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow (window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
