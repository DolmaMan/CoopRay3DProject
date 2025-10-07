#pragma once
#include <raylib.h>
#include<string>
#include<map>

struct Camera3DController;

extern Rectangle screenTextureRect;
extern Rectangle addMenuTextureRect;
extern Rectangle editMenuTextureRect;
extern Rectangle deleteMenuTextureRect;

extern std::map<std::string, Sound> ListSounds;

extern bool exitWindow;

extern Camera3DController cameraController;

extern RenderTexture screenTexture;
extern RenderTexture addMenuTexture;
extern RenderTexture editMenuTexture;
extern RenderTexture deleteMenuTexture;

enum MenusEnum { MainMenu, ExitMenu };
extern MenusEnum currentEnum;