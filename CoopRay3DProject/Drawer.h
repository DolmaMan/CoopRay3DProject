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
    static void DrawEllipsoid(Vector3 position, float radiusX, float radiusY, float radiusZ,
        int segments, Color color);
    static std::vector<unsigned short> GenerateEllipsoidIndices(int segments);
    static std::vector<EllipsoidVertex> GenerateEllipsoidVertices(float radiusX, float radiusY, float radiusZ, int segments, Color color);
};
