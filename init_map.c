#include "gamelib.h"

int read_map()
{

    FILE *f = fopen(MAP_PATH, "r");
    if (!f)
    {
        printf("The file '%s' is not found\n", MAP_PATH);
        return 0;
    }

    char map_info[6];
    char c;
    int i = 0;
    while ((c = fgetc(f)) != ',')
    {
        if (i > 5)
        {
            printf("The fist line on file '%s' is not correct\n", MAP_PATH);
            return 0;
        }
        map_info[i++] = c;
    }

    map_info[i] = '\0';

    while ((c = fgetc(f)) != 'x')
    {
        VERTICAL_BOXES_NUMBER *= 10;
        VERTICAL_BOXES_NUMBER += c - '0';
    }
    while ((c = fgetc(f)) != '\n')
    {
        HORIZONTAL_BOXES_NUMBER *= 10;
        HORIZONTAL_BOXES_NUMBER += c - '0';
    }

    if (VERTICAL_BOXES_NUMBER > HORIZONTAL_BOXES_NUMBER)
        BLOCK_SIZE = SCREEN_HEIGHT / VERTICAL_BOXES_NUMBER;
    else
        BLOCK_SIZE = SCREEN_HEIGHT / HORIZONTAL_BOXES_NUMBER;

    char space_c = map_info[0];
    char wall_c = map_info[1];
    char dest_c = map_info[2];
    char box_c = map_info[3];
    char player_c = map_info[4];
    // c = fgetc(f);
    for (int col = 0; col < VERTICAL_BOXES_NUMBER; col++)
    {
        for (int r = 0; r < HORIZONTAL_BOXES_NUMBER; r++)
        {
            c = fgetc(f);

            if (c == space_c)
                continue;

            else if (c == wall_c)
                insert_barrier(r, col);

            else if (c == box_c)
                insert_box(r, col);

            else if (c == dest_c)
                insert_destination(r, col);

            else if (c == player_c)
            {
                player.value.h = BLOCK_SIZE;
                player.value.w = BLOCK_SIZE;
                player.value.y = col * BLOCK_SIZE;
                player.value.x = r * BLOCK_SIZE;
                player.flip = SDL_FLIP_NONE;
                player.texture = PLAYER_DOWN_TEXTURE;

                // printf("pass insert 4\n");
            }
            else
                r--;
        }
    }
    fclose(f);
    return 1;
}

void insert_barrier(int x, int y)
{
    // malloc new barrier object on memory and give him the correct coordinates
    Barrier *new_barrier = malloc(sizeof(Barrier));
    if (!new_barrier)
        return;
    // WEIGHT / 8 window size / numbers of squares we have in this case 800 / 8 = 100
    new_barrier->value.h = BLOCK_SIZE;
    new_barrier->value.w = BLOCK_SIZE;

    new_barrier->value.y = y * BLOCK_SIZE;
    new_barrier->value.x = x * BLOCK_SIZE;

    if (BARRIERS_HEAD == NULL)
    {

        BARRIERS_HEAD = new_barrier;
        new_barrier->next = NULL;
        return;
    }
    else
    {
        new_barrier->next = BARRIERS_HEAD;
        BARRIERS_HEAD = new_barrier;
    }
}

void insert_destination(int x, int y)
{
    Destination *new_destination = malloc(sizeof(Destination));
    if (!new_destination)
        return;
    new_destination->value.h = BLOCK_SIZE;
    new_destination->value.w = BLOCK_SIZE;
    DESTINATIONS_NUMBER += 1;
    // printf("col=%d\trow=%d\n", x, y);

    new_destination->value.x = x * BLOCK_SIZE;
    new_destination->value.y = y * BLOCK_SIZE;
    if (DESTINATIONS_HEAD == NULL)
    {

        DESTINATIONS_HEAD = new_destination;
        new_destination->next = NULL;
        return;
    }
    else
    {
        new_destination->next = DESTINATIONS_HEAD;
        DESTINATIONS_HEAD = new_destination;
    }
}

void insert_box(int x, int y)
{
    Box *new_box = malloc(sizeof(Box));
    if (!new_box)
        return;
    new_box->value.h = BLOCK_SIZE;
    new_box->value.w = BLOCK_SIZE;

    new_box->value.x = x * BLOCK_SIZE;
    new_box->value.y = y * BLOCK_SIZE;
    new_box->texture = BOX_TEXTURE;
    new_box->is_on_place = 0;

    // printf(" new_box->value.x %d\tnew_box->value.y%d\n", new_box->value.x, new_box->value.y);

    if (BOXS_HEAD == NULL)
    {
        BOXS_HEAD = new_box;
        new_box->next = NULL;
    }
    else
    {
        new_box->next = BOXS_HEAD;
        BOXS_HEAD = new_box;
    }
}
