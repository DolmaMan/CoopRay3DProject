#include "drawer.h"

void DrawGridXY(int slices, float spacing)
{
    float halfSlices = (float)slices / 2.0f;

    for (int i = 0; i <= slices; i++)
    {
        float y = (i - halfSlices) * spacing;
        DrawLine3D(
            { -halfSlices * spacing, y, 0.0f },
            { halfSlices* spacing, y, 0.0f },
            LIGHTGRAY);
    }

    for (int i = 0; i <= slices; i++)
    {
        float x = (i - halfSlices) * spacing;
        DrawLine3D(
            { x, -halfSlices * spacing, 0.0f },
            { x, halfSlices* spacing, 0.0f },
            LIGHTGRAY
        );
    }
}

void Drawer::DrawScene(const Camera3DController& cameraController) {
    BeginMode3D(cameraController.camera);

    DrawGridXY(20, 1.0f);

    DrawLine3D({ 0, 0, 0 }, { 15, 0, 0 }, RED);    
    DrawLine3D({ 0, 0, 0 }, { 0, -15, 0 }, BLUE);   
    DrawLine3D({ 0, 0, 0 }, { 0, 0, 15 }, GREEN);

    for (auto fig : vecFigures) {
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Circle*>) {
                Circle::DrawCircle(arg);
            }
            else if constexpr (std::is_same_v<T, Ellipse*>) {
                Ellipse::DrawEllipse(arg);
            }
            else if constexpr (std::is_same_v<T, Helix*>) {
                Helix::DrawHelix(arg);
            }
        }, fig);
    }
    

    EndMode3D();
}

void Drawer::DrawScene(const Camera3DController& cameraController, char* pointStr, char* derStr)
{
    BeginMode3D(cameraController.camera);

    DrawGridXY(20, 1.0f);

    DrawLine3D({ 0, 0, 0 }, { 15, 0, 0 }, RED);
    DrawLine3D({ 0, 0, 0 }, { 0, -15, 0 }, BLUE);
    DrawLine3D({ 0, 0, 0 }, { 0, 0, 15 }, GREEN);

    for (auto fig : vecFigures) {
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Circle*>) {
                Circle::DrawCircle(arg);
            }
            else if constexpr (std::is_same_v<T, Ellipse*>) {
                Ellipse::DrawEllipse(arg);
            }
            else if constexpr (std::is_same_v<T, Helix*>) {
                Helix::DrawHelix(arg);
            }
            }, fig);
    }

    DrawFirstDerivative(pointStr, derStr);
    EndMode3D();
}

void Drawer::DrawFirstDerivative(char* pointStr, char* derStr)
{
    bool fl = false;
    Vector3 point{ 0 };
    Vector3 derVector{ 0 };
    for (auto& fig : vecFigures) {
        std::visit([&](auto&& arg) {
            if ((*arg).Properties.isHighlightedInMenu)
            {
                sscanf(pointStr, "%f;%f;%f", &point.x, &point.y, &point.z);
                sscanf(derStr, "%f;%f;%f", &derVector.x, &derVector.y, &derVector.z);
                
                fl = true;
            }
            }, fig);
        if (fl) {
            Vector3 arrowEnd = {
                (point.x + derVector.x),
                (point.y + derVector.y),
                (point.z + derVector.z)
            };

            DrawSphere(point, 0.1f, BLUE);
            DrawSphere(arrowEnd, 0.1f, RED);
            DrawLine3D(point, arrowEnd, RED);

            fl = false;
        }
    }
}