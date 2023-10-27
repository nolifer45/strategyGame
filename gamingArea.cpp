#include "raylib.h"
#include <vector>
#include <string>

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

Color GRAPHITE = {41, 41, 41, 255};

void setupGameGrid(void)
{
    DrawGrid(100, 1.0f);    // Draw a grid (size, slice size)
    // Here you can add more 3D objects to build your game area
    DrawLine3D({100,0,0},{-100,0,0},BLACK);
    DrawLine3D({0,100,0},{0,-100,0},BLUE);
    DrawLine3D({0,0,100},{0,0,-100},RED);
}



Camera3D updateCameraZoom(Camera3D camera) 
{
    float zoomValue = GetMouseWheelMove(); 
    camera.position.z += zoomValue/2;
    camera.position.y += zoomValue;
    return camera;
}

Camera3D updateCameraScroll(Camera3D camera)
{
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x > GetScreenWidth()-20)
    {
        camera.position.x -=.1;
         camera.target.x -=.1;
    }
    if (mousePos.x < 10)
    {
        camera.position.x +=.1;
        camera.target.x +=.1;
    }
    if (mousePos.y > GetScreenHeight()-20)
    {
        camera.position.y -=.1;
         camera.target.y -=.1;
    }
    if (mousePos.y < 10)
    {
        camera.position.y +=.1;
         camera.target.y +=.1;
    }
    return camera;
}

void handleFullscreenLogic(Vector2 screenResolution)
{
    if (!IsWindowFullscreen()) 
            {
                ToggleFullscreen();
                SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
            } else 
            {
                ToggleFullscreen();
                SetWindowSize(screenResolution.x, screenResolution.y);
            }
}
void drawGroundTexture(Texture2D ground, std::vector<int> randomRotationVector)
{   
    //För varje rotationsincrement måste hörnvectorn för varje ruta multipliceras med +/- 1 
    //för att motsvara rotationen
    int xyPlane = 100;
    for (int tileX = -xyPlane; tileX < xyPlane; tileX += 1){
        for (int tileY = -xyPlane; tileY < xyPlane; tileY += 1){
            Rectangle sourceRec = { 0.0f, 0.0f, (float)ground.width, (float)ground.height };
            Rectangle destRec = { (float)tileX, (float)tileY, 1.f, 1.f};
            Vector2 origin = {0.f, 0.f };
            
           /* if (randomRotationVector[tileX + tileY != 0])
            {
                destRec.x = randomRotationVector[tileX + tileY] *tileX;
                destRec.y = randomRotationVector[tileX + tileY] *tileY;
            }
            */
            DrawTexturePro(ground, sourceRec, destRec, origin, 0.f, WHITE);
    }
    }
}
std::vector<int> createTerrainRotationVector()
{
    std::vector<int> vector(10000);
    for (int &randomRotation : vector)
    {
        randomRotation  = (float)GetRandomValue(0,3);
    }
    return vector;
}

int main(void)
{
    // Initialization
    const int screenWidth = 960*1.5;
    const int screenHeight = 540*1.5;
    Vector2 screenResolution{screenWidth,screenHeight};
    InitWindow(screenWidth, screenHeight, "3D Strategy Game Area - Raylib");
    Texture2D mudTex = LoadTexture("D:\\Projects\\C++\\StrategyGame\\Assets\\TerrainTextures\\mud.png");
    // Define the camera to look into our 3d world
    Camera3D camera = { { -0, -10.0f, -5.0f }, // Camera position
                      { 0.0f, 0.0f, 0.0f },    // Camera looking at point
                      { 0.0f, 1.0f, 0.0f },    // Camera up vector (rotation towards target)
                      45.0f,                   // Camera field-of-view Y
                      CAMERA_PERSPECTIVE };

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    std::vector<int> randomRotationVector = createTerrainRotationVector();
    // Main game loop
    while (!WindowShouldClose()) {      // Detect window close button or ESC key
        // Toggle fullscreen
        if(IsKeyPressed(KEY_F))
         {
            handleFullscreenLogic(screenResolution);
         }
        // Draw
        BeginDrawing();
            ClearBackground(GRAPHITE);
            BeginMode3D(camera);
            camera = updateCameraZoom(camera);
            camera = updateCameraScroll(camera);     
            setupGameGrid();
            drawGroundTexture(mudTex,randomRotationVector);
            EndMode3D();
            
            DrawText("Welcome to the strategy game area!", 10, 40, 20, DARKGRAY);
            DrawFPS(10, 10);
            
            

        EndDrawing();
    }
    UnloadTexture(mudTex);
    CloseWindow();        // Close window and OpenGL context

    return 0;

}