#include <stdio.h> 
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: %s <mp3-file>\n", argv[0]);
    return 1;
  }

  const char* filename = argv[1];

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2040) < 0) {
    printf("Mix_openAudio Error: %s\n", Mix_GetError());
    SDL_Quit();
    return 1;
  }

  Mix_Music* music = Mix_LoadMUS(filename);
  if (!music) {
    printf("Could not load %s\n", filename, Mix_GetError());
    Mix_CloseAudio();
    SDL_Quit();
    return 1;
  }

  printf("=== Simple MP3 Player ===\n");
  printf("Playing: %s\n", filename);
  printf("Controls:\n");
  printf(" p = pause\n");
  printf(" r = resume\n");
  printf(" s = stop\n");
  printf(" q = quit\n");
  Mix_PlayMusic(music, 1);

  char cmd;
  while (1) {
    cmd = getchar();
    
    if (cmd == 'p') {
      Mix_PauseMusic();
      printf("Paused.\n");
    } else if (cmd == 'r') {
      Mix_ResumeMusic();
      printf("Resumed.\n");
    } else if (cmd == 's') {
      Mix_HaltMusic();
      printf("Stopped.\n");
    } else if (cmd == 'P') {
      Mix_PlayMusic(music, 1);
      printf("Play.\n");
    } else if (cmd == 'q') {
      printf("Quit.\n");
      break;
    }
  }

  Mix_HaltMusic();
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();

  return 0;
}
