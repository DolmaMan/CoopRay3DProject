#include<filesystem>
#include<string>
#include<iostream>

#include "initProgram.h"
#include "drawer.h"
#include "ui.h"

#include "config.h"


Rectangle screenTextureRect;
std::map<std::string, Sound> ListSounds;

void LoadSounds() {
    std::string folder_path = "..\\assets\\audio"; // Путь к папке (в данном случае, текущая папка)

    try {
        // Создаем итератор для папки
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            // Получаем информацию о текущем элементе
            std::string file_path = entry.path().string(); // Полный путь к файлу/папке

            if (entry.is_regular_file()) { // Если это обычный файл
                ListSounds[entry.path().filename().string()] = LoadSound(entry.path().string().c_str());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Ошибка файловой системы: " << e.what() << std::endl;
    }
}

int main() 
{
    InitProgram();
    SetExitKey(KEY_NULL);

    Camera3DController cameraController;
    RenderTexture screenTexture = LoadRenderTexture(GetScreenWidth()-300, GetScreenHeight());
    screenTextureRect = { 0.0f, 50.0f, (float)screenTexture.texture.width, (float)-screenTexture.texture.height };

    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;

    InitAudioDevice();
    LoadSounds();


    while (!exitWindow) {
        if (exitWindowRequested)
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            
            
            // СДЕЛАТЬ МЕНЮ ВЫХОДА
            DrawRectangle(0, 100, GetScreenWidth(), 200, BLACK);
            DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, WHITE);

            EndDrawing();

            if (IsKeyPressed(KEY_Y) || WindowShouldClose()) break;
            else if (IsKeyReleased(KEY_ESCAPE) || IsKeyPressed(KEY_N)) exitWindowRequested = false;

            continue;
        }
        else 
        {


            if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
                PlaySound(ListSounds["General_Quitgame.wav"]);
                exitWindowRequested = true;
                continue;
            }
        }

        cameraController.HandleInput();
        cameraController.Update();

        BeginTextureMode(screenTexture);
        ClearBackground(RAYWHITE);
        Drawer::DrawScene(cameraController);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureRec(screenTexture.texture, screenTextureRect, { 0.0,0.0 }, RAYWHITE);

        UI::DrawUI();

        EndDrawing();
    }

    CleanupProgram();

    return 0;
}