#include "gamelib.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    // Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);

    WINDOW = SDL_CreateWindow(
        "Sokoban",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);
    MAP_PATH[17] = CURRENT_LEVEL + '0';
    if (!init_game())
        return 1;

    // if (!init_sounds())
    //     return 1;

    SDL_Event event;

    while (RUNNING)
    {
        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT)
                RUNNING = 0;
            if (event.type == SDL_KEYDOWN)
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    RUNNING = 0;
                    break;
                case SDLK_r:
                    init_game();
                    break;
                case SDLK_n:
                    CURRENT_LEVEL++;
                    MAP_PATH[17] = CURRENT_LEVEL + '0';
                    FILE *f = fopen(MAP_PATH, "r");
                    if (f)
                        init_game();
                    else
                        CURRENT_LEVEL--;
                    break;
                case SDLK_l:
                    if (CURRENT_LEVEL != 1)
                    {
                        CURRENT_LEVEL--;
                        MAP_PATH[17] = CURRENT_LEVEL + '0';
                        init_game();
                    }
                    break;
                default:
                    move_player(event);
                    break;
                }
        }
        if (IS_SOLVED)
        {

            CURRENT_LEVEL++;
            MAP_PATH[17] = CURRENT_LEVEL + '0';
            init_game();
        }

        render_map();
    };

    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
