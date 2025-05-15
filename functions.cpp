
#include "functions.h"
#include "graphics.h"
string filename="";
vector <string> word_list;
char level='1';
int max_bad_guess=6;
vector <char> chars;
int hint=5, maxhint=5, hint1;

int x;//khong quan trong

float totalScore=0, Score;
void chooseCategory(SDL_Event event){
    switch (event.key.keysym.sym) {
        case SDLK_1: case SDLK_KP_1:
            filename = "jobs";
            break;
        case SDLK_2: case SDLK_KP_2:
            filename = "fruits";
            break;
        case SDLK_3: case SDLK_KP_3:
            filename = "animals";
            break;
        case SDLK_4: case SDLK_KP_4:
            filename = "transports";
            break;
    }
}

void createWordList(const string& filename){
    ifstream file(filename);
    word_list.clear();
    if (!file.is_open()){
        cout<<"Category does not exist\n";
        return;
    }
    string s;
    while (file>>s){
        word_list.push_back(s);
    }
}
void createSecretWord(string &s){
    srand(time(0));
    int index;
    if (!word_list.empty()) index=rand()%(int)word_list.size();
    s=word_list[index];
}
string createHiddenWord(const string &s){
    string x(s.size(),'-');
    return x;
}
void updateIncorrectGuess(char guess, int &bad_guessed){
    bad_guessed++;
    chars.push_back(guess);
}
void updateCorrectGuess(string &secret_word, string word, char guess){
    int x=0;
    for (int i=0;i<(int)word.size();i++){
        if (guess==word[i]) {
                secret_word[i]=guess;
                x++;
        }
    }
    totalScore+=(40.0/(int)secret_word.size())*x;
    chars.push_back(guess);
}
char guessAChar(SDL_Renderer* renderer, TTF_Font* font, TTF_Font* font1, SDL_Color color,
                 int& hint,const string &secret_word, string& hidden_word, bool &useHint ){
    char g='\0';
    chars.push_back(g);
    do{

        SDL_Event e;
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) exit(0);

            if (e.type==SDL_KEYDOWN){
                SDL_Keycode key = e.key.keysym.sym;

                if (key >= SDLK_a && key <= SDLK_z) {
                        g=static_cast<char>(key);
                }
            }
            if (e.type==SDL_MOUSEBUTTONDOWN){
                int x=e.button.x, y=e.button.y;
                if (x>490&&x<530&&y>220&&y<260){
                    int n=secret_word.size();
                    SDL_Rect h_Rect={490, 220, 40, 40};
                    if (hint>0){
                        for (int i=0;i<n;i++){
                                useHint=true;
                            if (secret_word[i]!=hidden_word[i]){
                                hidden_word[i]=secret_word[i];
                                hint--;
                                drawRectangle(renderer, h_Rect);
                                SDL_Rect h_Rect1; h_Rect1.x=500; h_Rect1.y=215;

                                SDL_SetRenderDrawColor(renderer, 74, 106, 80, 255);
                                drawRectangle(renderer,h_Rect);
                                drawText(renderer, to_string(hint), font1, color, h_Rect1,0);
                                g=secret_word[i] ;
                                return g;
                            }
                        }
                    }
                    else{
                        SDL_Rect _rect; _rect.y=270;
                        SDL_SetRenderDrawColor(renderer, 74, 106, 80, 255);
                        SDL_Rect rect;
                        rect= {355, 265,100,45};
                        drawRectangle(renderer, rect);
                        drawText(renderer, "Hint=0", font, color, _rect);
                        SDL_Delay (300);
                        _rect= {355, 265,150,45};
                        SDL_SetRenderDrawColor(renderer, 91, 130, 93, 255);
                        drawRectangle(renderer,_rect);
                        break;
                    }
                }
            }
        }
    }
    while (isCharInWord(g, chars,x));
    return g;

}

void updateWin(SDL_Renderer* renderer, int &bad_guess, bool &running, const int&Score, const int&hint1){
    SDL_Texture* texture=loadTexture("image/bingo.png", renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    ostringstream ss;
    ss <<fixed <<setprecision(1) << totalScore;
    string scoreText = ss.str();
    string score="Score: "+scoreText;
    TTF_Font* font = TTF_OpenFont("Schoolbell-Regular.ttf", 30);
    SDL_Color black={0,0,0};
    SDL_Rect r={340,230, 15,15};
    drawText (renderer, score.c_str(),font, black, r);
    SDL_RenderPresent(renderer);
    while (true){
        SDL_Event e;
        while (SDL_PollEvent (&e)){
            if (e.type==SDL_MOUSEBUTTONDOWN){
                int x=e.button.x;
                int y=e.button.y;
                SDL_Log(" Click  (%d, %d)",x,y);
                if (x>350&&x<450&&y>290&&y<320){
                    bad_guess=0;
                    level++;
                    cout<<"Next\n";
                    return;
                }
                if (x>350&&x<450&&y>340&&y<375){
                    bad_guess=0;
                    cout<<"Replay\n";
                    hint=hint1;
                    totalScore=Score;
                    return;
                }
                if (x>350&&x<450&&y>395&&y<430){
                     exit(0);
                }
            }
        }
    }
}
void updateLose(SDL_Renderer *renderer, int &bad_guess, bool &running){
    SDL_Texture* texture=loadTexture("image/Gameover.png", renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    ostringstream ss;
    ss <<fixed <<setprecision(1) << totalScore;
    string scoreText = ss.str();
    string score="Score: "+scoreText;
    TTF_Font* font = TTF_OpenFont("Schoolbell-Regular.ttf", 30);
    SDL_Color white={255,255,255};
    SDL_Rect r={390,275, 15,15};
    drawText (renderer, score.c_str(),font, white, r);
    SDL_RenderPresent(renderer);
    SDL_RenderPresent(renderer);
    while(true){
        SDL_Event e;
        while (SDL_PollEvent (&e)){
            if (e.type==SDL_MOUSEBUTTONDOWN){
                int x=e.button.x;
                int y=e.button.y;
                SDL_Log(" Click  (%d, %d)",x,y);
                if (x>260&&x<370&&y>330&&y<360){
                    bad_guess=0;
                    level='1';
                    totalScore=0;
                    hint=maxhint;
                    cout<<"Replay\n";
                    return;
                }
                if (x>420&&x<530&&y>330&&y<360){
                    exit(0);
                }
            }
        }
    }
}
