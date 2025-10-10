
#ifndef RATA_H
#define RATA_H

#define SDL_MAIN_HANDLED
#define TITLE "Sokoban"
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>

// structs
typedef struct Barrier Barrier;
typedef struct Destination Destination;
typedef struct Box Box;
typedef struct Bg Bg;
typedef struct PLAYER PLAYER;
typedef struct MenuItem MenuItem;

struct Barrier
{
    SDL_Rect value;
    Barrier *next;
};

struct Destination
{
    SDL_Rect value;
    Destination *next;
};

struct Box
{
    SDL_Rect value;
    Box *next;
    SDL_Texture *texture;
    int is_on_place;
};

struct Bg
{
    SDL_Rect value;
    Bg *next;
};
struct PLAYER
{
    SDL_Rect value;
    SDL_RendererFlip flip;
    SDL_Texture *texture;
};

struct MenuItem
{
    SDL_Rect rect;
    int hovered;
};

// // globaal variable
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
// extern int PLAY_SCREEN;
extern int IS_SOLVED;
extern int VERTICAL_BOXES_NUMBER;
extern int HORIZONTAL_BOXES_NUMBER;
extern int DESTINATIONS_NUMBER;
extern int SOLVED_BOXES;
extern int CURRENT_LEVEL;
extern char MAP_PATH[];
extern int BLOCK_SIZE;
extern int BG_SIZE;
extern int RUNNING;

extern Mix_Chunk *MOVE_SOUND;
extern Mix_Chunk *NON_MOVE_SOUND;
extern Mix_Chunk *MOVE_BOX_SOUND;
extern Mix_Chunk *BOX_ON_PLACE_SOUND;
extern Mix_Chunk *BOX_NON_PLACE_SOUND;
extern Mix_Chunk *RESTART_SOUND;

extern SDL_Renderer *RENDERER;
extern SDL_Renderer *RENDERER;
extern SDL_Window *WINDOW;
// extern SDL_Texture *INFO_TEXTURE;
extern SDL_Texture *LOGO_TEXTURE;
extern SDL_Texture *BACKGROUND_TEXTURE;
extern SDL_Texture *PLAYER_TEXTURE;
extern SDL_Texture *PLAYER_UP_TEXTURE;
extern SDL_Texture *PLAYER_DOWN_TEXTURE;
extern SDL_Texture *BOX_TEXTURE;
extern SDL_Texture *DESTINATIONS_TEXTURE;
extern SDL_Texture *BARRIERS_TEXTURE;
extern Bg *BG_HEAD;
extern Barrier *BARRIERS_HEAD;
extern Box *BOXS_HEAD;
extern Destination *DESTINATIONS_HEAD;
extern PLAYER player;
// extern SDL_Rect MAIN_SCREEN;
// // functions
void destroy_sounds();
int init_sounds();
int read_map();
void insert_barrier(int x, int y);
void insert_destination(int x, int y);
void insert_box(int x, int y);
void render_map();
void move_player(SDL_Event event);
int move_box(int direction, Box *my_box);
int find_barrier(int x_pos, int y_pos);
int can_player_move(int direction);
int can_box_move(int direction, int distance, Box *current_box);
int find_box(int x_pos, int y_pos, Box **next_box);
void check_solved(Box *my_box);
int init_game();
int init_texture();
int init_background();

#endif
