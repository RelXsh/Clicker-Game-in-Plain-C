#include <assert.h>
#include "raylib.h"
#include "game_model.c"

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

void updateData();

void incPoints();
int getCurrentStep();
void incStep();

int points;
int upgradeCost;
int step;

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
    initialize_game_logic();    
    updateData();

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
        if (currentGesture == GESTURE_TAP)
            if (currentGesture != lastGesture) {
                if (CheckCollisionPointRec(touchPosition, touchArea))
                    incPoints();
                else if (CheckCollisionPointRec(touchPosition, upgradeArea))
                    incStep();
            }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText(TextFormat("taps: %i", points), 10, 10, FONTSIZE, (points % 10 == 0) ? GOLD : LIGHTGRAY);
            DrawText(TextFormat("current step: %i", step), 10, 10 + FONTSIZE + TEXTMARGIN, FONTSIZE, LIGHTGRAY);

            DrawRectangleRec(touchArea, GRAY);
            DrawRectangleRec(upgradeArea, LIME); 
            DrawText(TextFormat("upgrade costs: %i taps", upgradeCost), 10, 150 + HTOUCH - TEXTMARGIN - FONTSIZE, 20, RED);
        EndDrawing();
    }

    save_data();

    // Close window and OpenGL context
    CloseWindow();   
    return 0;
}

void incPoints()
{
    increase_points();
    updateData();
}

void incStep()
{
    try_upgrade_step(get_upgrade_price());
    updateData();
}

void updateData()
{
    points = get_current_points();
    upgradeCost = get_upgrade_price();
    step = get_step();
}
