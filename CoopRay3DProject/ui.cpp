#include "ui.h"
bool addMenuRequested = false,
     editMenuRequested = false,
     deleteMenuRequested = false;

void UI::DrawMainMenu() {
    if (
        !addMenuRequested &&
        !editMenuRequested &&
        !deleteMenuRequested
        ) 
    {
        cameraController.HandleInput();
        cameraController.Update();
    }
    BeginTextureMode(screenTexture);
    ClearBackground(RAYWHITE);
    Drawer::DrawScene(cameraController);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTextureRec(screenTexture.texture, screenTextureRect, { 0.0,50.0 }, RAYWHITE); //Ñåòêà

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 255);

    DrawText("WASD: Move camera", 10, 60, 16, DARKGRAY);
    DrawText("Right mouse button or TAB: Free camera mode", 10, 80, 16, DARKGRAY);
    DrawText("R: Reset camera", 10, 100, 16, DARKGRAY);
    DrawText("ESC: Exit", 10, 120, 16, DARKGRAY);

    if (GuiButton({ 20, 10, 120, 30 }, "Add Shape")) { addMenuRequested = true; };
    if (GuiButton({ 150, 10, 120, 30 }, "Delete Shape")) 
    {
        if(isElementHighlighted())
            deleteMenuRequested = true; 
    };
    if (GuiButton({ 280, 10, 120, 30 }, "Edit Shape")) 
    { 
        if (isElementHighlighted())
            editMenuRequested = true; 
    };

    if (addMenuRequested) { DrawAddMenu(); }
    else if (editMenuRequested) { DrawEditMenu(); }
    else if(deleteMenuRequested) { DrawDeleteMenu(); }
    
    DrawRectangleLinesEx(bigRect, 1, DARKGRAY);
    DrawRectangleLinesEx(listFiguresRect, 1, DARKGRAY);

    DrawText("SHAPES LIST", screenWidth - 290, 65, 20, BLACK);

    DrawText("ID", screenWidth - 290, 110, 16, DARKGRAY);
    DrawText("Type", screenWidth - 250, 110, 16, DARKGRAY);
    DrawText("Position", screenWidth - 190, 110, 16, DARKGRAY);
    
    DrawLine(screenWidth - 300 + 1, 50, screenWidth - 300, 135, DARKGRAY);
    DrawLine(screenWidth - 300 + 1, 95, screenWidth, 95, DARKGRAY);
    

    DrawFigureList();
    DrawFPS(screenWidth - 80, screenHeight - 25);

    EndDrawing();

    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) {
        //PlaySound(ListSounds["General_Quitgame.wav"]);
        //currentEnum = MenusEnum::ExitMenu;
        exitWindow = true;  //Вернуть в конце
    }
}

void UI::DrawExitMenu() {
    BeginDrawing();
    ClearBackground(RAYWHITE);


    // ÑÄÅËÀÒÜ ÌÅÍÞ ÂÛÕÎÄÀ
    Color BgCol = { 0, 0, 0, 200 };
    DrawRectangle(0, 200, screenWidth, 200, BgCol);
    DrawText("Are you sure you want to exit program? [Y/N]", 40, 270, 30, WHITE);

    EndDrawing();

    if (IsKeyPressed(KEY_Y) || WindowShouldClose()) exitWindow = true;
    else if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_N)) currentEnum = MenusEnum::MainMenu;

}

