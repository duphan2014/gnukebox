#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct Song{
    char songName[256];  // Fixed-size array for song name otherwise can't strcpy -> segmentation fault because uninitialised memory
    Mix_Music *music;
} Song;

typedef struct Player{
    Song songs[50];
    Song* currentSong;
    int numberOfSongs;
    Song* nextSong;
    Song* previousSong;
    char currentDir[512];
} Player;

typedef struct {

} UI;

typedef struct FileManager{

} FileManager;

int Player_init(Player *self);
void Player_listSongs(Player *self);
int Player_play(Player *self, int i);
void Player_pause(Player *self);
void Player_resume(Player *self);
void Player_stop(Player *self);
void Player_next(Player *self);
void Player_previous(Player *self);

void Song_init(Song *self);
void Song_getStatus(Song *self);

void display_menu();