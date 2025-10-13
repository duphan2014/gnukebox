#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {

} UI;

// Constructor
void UI_init(UI *self);

// Method
void UI_display(UI *self);