#include "rata.h"

int init_texture()
{
    srand(time(NULL));

    int randomNumber = rand() % 6;
    char bg_name[32] = "./assets/backgrounds/bg (1).png";
    bg_name[25] = randomNumber + '0';

    SDL_Surface *background_surface = IMG_Load(bg_name);
    SDL_Surface *player_surface = IMG_Load("./assets/textures/player.png");
    SDL_Surface *player_up_surface = IMG_Load("./assets/textures/player_up.png");
    SDL_Surface *player_down_surface = IMG_Load("./assets/textures/player_down.png");
    SDL_Surface *box_surface = IMG_Load("./assets/textures/box.png");
    SDL_Surface *barrier_surface = IMG_Load("./assets/textures/barrier.png");
    SDL_Surface *destination_surface = IMG_Load("./assets/textures/destination.png");
    SDL_Surface *logo_surface = IMG_Load("./assets/textures/logo.png");
    // SDL_Surface *info_surface = IMG_Load("./assets/textures/info.png");

    if (!background_surface || !player_surface || !box_surface || !barrier_surface || !destination_surface || !player_up_surface || !player_down_surface || !logo_surface)
    {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        return 0;
    }

    DESTINATIONS_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, destination_surface);
    BACKGROUND_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, background_surface);
    BARRIERS_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, barrier_surface);
    PLAYER_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, player_surface);
    PLAYER_UP_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, player_up_surface);
    PLAYER_DOWN_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, player_down_surface);
    BOX_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, box_surface);
    LOGO_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, logo_surface);
    // INFO_TEXTURE = SDL_CreateTextureFromSurface(RENDERER, info_surface);

    SDL_FreeSurface(destination_surface);
    SDL_FreeSurface(background_surface);
    SDL_FreeSurface(barrier_surface);
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(player_up_surface);
    SDL_FreeSurface(player_down_surface);
    SDL_FreeSurface(box_surface);
    SDL_FreeSurface(logo_surface);
    // SDL_FreeSurface(info_surface);
    return 1;
}