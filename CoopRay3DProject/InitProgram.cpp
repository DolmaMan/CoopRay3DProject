#include "InitProgram.h"


Camera3DController::Camera3DController() {
    cameraPosition = { 10.0f, 10.0f, 10.0f };
    cameraTarget = { 0.0f, 0.0f, 0.0f };
    cameraUp = { 0.0f, 1.0f, 0.0f };
    cameraSpeed = 0.1f;
    cameraRotationSpeed = 0.03f;
    camera.position = cameraPosition;
    camera.target = cameraTarget;
    camera.up = cameraUp;
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    collision = { 0 };
    ray = { 0 };
}

void Camera3DController::Update() {
    if (IsCursorHidden()) UpdateCamera(&camera, CAMERA_FREE);
}

void Camera3DController::HandleInput() {

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && CheckCollisionPointRec(GetMousePosition(), { screenTextureRect.x, screenTextureRect.y, screenTextureRect.width, -screenTextureRect.height}  ))
    {
        if (IsCursorHidden()) EnableCursor();
        else DisableCursor();
    }

    if (IsKeyPressed(KEY_R)) {
        camera.position = cameraPosition;
        camera.target = cameraTarget;
        camera.up = cameraUp;
    }

    if (IsKeyPressed(KEY_TAB)) {
        if (IsCursorHidden()) EnableCursor();
        else DisableCursor();
    }
}

void InitProgram() {
    InitWindow(1280, 720, "Shaurmek");
    SetTargetFPS(60);


}

void CleanupProgram() {
    CloseAudioDevice();
    CloseWindow();
}