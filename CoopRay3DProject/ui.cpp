#include "ui.h"
bool addMenuRequested = false,
     editMenuRequested = false,
     deleteMenuRequested = false;

void UI::DrawMainMenu() {
    if (
        !addMenuRequested &&
        !editMenuRequested &&
        !deleteMenuRequested
        ) 
    {
        cameraController.HandleInput();
        cameraController.Update();
    }
    BeginTextureMode(screenTexture);
    ClearBackground(RAYWHITE);
    Drawer::DrawScene(cameraController);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTextureRec(screenTexture.texture, screenTextureRect, { 0.0,50.0 }, RAYWHITE); //—ÂÚÍ‡


    DrawText("WASD: Move camera", 10, 60, 16, DARKGRAY);
    DrawText("Right mouse button or TAB: Free camera mode", 10, 80, 16, DARKGRAY);
    DrawText("R: Reset camera", 10, 100, 16, DARKGRAY);
    DrawText("ESC: Exit", 10, 120, 16, DARKGRAY);

    DrawRectangle(0, 0, GetScreenWidth(), 50, Color{ 230, 230, 230, 255 });
    DrawRectangle(0, 50, GetScreenWidth(), 1, GRAY);

    

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 255);

    if (GuiButton({ 20, 10, 120, 30 }, "Add Shape"))
    {
        addMenuRequested = true;
    };

    if (GuiButton({ 150, 10, 120, 30 }, "Delete Shape"))
    {
        deleteMenuRequested = true;
    };

    if (GuiButton({ 280, 10, 120, 30 }, "Edit Shape"))
    {
        editMenuRequested = true;
    };

    if (addMenuRequested)
    {
        DrawAddMenu();
    }
    else if (editMenuRequested) 
    {
        DrawEditMenu();
    }
    else if(deleteMenuRequested)
    {
        DrawDeleteMenu();
    }


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

    EndDrawing();

    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
        PlaySound(ListSounds["General_Quitgame.wav"]);
        currentEnum = MenusEnum::ExitMenu;
    }
}

void UI::DrawExitMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);


    // —ƒ≈À¿“‹ Ã≈Õﬁ ¬€’Œƒ¿
    Color BgCol = { 0, 0, 0, 200 };
    DrawRectangle(0, 200, GetScreenWidth(), 200, BgCol);
    DrawText("Are you sure you want to exit program? [Y/N]", 40, 270, 30, WHITE);

    EndDrawing();

    if (IsKeyPressed(KEY_Y) || WindowShouldClose()) exitWindow = true;
    else if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_N)) currentEnum = MenusEnum::MainMenu;

}

void UI::DrawAddMenu() 
{
    static Rectangle menuRect = { 420.0, 160.0, 400, 400 };
    DrawRectanglePro(menuRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menuRect.x + 1, menuRect.y, menuRect.width - 1, menuRect.height - 1, BLACK);

    static Rectangle rect = { menuRect.x, menuRect.y, 100, 10 };
    static char* str = new char[100] {'\0'};
    if (GuiTextBox(rect, str, 100, true)) {

    };
    static const char* str2 = "Circle;Ellipse;Helix";
    static int selectedIndex = 0;
    static bool editMode = false;
    static Rectangle topRect = { menuRect.x, menuRect.y + 25, 400, 25 };
    if (GuiDropdownBox({menuRect.x + 100, menuRect.y + 100, 100, 20 }, str2, &selectedIndex, editMode)) {
        editMode = !editMode;
    }

    if (GuiButton({ menuRect.x + 375, menuRect.y, 25, 25 }, "X"))
    {
        addMenuRequested = false;
    }
    

}

void UI::DrawEditMenu() 
{

}

void UI::DrawDeleteMenu() 
{

}
