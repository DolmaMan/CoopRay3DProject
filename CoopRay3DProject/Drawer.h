#pragma once
#include <raylib.h>
#include"config.h"
#include"Figures.h"
#include "initProgram.h"

class Drawer {
public:
    // Структура для хранения вершины эллипсоида
    struct EllipsoidVertex {
        Vector3 position;
        Color color;
    };

    static void DrawScene(const Camera3DController& cameraController);
};
