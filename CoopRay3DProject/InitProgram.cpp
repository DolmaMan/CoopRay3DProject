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
}

void Camera3DController::Update() {
    UpdateCamera(&camera, CAMERA_FREE);
}

void Camera3DController::HandleInput() {
    if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(Vector3Normalize(Vector3Subtract(camera.target, camera.position)), cameraSpeed));
    if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(Vector3Normalize(Vector3Subtract(camera.target, camera.position)), cameraSpeed));
    if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(Vector3Normalize(Vector3CrossProduct(Vector3Subtract(camera.target, camera.position), camera.up)), cameraSpeed));
    if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(Vector3Normalize(Vector3CrossProduct(Vector3Subtract(camera.target, camera.position), camera.up)), cameraSpeed));

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 mouseDelta = GetMouseDelta();
        camera.target = Vector3Add(camera.position, Vector3RotateByAxisAngle(Vector3Subtract(camera.target, camera.position), camera.up, -mouseDelta.x * cameraRotationSpeed));

        Vector3 right = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(camera.target, camera.position), camera.up));
        camera.target = Vector3Add(camera.position, Vector3RotateByAxisAngle(Vector3Subtract(camera.target, camera.position), right, -mouseDelta.y * cameraRotationSpeed));
    }

    if (IsKeyPressed(KEY_R)) {
        camera.position = cameraPosition;
        camera.target = cameraTarget;
        camera.up = cameraUp;
    }
}

void InitProgram() {
    InitWindow(1280, 720, "Shaurmek");
    SetTargetFPS(60);


}

void CleanupProgram() {
    CloseWindow();
}