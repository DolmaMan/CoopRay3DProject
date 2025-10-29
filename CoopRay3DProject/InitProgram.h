#pragma once
#include<raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include"config.h"


struct Camera3DController {
    Camera3D camera;
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    Vector3 cameraUp;
    float cameraSpeed;
    float cameraRotationSpeed;
    RayCollision collision;
    Ray ray;

    Camera3DController();
    void Update();
    void HandleInput();
};


void InitProgram();
void CleanupProgram();