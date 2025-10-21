#include<filesystem>
#include<string>
#include<iostream>

#include "initProgram.h"
#include "drawer.h"
#include "ui.h"

#include "config.h"

int screenWidth;
int screenHeight;

Rectangle screenTextureRect;
Rectangle addMenuTextureRect;

Rectangle bigRect;
Rectangle listFiguresRect;

std::unordered_map<std::string, Sound> ListSounds;

bool exitWindowRequested = false;   // Flag to request window to exit
bool exitWindow = false;

Camera3DController cameraController;

RenderTexture screenTexture;
RenderTexture addMenuTexture;

MenusEnum currentEnum;

std::unordered_map<std::string, Font> ListFonts;
std::string currentFontName;

std::vector<figure_variant> vecFigures;

void LoadSounds() {
    std::string folder_path = "..\\assets\\audio";

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

void LoadFonts() {
    ListFonts["Consolas"] = LoadFont("..\\assets\\fonts\\consolab.ttf");
    ListFonts["Braille"] = LoadFont("..\\assets\\fonts\\braille.ttf");
    currentFontName = "Consolas";
}

int main() 
{
    InitProgram();
    SetExitKey(KEY_NULL);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    screenTexture = LoadRenderTexture(screenWidth - 300, screenHeight - 80);
    screenTextureRect = { 0.0f, 0.0f, (float)screenTexture.texture.width, (float)-screenTexture.texture.height };
    
    currentEnum = MainMenu;

    bigRect = { 0.0f ,50.0f, (float)screenWidth, (float)screenHeight - 80 };
    listFiguresRect = { (float)screenWidth - 300, 135, 300, (float)screenHeight - 165 };
    
    InitAudioDevice();
    LoadSounds();
    LoadFonts();

    GuiSetFont(ListFonts[currentFontName]);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);

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