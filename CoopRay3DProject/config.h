#pragma once
#include<raylib.h>
#include<vector>
#include<string>
#include<variant>
#include<unordered_map>

struct Camera3DController;

extern int screenWidth;
extern int screenHeight;

extern Rectangle screenTextureRect;

extern Rectangle bigRect;
extern Rectangle listFiguresRect;

extern std::unordered_map<std::string, Sound> ListSounds;

extern bool exitWindow;

extern Camera3DController cameraController;

extern RenderTexture screenTexture;

enum MenusEnum { MainMenu, ExitMenu };
extern MenusEnum currentEnum;

class Circle;
class Ellipse;

