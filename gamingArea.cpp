#include "raylib.h"

class Character
{
private:
    /* data */
public:
    Character(/* args */);
    ~Character();
};

Character::Character(/* args */)
{
}




int main(void)
{
// Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "3D Strategy Game Area - Raylib");

    // Define the camera to look into our 3d world
    Camera camera = { { 10.0f, 10.0f, 10.0f }, // Camera position
                      { 0.0f, 0.0f, 0.0f },    // Camera looking at point
                      { 0.0f, 1.0f, 0.0f },    // Camera up vector (rotation towards target)
                      45.0f,                   // Camera field-of-view Y
                      CAMERA_PERSPECTIVE };

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    
    // Main game loop
    while (!WindowShouldClose()) {      // Detect window close button or ESC key
        // Update
        UpdateCamera(&camera,CAMERA_ORBITAL);          // Update camera

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(100, 10.0f);    // Draw a grid (size, slice size)
                // Here you can add more 3D objects to build your game area
                DrawLine3D({100,0,0},{-100,0,0},BLACK);
                DrawLine3D({0,100,0},{0,-100,0},BLUE);
                DrawLine3D({0,0,100},{0,0,-100},RED);
            EndMode3D();
            
            DrawText("Welcome to the strategy game area!", 10, 40, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;

}