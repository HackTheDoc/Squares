#include <iostream>
#include <cstdlib>
#include <SDL2/SDL.h>

#define SZ 256
#define a 1
#define A 100

bool init();
bool loop();
void kill();

SDL_Window* w = NULL;
int x = 0;
int y = 0;
SDL_DisplayMode m;
SDL_Surface* s = NULL;
int r = 0;
int g = 0;
int b = 0;

int K;

int main(int argc, char const *argv[]) {
    srand(time(0));

    if (init()) {
        while (loop()) {}
        kill();
    } else {
        system("pause");
        return 1;
    }
    return 0;
}

bool init() {
    bool o = true;
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL : %s", SDL_GetError());
        o = false;
    }

    if (o) {
        // Init window
        w = SDL_CreateWindow(
            "",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SZ, SZ,
            SDL_WINDOW_SHOWN
        );
        SDL_GetCurrentDisplayMode(0, &m);

        s = SDL_GetWindowSurface(w);
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;

        K = rand() % A + a;
    }
    return o;
}

bool loop() {
    bool l = true;

    SDL_FillRect( s, NULL, SDL_MapRGB( s->format, r, g, b ) );

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                l = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_q) {
                    l = false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                int p, q;
                SDL_GetMouseState(&p, &q);
                if (p >= 0 && p < SZ && q >= 0 && q < SZ) {
                    r = rand() % 256;
                    g = rand() % 256;
                    b = rand() % 256;

                    x = rand() % (m.w-SZ);
                    y = rand() % (m.h-SZ);
                    SDL_SetWindowPosition(w, x, y);

                    K--;
                }
                break;
            default:
                break;
        }
    }
    if (K == 0) {
        l = false;
    }

    SDL_UpdateWindowSurface(w);

    return l;
}

void kill() {
    SDL_DestroyWindow(w);
    w = NULL;
    SDL_Quit();
}
