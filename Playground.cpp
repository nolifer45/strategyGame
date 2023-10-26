#include "raylib.h"

int main(void)
{
// Initialize the window and OpenGL context
    const int screenWidth = 1600;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Raylib 3D Shape Example");

    // Define the camera and its target
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (set to point towards the sky)
    camera.fovy = 60.0f;                                // Camera field-of-view Y
    //camera.type = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);                                   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {                      // Detect window close button or ESC key
        // Update
        UpdateCamera(&camera,CAMERA_THIRD_PERSON);                          // Update internal camera parameters (free camera)

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);        // Draw a red cube
                DrawGrid(10, 1.0f);                                   // Draw a grid

            EndMode3D();

            DrawText("Welcome to the Raylib 3D world!", 10, 10, 20, BLACK);
            DrawFPS(screenWidth - 90, screenHeight - 30);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;

}