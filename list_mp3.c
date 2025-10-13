#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(void) {
    struct dirent *entry;
    DIR *dir = opendir(".");

    if (!dir) {
        perror("opendir");
        return 1;
    }

    printf("=== MP3 Files in Current Directory ===\n");

    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;
        size_t len = strlen(name);

        if (len > 4 && strcmp(name + len - 4, ".mp3") == 0) {
            printf(" - %s\n", name);
        }
    }

    closedir(dir);
    return 0;
}