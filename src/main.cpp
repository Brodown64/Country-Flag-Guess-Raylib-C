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

    const char* files[512]; // file amount detected
    int count = 0;
    while ((entry = readdir(dp))!= NULL) { // while directory is read
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
    Texture2D button = LoadTexture("resources/button.jpg");

    float frameHeight = (float)button.height;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };

    Rectangle btnBounds = { screenWidth/2.0f - button.width/2.0f, screenHeight/2.0f - button.height/2.0f, (float)button.width, frameHeight };

    Vector2 mousePoint = { 0.0f, 0.0f };

    int btnState = 0;                
    bool btnAction = false;         


    ImageResize(&country, 300, 200);

    UnloadImage(country);

    Vector2 position = {250, 200}; // position on screen

    bool flagChosen = false;

    while (!WindowShouldClose()) {
       mousePoint = GetMousePosition();
       if (IsKeyPressed(KEY_K) && !flagChosen) {
            if (showImage) UnloadTexture(texture);

            const char* randomFlag = GetRandomFlagPath();
            if (randomFlag == NULL) continue;

            Image flag = LoadImage(randomFlag);
            ImageResize(&flag, 300, 200);
            texture = LoadTextureFromImage(flag);
            UnloadImage(flag);

            showImage = true;
            flagChosen = true;

        }

        btnAction = false;

        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                btnState = 2;
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                btnAction = true;
            } else {
                btnState = 1;
            }

        } else {
            btnState = 0;
        }

        if (btnAction)
        {
            printf("Works!");

            // TODO: Any desired action
        }

        BeginDrawing();
        ClearBackground(darkGreen);

        if (!flagChosen) {
            DrawText("Press K to play", 340, 520, 20, RED);
        } else {
            DrawText("Only one flag per game!", 290, 520, 20, RED);
        }
        if (showImage) {
            DrawTextureV(texture, position, WHITE);
            DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
        }

        DrawText("Country Guess Game", 300, 80, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