void UI::DrawAddMenu() 
{
    static Rectangle menuRect = { 420.0, 160.0, 400, 400 };
    DrawRectanglePro(menuRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menuRect.x + 1, menuRect.y, menuRect.width - 1, menuRect.height - 1, BLACK);

    static Rectangle rect = { menuRect.x, menuRect.y, 100, 10 };
    static char* str = new char[100] {'\0'};
    if (GuiTextBox(rect, str, 100, true)) {

    };
    static const char* str2 = "Circle;Ellipse;Helix";
    static int selectedIndex = 0;
    static bool editMode = false;
    static Rectangle topRect = { menuRect.x, menuRect.y + 25, 400, 25 };
    if (GuiDropdownBox({menuRect.x + 100, menuRect.y + 100, 100, 20 }, str2, &selectedIndex, editMode)) {
        editMode = !editMode;
    }

    static float centerX = 10;
    static float centerY = 0;
    static float centerZ = 0;
    static float radius = 10;
    static float rotationAxisX = 0;
    static float rotationAxisY = 0;
    static float rotationAxisZ = 0;
    static float rotationAngle = 0;

    if (GuiButton({ menuRect.x + 375, menuRect.y, 25, 25 }, "X"))
    {
        addMenuRequested = false;
        std::unordered_map<std::string, float> props;
        props["centerX"] = centerX;
        props["centerY"] = centerY;
        props["centerZ"] = centerZ;
        props["radius"] = radius;
        props["rotationAxisX"] = rotationAxisX;
        props["rotationAxisY"] = rotationAxisY;
        props["rotationAxisZ"] = rotationAxisZ;
        props["rotationAngle"] = rotationAngle;
        
        Figure* fig = new Figure("Circle", props, GetRandomColor());
        UpdateFigureList();
    }
    

}

void UI::DrawEditMenu() 
{
    static Rectangle menuRect = { 420.0, 160.0, 400, 400 };
    DrawRectanglePro(menuRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menuRect.x + 1, menuRect.y, menuRect.width - 1, menuRect.height - 1, BLACK);
}

void UI::DrawDeleteMenu() 
{
    static Rectangle menuRect = { 420.0, 160.0, 400, 400 };
    DrawRectanglePro(menuRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menuRect.x + 1, menuRect.y, menuRect.width - 1, menuRect.height - 1, BLACK);
}

void UI::UpdateFigureList()
{
    Rectangle figureInMenuRect{ listFiguresRect.x, listFiguresRect.y, listFiguresRect.width, 30 };
    for (auto& pair : mapFigures) {
        pair.second->figureRect = figureInMenuRect;
        pair.second->isHighlighted = false;
        figureInMenuRect.y += 29;
    }
}

void UI::UpdateFigureList(std::multimap<std::string, Figure*>::iterator excludingIter)
{
    Rectangle figureInMenuRect{ listFiguresRect.x, listFiguresRect.y, listFiguresRect.width, 30 };
    for (auto it = mapFigures.begin(); it != mapFigures.end(); it++) {
        (*it).second->figureRect = figureInMenuRect;
        if(it != excludingIter)
            (*it).second->isHighlighted = false;
        figureInMenuRect.y += 29;
    }
}

void UI::DrawFigureList()
{
    if (CheckCollisionPointRec(GetMousePosition(), listFiguresRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (auto it = mapFigures.begin(); it != mapFigures.end();it++) {
            if (CheckCollisionPointRec(GetMousePosition(), (*it).second->figureRect)) {
                if ((*it).second->isHighlighted) {
                    UpdateFigureList();
                }
                else {
                    (*it).second->isHighlighted = true;
                    UpdateFigureList(it);
                    DrawRectangleLinesEx((*it).second->figureRect, 2, BLUE);
                }
            }
            else {
                DrawRectangleLinesEx((*it).second->figureRect, 1, BLACK);
            }

            DrawText(
                std::to_string((int)(*(*it).second).Properties["id"]).c_str(),
                (*it).second->figureRect.x + 10,
                (*it).second->figureRect.y + 10,
                16, BLACK
            );
            DrawText(
                (*(*it).second).figureName.c_str(),
                (*it).second->figureRect.x + 50,
                (*it).second->figureRect.y + 10,
                16, BLACK
            );
        }
    }
    else {
        for (auto& pair : mapFigures) {
            if(pair.second->isHighlighted)
                DrawRectangleLinesEx(pair.second->figureRect, 2, BLUE);
            else
                DrawRectangleLinesEx(pair.second->figureRect, 1, BLACK);

            DrawText(
                std::to_string((int)(*pair.second).Properties["id"]).c_str(),
                pair.second->figureRect.x + 10,
                pair.second->figureRect.y + 10,
                16, BLACK
            );
            DrawText(
                (*pair.second).figureName.c_str(),
                pair.second->figureRect.x + 50,
                pair.second->figureRect.y + 10,
                16, BLACK
            );
        }
    }
}

bool UI::isElementHighlighted()
{
    for (auto fig : mapFigures)
        if (fig.second->isHighlighted)
            return true;
    return false;
}
