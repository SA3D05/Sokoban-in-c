#include "gamelib.h"

int init_background()
{

    int column = -1;
    int row = 0;

    for (int i = 0; i < 4 * 12; i++)
    {

        Bg *new_bg = malloc(sizeof(Bg));
        new_bg->value.h = BG_SIZE;
        new_bg->value.w = BG_SIZE;
        new_bg->value.x = row * BG_SIZE;
        new_bg->value.y = column * BG_SIZE;
        row++;
        if (row == 4)
        {
            column += 1;
            row = 0;
        }

        if (BG_HEAD == NULL)
        {
            new_bg->next = NULL;
            BG_HEAD = new_bg;
        }
        else
        {
            Bg *temp = BG_HEAD;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = new_bg;
            new_bg->next = NULL;
        }
    }
    return 1;
}