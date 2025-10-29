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


std::unordered_map<std::string, Font> ListFonts;
std::string currentFontName;

std::vector<figure_variant> vecFigures;

void LoadSounds() {
    std::string folder_path = "..\\assets\\audio";

    try {
        // Ñîçäàåì èòåðàòîð äëÿ ïàïêè
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            // Ïîëó÷àåì èíôîðìàöèþ î òåêóùåì ýëåìåíòå
            std::string file_path = entry.path().string(); // Ïîëíûé ïóòü ê ôàéëó/ïàïêå

            if (entry.is_regular_file()) { // Åñëè ýòî îáû÷íûé ôàéë
                ListSounds[entry.path().filename().string()] = LoadSound(entry.path().string().c_str());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}

void LoadFonts() {
    ListFonts["Consolas"] = LoadFont("..\\assets\\fonts\\consolab.ttf");
    ListFonts["Minecraft"] = LoadFont("..\\assets\\fonts\\minecraft.ttf");
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
    

    bigRect = { 0.0f ,50.0f, (float)screenWidth, (float)screenHeight - 80 };
    listFiguresRect = { (float)screenWidth - 300, 135, 300, (float)screenHeight - 165 };
    
    UI::LoadUiControls();

    InitAudioDevice();
    LoadSounds();
    LoadFonts();

    GuiSetFont(ListFonts[currentFontName]);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);

    while (!exitWindow) {
            UI::DrawMainMenu();
    }

    CleanupProgram();

    return 0;
}