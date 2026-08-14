#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "raylib.h"

#define FPS 60
#define SCREENWIDTH 800
#define SCREENHEIGHT 450

// buttons size
#define WTOUCH 100
#define HTOUCH 100
#define WUPGRADE 100
#define HUPGRADE 100

// margins
#define TEXTMARGIN 5
#define FONTSIZE 20

void incPoints(int *points, int step);
int getCurrentStep();
void incStep(int *points, int upgradeCost);

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = SCREENWIDTH;
    int screenHeight = SCREENHEIGHT;

    InitWindow(screenWidth, screenHeight, "clicker");

    SetTargetFPS(FPS);

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    //--------------------------------------------------------------------------------------
    
    int points = 0;
    int upgradeCost = 5;

    Vector2 touchPosition = { 0, 0 };

    int currentGesture = GESTURE_NONE;
    int lastGesture = GESTURE_NONE;

    //                      x    -y   w    h   
    Rectangle touchArea = { 100, 100, WTOUCH, HTOUCH };
    Rectangle upgradeArea = { 100, 150 + HTOUCH, WUPGRADE, HUPGRADE };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // screen resizing
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
#if 0
        Rectangle touchArea = { 100, 100, 100, 100 };
#endif

        // current touch and gesture
        touchPosition = GetTouchPosition(0);
        lastGesture = currentGesture;
        currentGesture = GetGestureDetected();

        // checks for tap
        if (CheckCollisionPointRec(touchPosition, touchArea) && currentGesture != GESTURE_NONE)
            if (currentGesture != lastGesture)
                if (currentGesture == GESTURE_TAP)
                    incPoints(&points, getCurrentStep());
        if (CheckCollisionPointRec(touchPosition, upgradeArea) && currentGesture != GESTURE_NONE)
            if (currentGesture != lastGesture)
                if (currentGesture == GESTURE_TAP)
                    incStep(&points, upgradeCost);
        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangleRec(touchArea, GRAY);
            DrawRectangleRec(upgradeArea, LIME); 
            DrawText(TextFormat("upgrade costs: %i taps", upgradeCost), 100 + TEXTMARGIN, 150 + HTOUCH + TEXTMARGIN, 20, RED);
            DrawText(TextFormat("taps: %i", points), 10, 10, FONTSIZE, (points % 10 == 0) ? GOLD : LIGHTGRAY);
            DrawText(TextFormat("current step: %i", getCurrentStep()), 10, 10 + FONTSIZE + TEXTMARGIN, FONTSIZE, LIGHTGRAY);
        EndDrawing();
    }
    // Close window and OpenGL context
    CloseWindow();   
    return 0;
}

void incPoints(int *points, int step)
{
    (*points) += step;
}

int step = 1;
int getCurrentStep()
{
    return step;
}

void incStep(int *points, int upgradeCost)
{
    if (*points >= upgradeCost) {
        *points -= upgradeCost;
        step++;
    }
}
