#pragma once
#include<raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION



struct Camera3DController {
    Camera3D camera;
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    Vector3 cameraUp;
    float cameraSpeed;
    float cameraRotationSpeed;

    Camera3DController();
    void Update();
    void HandleInput();
};


void InitProgram();
void CleanupProgram();


class InitProgram
{

};

