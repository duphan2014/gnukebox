#include "player.h"

int DEBUG = 0;

int Player_init(Player *self) {
    if (DEBUG) printf("Player_init 1\n");
    self->numberOfSongs = 0;  // Initialize to 0
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (!dir) {
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
}
void Player_listSongs(Player *self) {
    printf("Available Songs:\n");
    for(int i = 0; i < self->numberOfSongs; i++) {
        printf(".%s\n", self->songs[i].songName);
    }
}

void Player_play(Player *self) {

}
void Player_pause(Player *self) {

}
void Player_resume(Player *self) {

}
void Player_stop(Player *self) {

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
    printf("  l to list songs\n");
    printf("  q to quit\n");

    char cmd;
    while (running) {
        cmd = getchar();

        if (cmd == 'q') {
            break;
        } else if (cmd == 'l') {
            Player_listSongs(&player);
        }

    }
}

