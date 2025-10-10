#include "rata.h"

void render_map()
{
    // SET BACKGROUND BLACK
    // SDL_SetRenderDrawColor(RENDERER, 120, 120, 120, 0);
    // SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 0);
    // SDL_RenderClear(RENDERER);
    SDL_RenderClear(RENDERER);
    // background render
    // SDL_RenderClear(RENDERER);
    Bg *bg_temp = BG_HEAD;
    while (bg_temp)
    {
        // SDL_RenderCopyEx(RENDERER, texture, NULL, &bg_temp->value, 0, NULL, FLIP_VALUE);
        bg_temp->value.y += 2;
        if (bg_temp->value.y > SCREEN_HEIGHT)
            bg_temp->value.y = -1 * BG_SIZE;
        SDL_RenderCopy(RENDERER, BACKGROUND_TEXTURE, NULL, &bg_temp->value);
        bg_temp = bg_temp->next;
        // SDL_Delay(5);
        // SDL_RenderPresent(RENDERER);
    }
    // SDL_RenderClear(RENDERER);

    // GO OVER ALL BARRIERS IN LINKED LIST AND RENDER THEM
    Barrier *barrier_temp = BARRIERS_HEAD;
    while (barrier_temp)
    {
        // THE COLOR

        SDL_RenderCopy(RENDERER, BARRIERS_TEXTURE, NULL, &barrier_temp->value);
        barrier_temp = barrier_temp->next;
    }

    // SAME AS BARRIERS BUT DESTINATIONS
    Destination *destination_temp = DESTINATIONS_HEAD;
    while (destination_temp)
    {
        SDL_RenderCopy(RENDERER, DESTINATIONS_TEXTURE, NULL, &destination_temp->value);
        destination_temp = destination_temp->next;
    }

    // YOU KNOW
    Box *box_temp = BOXS_HEAD;
    while (box_temp)
    {

        SDL_RenderCopy(RENDERER, box_temp->texture, NULL, &box_temp->value);
        box_temp = box_temp->next;
    }
    // THIS FOR RENDER THE PLAYER
    // SDL_SetRenderDrawColor(RENDERER, 40, 200, 80, 255);
    // SDL_RenderFillRect(RENDERER, &PLAYER);
    // SDL_RenderCopy(RENDERER, texture, NULL, &PLAYER);

    SDL_RenderCopyEx(RENDERER, player.texture, NULL, &player.value, 0, NULL, player.flip);
    // SDL_RenderCopy(RENDERER, INFO_TEXTURE, NULL, &MAIN_SCREEN);

    // SDL_RenderDrawLine(RENDERER, 0, 0, 640, 0);
    // SDL_RenderDrawLine(RENDERER, 0, 0, 0, 480);
    // SDL_RenderDrawLine(RENDERER, 0, PLAY_SCREEN, PLAY_SCREEN, PLAY_SCREEN);
    // ALL GOOD NOW DRAW ON SCREEN
    SDL_RenderPresent(RENDERER);

    // 16 MEANS 60 FPS TO LEET THE CPU BREATH
    SDL_Delay(16);
}

void check_solved(Box *my_box)
{

    Destination *temp = DESTINATIONS_HEAD;
    while (temp)
    {
        if (my_box->value.x == temp->value.x && my_box->value.y == temp->value.y)
        {
            if (my_box->is_on_place == 1)
                return;
            my_box->is_on_place = 1;
            SOLVED_BOXES += 1;
            // Mix_PlayChannel(-1, BOX_ON_PLACE_SOUND, 0);

            if (SOLVED_BOXES == DESTINATIONS_NUMBER)
            {
                printf("\n\nCongratulations you solved this level!\n\n");
                IS_SOLVED = 1;
            }
            return;
        }
        else if (my_box->is_on_place == 1)
        {
            SOLVED_BOXES -= 1;
            my_box->is_on_place = 0;
        }
        temp = temp->next;
    }
}

int find_barrier(int x_pos, int y_pos)
{
    Barrier *temp = BARRIERS_HEAD;
    while (temp)
    {
        if (temp->value.x == x_pos && temp->value.y == y_pos)
            // barrier found on pos x,y
            return 1;
        temp = temp->next;
    }
    // barrier not found on pos x,y

    return 0;
}

int find_box(int x_pos, int y_pos, Box **next_box)
{
    Box *temp = BOXS_HEAD;
    while (temp)
    {
        // that {temp != *next_box} ignore first box node if we need to check the second one
        if (temp->value.x == x_pos && temp->value.x == y_pos && temp != *next_box)
        {
            *next_box = temp;
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int move_box(int direction, Box *my_box)
{
    if (direction == UP)
    {
        my_box->value.y -= BLOCK_SIZE;
    }
    else if (direction == DOWN)
    {
        my_box->value.y += BLOCK_SIZE;
    }
    else if (direction == LEFT)
    {
        my_box->value.x -= BLOCK_SIZE;
    }
    else if (direction == RIGHT)
    {
        my_box->value.x += BLOCK_SIZE;
    }
    Mix_PlayChannel(-1, MOVE_BOX_SOUND, 0);
}

int init_game()
{
    IS_SOLVED = 0;
    VERTICAL_BOXES_NUMBER = 0;
    HORIZONTAL_BOXES_NUMBER = 0;
    DESTINATIONS_NUMBER = 0;
    SOLVED_BOXES = 0;

    Barrier *temp_barrier = BARRIERS_HEAD;
    Box *temp_box = BOXS_HEAD;
    Destination *temp_destination = DESTINATIONS_HEAD;
    Bg *temp_bg = BG_HEAD;

    while (temp_bg)
    {
        BG_HEAD = BG_HEAD->next;
        free(temp_bg);
        temp_bg = BG_HEAD;
    }

    while (temp_barrier)
    {
        BARRIERS_HEAD = BARRIERS_HEAD->next;
        free(temp_barrier);
        temp_barrier = BARRIERS_HEAD;
    }

    while (temp_box)
    {
        BOXS_HEAD = BOXS_HEAD->next;
        free(temp_box);
        temp_box = BOXS_HEAD;
    }

    while (temp_destination)
    {
        DESTINATIONS_HEAD = DESTINATIONS_HEAD->next;
        free(temp_destination);
        temp_destination = DESTINATIONS_HEAD;
    }

    Mix_PlayChannel(-1, RESTART_SOUND, 0);
    // MAIN_SCREEN.h = SCREEN_HEIGHT;
    // MAIN_SCREEN.w = SCREEN_WIDTH;
    // MAIN_SCREEN.x = 0;
    // MAIN_SCREEN.y = 0;
    if (!init_texture())
        return 0;
    if (!read_map())
        return 0;
    if (!init_background())
        return 0;
}