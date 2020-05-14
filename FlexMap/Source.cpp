#include "raylib.h"
#include <stdio.h>

#include "Parser.hpp"

void ZoomRelativeToMouse();

void UpdateDrawFrame(void);

bool debug = true;

Camera2D camera = { 0 };
Vector2 oldMousePos;
bool mouseWasPressed = false;


int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    ParseFile("lejr.osm");
    
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Donkey Fucker");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void ZoomRelativeToMouse()
{
    float wheelMove = (float)GetMouseWheelMove();
    if (wheelMove != 0.0) {
        float oldZoom = camera.zoom;
        camera.zoom += (wheelMove * 0.025f);
        if (camera.zoom < 0.1f) camera.zoom = oldZoom;
        if (camera.zoom != oldZoom) {
            float x = GetMousePosition().x + (camera.offset.x - GetMousePosition().x) * (float)camera.zoom / (float)oldZoom;
            float y = GetMousePosition().y + (camera.offset.y - GetMousePosition().y) * (float)camera.zoom / (float)oldZoom;
            camera.offset.x = x;
            camera.offset.y = y;
            if (debug)
            {
                printf("Camera Moved: (%f, %f), ", x, y);
                printf("camera.zoom(%f) / oldZoom(%f): %f\n", (float)camera.zoom, (float)oldZoom, ((float)camera.zoom / (float)oldZoom));
            }
        }
    }
}

void Drag()
{
    bool mouseIsPressed = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    
    
    if (mouseIsPressed && !mouseWasPressed) {
        if (debug) printf("Mouse Was Pressed\n");
        oldMousePos = GetMousePosition();
        mouseWasPressed = true;
    } 
    else if (!mouseIsPressed && mouseWasPressed) {
        if (debug) printf("Mouse Was DePressed\n");
        mouseWasPressed = false;
    }
    if (mouseWasPressed) {
        Vector2 mousePos = GetMousePosition();
        camera.offset.x += mousePos.x - oldMousePos.x;
        camera.offset.y += mousePos.y - oldMousePos.y;
        oldMousePos = mousePos;
    }
}

static unsigned int g_seed = 210312;

inline int fastrand() {
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

void UpdateDrawFrame(void)
{
    // Update
           //----------------------------------------------------------------------------------
           // TODO: Update your variables here
           //----------------------------------------------------------------------------------
    if (IsKeyDown(KEY_RIGHT)) camera.offset.x -= 2.0f;
    if (IsKeyDown(KEY_LEFT)) camera.offset.x += 2.0f;
    if (IsKeyDown(KEY_UP)) camera.offset.y += 2.0f;
    if (IsKeyDown(KEY_DOWN)) camera.offset.y -= 2.0f;

    ZoomRelativeToMouse();
    Drag();
    // Camera reset (zoom and rotation)
    if (IsKeyPressed(KEY_R))
    {
        camera.zoom = 1.0f;
        camera.rotation = 0.0f;
    }


    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    {

        ClearBackground(RAYWHITE);

        

        BeginMode2D(camera);
        {
            DrawLine(0, 0, screenWidth, screenHeight, BLACK);
            DrawLine(screenWidth, 0, 0, screenHeight, BLACK);
            for (int i = 0; i < 100000; i++) {
                DrawLineEx({ (float)fastrand() / 10, (float)fastrand() / 10 }, { (float)fastrand() / 10, (float)fastrand() / 10 }, 30, BLACK);
            }
        }
        EndMode2D();
        DrawFPS(0, 0);
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
}