#include "gamelib.h"

int init_sounds()
{

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    MOVE_SOUND = Mix_LoadWAV("./assets/sounds/move.wav");
    NON_MOVE_SOUND = Mix_LoadWAV("./assets/sounds/non_move.wav");
    MOVE_BOX_SOUND = Mix_LoadWAV("./assets/sounds/push_box.wav");
    BOX_ON_PLACE_SOUND = Mix_LoadWAV("./assets/sounds/box_in_place.wav");
    BOX_NON_PLACE_SOUND = Mix_LoadWAV("./assets/sounds/box_non_place.wav");
    RESTART_SOUND = Mix_LoadWAV("./assets/sounds/restart.wav");

    if (!MOVE_SOUND ||
        !NON_MOVE_SOUND ||
        !MOVE_BOX_SOUND ||
        !BOX_ON_PLACE_SOUND ||
        !BOX_NON_PLACE_SOUND ||
        !MOVE_BOX_SOUND ||
        !RESTART_SOUND)
    {
        printf("Error loading sound: %s\n", Mix_GetError());
        return 0;
    }
    return 1;
}

void destroy_sounds()
{

    Mix_FreeChunk(MOVE_SOUND);
    Mix_FreeChunk(NON_MOVE_SOUND);
    Mix_FreeChunk(MOVE_BOX_SOUND);
    Mix_FreeChunk(BOX_ON_PLACE_SOUND);
    Mix_FreeChunk(BOX_NON_PLACE_SOUND);
    Mix_FreeChunk(RESTART_SOUND);
    Mix_CloseAudio();
    Mix_Quit();
}