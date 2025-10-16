#include "drawer.h"

void Drawer::DrawScene(const Camera3DController& cameraController) {
    BeginMode3D(cameraController.camera);

    DrawGrid(20, 1.0f);

    DrawLine3D({ 0, 0, 0 }, { 5, 0, 0 }, RED);    
    DrawLine3D({ 0, 0, 0 }, { 0, 5, 0 }, GREEN);  
    DrawLine3D({ 0, 0, 0 }, { 0, 0, 5 }, BLUE);   

    for (auto pair : mapFigures) 
    {
        if (pair.first == "Circle") 
        {
            Vector3 center = 
            { 
                (*pair.second).Properties["centerX"],
                (*pair.second).Properties["centerY"],
                (*pair.second).Properties["centerZ"]
            };
            Vector3 rotationAxis = 
            {
                (*pair.second).Properties["rotationAxisX"],
                (*pair.second).Properties["rotationAxisY"],
                (*pair.second).Properties["rotationAxisZ"]
            };
            DrawCircle3D(
                center,
                (*pair.second).Properties["radius"],
                rotationAxis,
                (*pair.second).Properties["rotationAngle"],
                (*pair.second).color
            );
        }
        else if (pair.first == "Ellipse") {

        }
        else if (pair.first == "Helix") {

        }
    }
    

    /*DrawCube({0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, MAROON);

    DrawSphere({ 3.0f, 0.0f, 0.0f }, 1.0f, GREEN);
    DrawSphereWires({ 3.0f, 0.0f, 0.0f }, 1.0f, 16, 16, DARKGREEN);

    DrawCube({ 0.0f, 3.0f, 0.0f }, 1.0f, 1.0f, 1.0f, PURPLE);
    DrawSphere({ 3.0f, 3.0f, 0.0f }, 0.8f, ORANGE);*/

    EndMode3D();
}
