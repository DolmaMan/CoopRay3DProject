#include "drawer.h"

void Drawer::DrawScene(const Camera3DController& cameraController) {
    BeginMode3D(cameraController.camera);

    DrawGrid(20, 1.0f);

    DrawLine3D({ 0, 0, 0 }, { 5, 0, 0 }, RED);    
    DrawLine3D({ 0, 0, 0 }, { 0, 5, 0 }, GREEN);  
    DrawLine3D({ 0, 0, 0 }, { 0, 0, 5 }, BLUE);   

    for (auto fig : vecFigures) {
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Circle*>) {
                Circle::DrawCircle(arg);
            }
            else if constexpr (std::is_same_v<T, Ellipse>) {

            }
            }, fig);
    }
    

    EndMode3D();
}
