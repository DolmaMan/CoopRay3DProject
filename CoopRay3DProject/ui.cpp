#include "ui.h"
#include <raylib.h>

void UI::DrawUI() {

    DrawText("WASD: Move camera", 10, 60, 16, DARKGRAY);
    DrawText("Right mouse button: Rotate camera", 10, 80, 16, DARKGRAY);
    DrawText("R: Reset camera", 10, 100, 16, DARKGRAY);
    DrawText("ESC: Exit", 10, 120, 16, DARKGRAY);

    DrawRectangle(0, 0, GetScreenWidth(), 50, Color{ 230, 230, 230, 255 });
    DrawRectangle(0, 50, GetScreenWidth(), 1, GRAY);

    DrawRectangle(20, 10, 120, 30, Color{ 200, 200, 200, 255 });
    DrawRectangleLines(20, 10, 120, 30, GRAY);
    DrawText("Add Shape", 35, 17, 16, BLACK);

    DrawRectangle(150, 10, 120, 30, Color{ 200, 200, 200, 255 });
    DrawRectangleLines(150, 10, 120, 30, GRAY);
    DrawText("Delete Shape", 160, 17, 16, BLACK);

    DrawRectangle(280, 10, 120, 30, Color{ 200, 200, 200, 255 });
    DrawRectangleLines(280, 10, 120, 30, GRAY);
    DrawText("Edit Shape", 295, 17, 16, BLACK);

    DrawRectangle(GetScreenWidth() - 300, 50, 300, GetScreenHeight() - 50, Color{ 240, 240, 240, 255 });
    DrawRectangle(GetScreenWidth() - 300, 50, 1, GetScreenHeight() - 50, GRAY);

    DrawText("SHAPES LIST", GetScreenWidth() - 290, 65, 20, BLACK);
    DrawRectangle(GetScreenWidth() - 300, 95, 300, 1, GRAY);


    DrawText("ID", GetScreenWidth() - 290, 110, 16, DARKGRAY);
    DrawText("Type", GetScreenWidth() - 250, 110, 16, DARKGRAY);
    DrawText("Position", GetScreenWidth() - 190, 110, 16, DARKGRAY);

    DrawRectangle(GetScreenWidth() - 300, 135, 300, 1, GRAY);


    DrawRectangle(0, GetScreenHeight() - 30, GetScreenWidth(), 30, Color{ 240, 240, 240, 255 });
    DrawRectangle(0, GetScreenHeight() - 30, GetScreenWidth(), 1, GRAY);
    DrawText("", 10, GetScreenHeight() - 22, 16, DARKGRAY);

    DrawFPS(GetScreenWidth() - 80, GetScreenHeight() - 25);
}
