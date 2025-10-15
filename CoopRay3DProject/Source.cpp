#include<filesystem>
#include<string>
#include<iostream>

#include "initProgram.h"
#include "drawer.h"
#include "ui.h"

#include "config.h"


Rectangle screenTextureRect;
Rectangle addMenuTextureRect;

std::unordered_map<std::string, Sound> ListSounds;

bool exitWindowRequested = false;   // Flag to request window to exit
bool exitWindow = false;

Camera3DController cameraController;

RenderTexture screenTexture;
RenderTexture addMenuTexture;

MenusEnum currentEnum;

std::unordered_map<std::string, std::vector<Figure>> mapFigures;

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

    screenTexture = LoadRenderTexture(GetScreenWidth()-300, GetScreenHeight()-80);
    screenTextureRect = { 0.0f, 0.0f, (float)screenTexture.texture.width, (float)-screenTexture.texture.height };
    
    currentEnum = MainMenu;

    
    InitAudioDevice();
    LoadSounds();



    while (!exitWindow) {
        switch (currentEnum) {
        case MainMenu: {
            UI::DrawMainMenu();
        }break;
        case ExitMenu: {
            UI::DrawExitMenu();
        }break;
        }
    }

    CleanupProgram();

    return 0;
}