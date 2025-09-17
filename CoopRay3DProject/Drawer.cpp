#include "drawer.h"
#include <raylib.h>

void Drawer::DrawScene(const Camera3DController& cameraController) {
    BeginMode3D(cameraController.camera);

    DrawGrid(20, 1.0f);

    DrawLine3D({ 0, 0, 0 }, { 5, 0, 0 }, RED);    
    DrawLine3D({ 0, 0, 0 }, { 0, 5, 0 }, GREEN);  
    DrawLine3D({ 0, 0, 0 }, { 0, 0, 5 }, BLUE);   

    DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, MAROON);

    DrawSphere({ 3.0f, 0.0f, 0.0f }, 1.0f, GREEN);
    DrawSphereWires({ 3.0f, 0.0f, 0.0f }, 1.0f, 16, 16, DARKGREEN);

    DrawCube({ 0.0f, 3.0f, 0.0f }, 1.0f, 1.0f, 1.0f, PURPLE);
    DrawSphere({ 3.0f, 3.0f, 0.0f }, 0.8f, ORANGE);

    EndMode3D();
}
