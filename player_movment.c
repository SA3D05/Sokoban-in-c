#include "rata.h"

void move_player(SDL_Event event)
{
    // if the PLAYER collision
    // play sound here later

    if (event.key.keysym.sym == SDLK_UP)
    {
        if (can_player_move(UP))
        {
            player.value.y -= BLOCK_SIZE;
        }
        player.flip = SDL_FLIP_NONE;
        player.texture = PLAYER_UP_TEXTURE;
    }
    else if (event.key.keysym.sym == SDLK_DOWN)
    {
        if (can_player_move(DOWN))
        {
            player.value.y += BLOCK_SIZE;
        }
        player.flip = SDL_FLIP_NONE;
        player.texture = PLAYER_DOWN_TEXTURE;
    }
    else if (event.key.keysym.sym == SDLK_LEFT)
    {
        if (can_player_move(LEFT))
        {
            player.value.x -= BLOCK_SIZE;
        }
        player.flip = SDL_FLIP_NONE;
        player.texture = PLAYER_TEXTURE;
    }
    else if (event.key.keysym.sym == SDLK_RIGHT)
    {
        if (can_player_move(RIGHT))
        {
            player.value.x += BLOCK_SIZE;
        }
        player.texture = PLAYER_TEXTURE;
        player.flip = SDL_FLIP_HORIZONTAL;
    }
}

