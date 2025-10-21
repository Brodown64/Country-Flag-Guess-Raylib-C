#include <raylib.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>

#define FLAGS_DIR "flags/"

const char* GetRandomFlagPath() {
    static char filepath[256];
    struct dirent *entry;
    DIR *dp = opendir(FLAGS_DIR);

    if (dp == NULL) {
        printf("Failed to open directory: %s\n", FLAGS_DIR);
        return NULL;
    }

    const char* files[512];
    int count = 0;
    while ((entry = readdir(dp))!= NULL) {
        if (strstr(entry->d_name, ".png")) {
            files[count++] = strdup(entry->d_name);
        }
    }
    closedir(dp);

    if (count == 0) return NULL;

    int randomIndex = GetRandomValue(0, count - 1);
    snprintf(filepath, sizeof(filepath), "%s%s", FLAGS_DIR, files[randomIndex]);

    for (int i = 0; i< count; i++) free((void*)files[i]);

    return filepath;
}

int main(void) {
    Color darkGreen = {20, 160, 133, 255};
    int screenWidth = 800;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Countryguess");
    SetTargetFPS(60);

    srand(time(NULL));
    Texture2D texture = {0};
    bool showImage = false;

    Image country = LoadImage("flags/ar.png");

    ImageResize(&country, 300, 200);

    UnloadImage(country);

    Vector2 position = {250, 200}; // position on screen

    while (!WindowShouldClose()) {
       if (IsKeyPressed(KEY_K)) {
            if (showImage) UnloadTexture(texture);

            const char* randomFlag = GetRandomFlagPath();
            if (randomFlag == NULL) continue;

            Image flag = LoadImage(randomFlag);
            ImageResize(&flag, 300, 200);
            texture = LoadTextureFromImage(flag);
            UnloadImage(flag);

            showImage = true;
        }

        BeginDrawing();
        ClearBackground(darkGreen);

        if (showImage) {
            DrawTextureV(texture, position, WHITE);
        }

        DrawText("Country Guess Game", 300, 80, 20, RED);
        DrawText("Press K to play", 340, 520, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
