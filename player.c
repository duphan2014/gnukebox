#include "player.h"

int DEBUG = 0;

int Player_init(Player *self) {
    if (DEBUG) printf("Player_init 1\n");
    self->numberOfSongs = 0;  // Initialize to 0
    struct dirent *entry;
    
    // Get the home directory path
    char *home_dir = getenv("HOME");
    char music_path[512];
    
    if (home_dir) {
        snprintf(music_path, sizeof(music_path), "%s/Music", home_dir);
    } else {
        strcpy(music_path, "./");  // Fallback to current directory
    }

    strcpy(self->currentDir, music_path);
    
    DIR *dir = opendir(music_path);
    
    if (DEBUG) printf("Trying to open directory: %s\n", music_path);

    if (!dir) {
        printf("Failed to open directory: %s\n", music_path);
        perror("opendir");
        return 1;
    }

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;
        size_t len = strlen(name);

        if (len > 4 && strcmp(name + len - 4, ".mp3") == 0) {
            strcpy(self->songs[i].songName, name);
            self->numberOfSongs++;
            i++;
            if (DEBUG) printf("Player_init i=%i\n", i);
        }
    }
    closedir(dir);
    if (DEBUG) printf("Player_init 2\n");

    if (DEBUG) printf("self->numberOfSongs %i\n", self->numberOfSongs);


    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2040) < 0) {
        printf("Mix_openAudio Error: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }
}

void Player_listSongs(Player *self) {
    printf("Available Songs:\n");
    for(int i = 0; i < self->numberOfSongs; i++) {
        printf("%i. %s\n", i, self->songs[i].songName);
    }
}

int Player_play(Player *self, int i) {
    self->currentSong = &self->songs[i];
    char * filename = self->currentSong->songName;
    char song_path[512];
    snprintf(song_path, sizeof(song_path), "/home/pc/Music/%s", filename);
    Mix_Music* music = self->currentSong->music;
    music = Mix_LoadMUS(song_path);
    //printf("%s", song_path);
    if (!music) {
        printf("Could not load %s\n", filename, Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }
    printf("Currently Playing: %s\n", filename);
    Mix_PlayMusic(music, 1);
}

void Player_pause(Player *self) {
    Mix_PauseMusic();
    printf("Paused.\n");
}
void Player_resume(Player *self) {
    Mix_ResumeMusic();
    printf("Resumed.\n");
}
void Player_stop(Player *self) {
    Mix_HaltMusic();
    printf("Stopped.\n");
}
void Player_next(Player *self) {

}
void Player_previous(Player *self) {

}


int main() {
    Player player;

    int running = 1;

    Player_init(&player);

    printf("== gnukebox ==\n");
    printf("  L to list songs\n");
    printf("  P to play song\n");
    printf("  p to pause\n");
    printf("  s to stop\n");
    printf("  q to quit\n");

    char cmd;
    while (running) {
        printf("\n> ");
        cmd = getchar();

        if (cmd == 'q') {
            system("cls");
            break;
        } else if (cmd == 'L') {
            Player_listSongs(&player);
        } else if (cmd == 'P') {
            printf("Enter song index: ");
            int index;
            scanf("%d", &index);
            Player_play(&player, index);
        } else if (cmd == 'p') {
            Player_pause(&player);
        } else if (cmd == 'r') {
            Player_resume(&player);
        } else if (cmd == 's') {
            Player_stop(&player);
        }

    }

    Mix_HaltMusic();
    Mix_FreeMusic(player.currentSong->music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