int can_player_move(int direction)
{
    // if there is a box in front of player this is the position of it x,y
    int next_xpos;
    int next_ypos;

    // if there is a box in front of the box  this is the position of it x2,y2
    int box_xpos;
    int box_ypos;

    // this is the pinter to the first box to move it later
    Box *next_box = NULL;

    if (direction == UP)
    {
        // printf("player x = %d | y = %d\n", PLAYER.x, PLAYER.y);

        next_xpos = player.value.x;
        next_ypos = player.value.y - BLOCK_SIZE;

        if (find_barrier(next_xpos, next_ypos))
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
            return 0;
        }

        // if player on top of screen y_pos = 0
        else if (next_ypos < 0)
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
            return 0;
        }

        if (find_box(next_xpos, next_ypos, &next_box))
        {

            // printf("box was found!\n");
            box_xpos = next_xpos;
            box_ypos = next_ypos - BLOCK_SIZE;

            // there is box on front of the player direction
            if (find_barrier(box_xpos, box_ypos))
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
                // printf("barrier front of the box you can't move\n\n");
                return 0;
            }
            else if (find_box(box_xpos, box_ypos, &next_box))
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                // printf(" box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
                // printf("there is 2 boxes in front of player!\nyou cant move\n\n");
                // printf("second box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
                return 0;
            }
            // same as   (PLAYER.y == 0) up there but for boxes
            else if (box_ypos < 0)
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
                return 0;
            }
            else
            {
                // printf("nothing front of box you can move!\n\n");

                move_box(UP, next_box);
                check_solved(next_box);

                // printf("solved: %d\n", SOLVED);
                return 1;
            }
        }
        else
        {
            Mix_PlayChannel(-1, MOVE_SOUND, 0);
            return 1;
        }
    }
    else if (direction == DOWN)
    {

        // printf("player x = %d | y = %d\n", PLAYER.x, PLAYER.y);

        next_xpos = player.value.x;
        next_ypos = player.value.y + BLOCK_SIZE;

        if (find_barrier(next_xpos, next_ypos))
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
            return 0;
        }
        // if player on bottom of screen y_pos = 800 - 100 / if screen height == 800 and boxs == 100

        else if (next_ypos >= SCREEN_HEIGHT)
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
            return 0;
        }

        if (find_box(next_xpos, next_ypos, &next_box))
        {
            // printf("box was found!\n");
            box_xpos = next_xpos;
            box_ypos = next_ypos + BLOCK_SIZE;

            // printf("first box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
            // there is box on front of the player direction
            if (find_barrier(box_xpos, box_ypos))
            {
                // printf(" box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                // printf("barrier front of the box you can't move\n\n");
                return 0;
            }
            else if (find_box(box_xpos, box_ypos, &next_box))
            {
                // printf("there is 2 boxes in front of player!\nyou cant move\n\n");
                // printf("second box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                return 0;
            }
            else if (box_ypos >= SCREEN_HEIGHT)
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
                return 0;
            }
            else
            {
                // printf("nothing front of box you can move!\n\n");

                move_box(DOWN, next_box);
                check_solved(next_box);
                // printf("solved: %d\n", SOLVED);
                return 1;
            }
        }
        else
        {
            Mix_PlayChannel(-1, MOVE_SOUND, 0);
            return 1;
        }
    }
    else if (direction == LEFT)
    {
        // printf("player x = %d | y = %d\n", PLAYER.x, PLAYER.y);

        next_xpos = player.value.x - BLOCK_SIZE;
        next_ypos = player.value.y;

        if (find_barrier(next_xpos, next_ypos))
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
            return 0;
        }
        // if player on bottom of screen x_pos = 0

        else if (next_xpos < 0)
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
            return 0;
        }
        if (find_box(next_xpos, next_ypos, &next_box))
        {
            // printf(" box x = %d | y = %d\n", next_box->value.x, next_box->value.x);

            // printf("box was found!\n");
            box_xpos = next_xpos - BLOCK_SIZE;
            box_ypos = next_ypos;

            // printf("first box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
            // there is box on front of the player direction
            if (find_barrier(box_xpos, box_ypos))
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                // printf("barrier front of the box you can't move\n\n");
                return 0;
            }
            else if (find_box(box_xpos, box_ypos, &next_box))
            {
                // printf("there is 2 boxes in front of player!\nyou cant move\n\n");
                // printf("second box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                return 0;
            }
            else if (box_xpos < 0)
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                return 0;
            }
            else
            {
                // printf("nothing front of box you can move!\n\n");

                move_box(LEFT, next_box);
                check_solved(next_box);
                // printf("solved: %d\n", SOLVED);

                return 1;
            }
        }
        else
        {
            Mix_PlayChannel(-1, MOVE_SOUND, 0);
            return 1;
        }
    }
    else if (direction == RIGHT)
    {
        // printf("player x = %d | y = %d\n", PLAYER.x, PLAYER.y);

        next_xpos = player.value.x + BLOCK_SIZE;
        next_ypos = player.value.y;

        if (find_barrier(next_xpos, next_ypos))
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

            return 0;
        }
        // if player on bottom of screen x_pos = 800 - 100 / if screen width == 800 and boxs == 100

        else if (next_xpos >= SCREEN_WIDTH)
        {
            Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

            return 0;
        }

        if (find_box(next_xpos, next_ypos, &next_box))
        {
            // printf(" box x = %d | y = %d\n", next_box->value.x, next_box->value.x);

            // printf("box was found!\n");
            box_xpos = next_xpos + BLOCK_SIZE;
            box_ypos = next_ypos;

            // printf("first box x = %d | y = %d\n", next_box->value.x, next_box->value.x);
            // there is box on front of the player direction
            if (find_barrier(box_xpos, box_ypos))
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);
                // printf("barrier front of the box you can't move\n\n");
                return 0;
            }
            else if (find_box(box_xpos, box_ypos, &next_box))
            {
                // printf("there is 2 boxes in front of player!\nyou cant move\n\n");
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                return 0;
            }
            else if (box_xpos >= SCREEN_WIDTH)
            {
                Mix_PlayChannel(-1, NON_MOVE_SOUND, 0);

                return 0;
            }
            else
            {
                // printf("nothing front of box you can move!\n\n");
                move_box(RIGHT, next_box);
                check_solved(next_box);
                // printf("solved: %d\n", SOLVED);
                return 1;
            }
        }
        else
        {
            Mix_PlayChannel(-1, MOVE_SOUND, 0);
            return 1;
        }
    }
    return 0;
}
