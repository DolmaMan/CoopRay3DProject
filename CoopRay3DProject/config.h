#pragma once
#include <raylib.h>
#include<string>
#include<map>

struct Camera3DController;

extern Rectangle screenTextureRect;
extern std::map<std::string, Sound> ListSounds;

extern bool exitWindow;

extern Camera3DController cameraController;
extern RenderTexture screenTexture;

enum MenusEnum { MainMenu, ExitMenu };
extern MenusEnum currentEnum;