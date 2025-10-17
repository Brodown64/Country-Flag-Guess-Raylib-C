#include <raylib.h>
#include <stdio.h>

int main(void) {
    Color darkGreen = {20, 160, 133, 255};
    int screenWidth = 800;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Countryguess");
    SetTargetFPS(60);

    Image country = LoadImage("flags/ar.png");

    ImageResize(&country, 300, 200);

    Texture2D texture = LoadTextureFromImage(country);
    UnloadImage(country);

    Vector2 position = {250, 200}; // position on screen
    bool showImage = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_K) && !showImage) {
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
