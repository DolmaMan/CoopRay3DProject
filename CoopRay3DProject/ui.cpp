#include "ui.h"


void UI::DrawMainMenu() {
    GetScene();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTextureRec(screenTexture.texture, screenTextureRect, { 0.0,0.0 }, RAYWHITE); //—ÂÚÍ‡


    DrawText("WASD: Move camera", 10, 60, 16, DARKGRAY);
    DrawText("Right mouse button: Free camera mode", 10, 80, 16, DARKGRAY);
    DrawText("R: Reset camera", 10, 100, 16, DARKGRAY);
    DrawText("ESC: Exit", 10, 120, 16, DARKGRAY);

    DrawRectangle(0, 0, GetScreenWidth(), 50, Color{ 230, 230, 230, 255 });
    DrawRectangle(0, 50, GetScreenWidth(), 1, GRAY);

    

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 255);

    if (GuiButton({ 20, 10, 120, 30 }, "Add Shape"))
    {

    };

    if (GuiButton({ 150, 10, 120, 30 }, "Delete Shape"))
    {

    };

    if (GuiButton({ 280, 10, 120, 30 }, "Edit Shape"))
    {

    };

    /*DrawRectangle(20, 10, 120, 30, Color{ 200, 200, 200, 255 });
    DrawRectangleLines(20, 10, 120, 30, GRAY);
    DrawText("Add Shape", 35, 17, 16, BLACK);*/

    /*DrawRectangle(150, 10, 120, 30, Color{ 200, 200, 200, 255 });
    DrawRectangleLines(150, 10, 120, 30, GRAY);
    DrawText("Delete Shape", 160, 17, 16, BLACK);*/

    /*DrawRectangle(280, 10, 120, 30, Color{ 200, 200, 200, 255 });
    DrawRectangleLines(280, 10, 120, 30, GRAY);
    DrawText("Edit Shape", 295, 17, 16, BLACK);*/

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
    DrawRectangle(0, 100, GetScreenWidth(), 200, BLACK);
    DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);

    EndDrawing();

    if (IsKeyPressed(KEY_Y) || WindowShouldClose()) exitWindow = true;
    else if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_N)) currentEnum = MenusEnum::MainMenu;

}

void UI::GetScene()
{
    cameraController.HandleInput();
    cameraController.Update();

    BeginTextureMode(screenTexture);
    ClearBackground(RAYWHITE);
    Drawer::DrawScene(cameraController);
    EndTextureMode();
}
