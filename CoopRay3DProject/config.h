#pragma once
#include <raylib.h>
#include<vector>
#include<string>
#include<unordered_map>

struct Camera3DController;

extern Rectangle screenTextureRect;

extern std::unordered_map<std::string, Sound> ListSounds;

extern bool exitWindow;

extern Camera3DController cameraController;

extern RenderTexture screenTexture;

enum MenusEnum { MainMenu, ExitMenu };
extern MenusEnum currentEnum;

extern class Figure;

extern std::unordered_map<std::string, std::vector<Figure>> mapFigures;