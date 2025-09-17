#include "initProgram.h"
#include "drawer.h"
#include "ui.h"

int main() {

    InitProgram();

    Camera3DController cameraController;

    while (!WindowShouldClose()) {
        cameraController.HandleInput();
        cameraController.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Drawer::DrawScene(cameraController);

        UI::DrawUI();

        EndDrawing();
    }

    CleanupProgram();

    return 0;
}