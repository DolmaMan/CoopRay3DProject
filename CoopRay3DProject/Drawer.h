#pragma once
#include <raylib.h>
#include"config.h"
#include"Figures.h"
#include "initProgram.h"

class Drawer {
public:
    static void DrawScene(const Camera3DController& cameraController);
};
