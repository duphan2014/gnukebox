#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>

#include "player.h"

int main() {
    Player player;
    Player_init(&player);

    initscr();
    noecho();
    curs_set(FALSE);

    keypad(stdscr, TRUE); // enable arrow key

    char *options[player.numberOfSongs];

    for (int i = 0; i < player.numberOfSongs; i++) {
        options[i] = player.songs[i].songName;
    }

    char *descriptions[] = {
        "This is the first option\nIt does something cool\nPress Enter to select",
        "This is the second option\nIt has different functionality\nTry it out!",
        "Exit the program\nPress Enter to quit\nGoodbye!"
    };
    int choice = 0;
    int ch;

    int n_options = 3;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); // rows, columns
    int split_x = max_x / 6;
    int split_y = max_y / 6;

    while (1) {
        clear();
        
        // Draw vertical separator
        for (int y = 0; y < max_y; y++) {
            mvprintw(y, split_x, "|");
        }

        // Draw horizontal separator on main content
        for (int x = max_x/8; x < max_x; x++ ) {
            mvprintw(5, split_y + 1 + x, "_");
        }
        
        // Draw menu options on the left side
        mvprintw(0, 2, "Menu:");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) attron(A_REVERSE);
            mvprintw(i + 2, 2, "%s", options[i]);
            if (i == choice) attroff(A_REVERSE);
        }
        
        // Draw description on the right side
        mvprintw(0, split_x + 2, "Description:");
        int desc_y = 2;
        char *desc = descriptions[choice];
        char *line = strtok(strdup(desc), "\n");
        while (line != NULL) {
            mvprintw(desc_y, split_x + 2, "%s", line);
            desc_y++;
            line = strtok(NULL, "\n");
        }
        
        refresh();
        ch = getch();

        if (ch == 'q') break;
        else if (ch == KEY_UP && choice > 0) choice--;
        else if (ch == KEY_DOWN && choice < n_options - 1) choice++;
        else if (ch == '\n' || ch == KEY_ENTER) {
            if( choice == 2) break; // quit
            else if (choice == 0) {
                mvprintw(max_y - 2, 2, "You selected: %s", options[0]);
                refresh();
                getch();
            } else if (choice == 1) {
                mvprintw(max_y - 2, 2, "You selected: %s", options[1]);
                refresh();
                getch();
            }
        }
    }
    endwin(); // Clean up ncurses
    return 0;
} 