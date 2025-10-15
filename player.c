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
    
    return 0;  // Success
}

void Player_listSongs(Player *self) {
    printf("Available Songs:\n");
    for(int i = 0; i < self->numberOfSongs; i++) {
        printf("%i. %s\n", i, self->songs[i].songName);
    }
}

int Player_play(Player *self, int i) {
    if (i == self->numberOfSongs) {
        i = 0;
    } else if (i == -1){
        i = self->numberOfSongs-1;
    }

    self->currentSongIndex = i;
    self->currentSong = &self->songs[i];

    char * filename = self->currentSong->songName;
    char song_path[512];
    snprintf(song_path, sizeof(song_path), "/home/pc/Music/%s", filename);
    Mix_Music* music = self->currentSong->music;
    music = Mix_LoadMUS(song_path);
    //printf("%s", song_path);
    if (!music) {
        printf("Could not load %s: %s\n", filename, Mix_GetError());
        //Mix_CloseAudio();
        //SDL_Quit();
        return 1;
    }
    printf("Playing: %d. %s\n", self->currentSongIndex, self->currentSong->songName);
    Mix_PlayMusic(music, 1);
    self->status = PLAYING;
    return 0;
}

void Player_pause(Player *self) {
    Mix_PauseMusic();
    self->status = PAUSED;
    printf("Paused: %s\n", self->currentSong->songName);
}
void Player_resume(Player *self) {
    Mix_ResumeMusic();
    self->status = PLAYING;
    printf("Resumed: %s\n", self->currentSong->songName);
}
void Player_stop(Player *self) {
    Mix_HaltMusic();
    self->status = STOPPED;
    printf("Stopped: %s\n", self->currentSong->songName);
}
void Player_next(Player *self) {
    Player_play(self, self->currentSongIndex + 1);
}

void Player_last(Player *self) {
    Player_play(self, self->currentSongIndex - 1);
}

void display_menu(){
    printf("== gnukebox ==\n");
    printf("  L to list songs\n");
    printf("  P to play song\n");
    printf("  p to pause\n");
    printf("  s to stop\n");
    printf("  q to quit\n");
    printf("  n to play next song\n");
    printf("  l to play last song\n");
}

int main() {
    Player player;

    int running = 1;

    Player_init(&player);

    system("clear");

    display_menu();
    printf("\n> ");

    char cmd;
    while (running) {
        cmd = getchar();

        if (cmd == 'q') {
            system("clear");
            break;
        } else if (cmd == 'L') {
            Player_listSongs(&player);

            printf("\n> ");
        } else if (cmd == 'P') {
            system("clear");
            Player_listSongs(&player);

            printf("\n> ");

            printf("Enter song index to play: ");
            int index;
            scanf("%d", &index);
            Player_play(&player, index);

            printf("\n> ");
        } else if (cmd == 'p') {
            system("clear");
            Player_listSongs(&player);

            printf("\n");

            Player_pause(&player);

            printf("\n> ");
        } else if (cmd == 'r') {
            system("clear");
            Player_listSongs(&player);

            printf("\n");

            Player_resume(&player);

            printf("\n> ");
        } else if (cmd == 's') {
            system("clear");
            Player_listSongs(&player);
            
            printf("\n");
            
            Player_stop(&player);

            printf("\n> ");
        } else if (cmd == 'n') {
            system("clear");
            Player_listSongs(&player);
            
            printf("\n");
            
            Player_next(&player);

            printf("\n> ");
        } else if (cmd == 'l') {
            system("clear");
            Player_listSongs(&player);
            
            printf("\n");
            
            Player_last(&player);

            printf("\n> ");
        }
    }

    Mix_HaltMusic();
    Mix_FreeMusic(player.currentSong->music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

