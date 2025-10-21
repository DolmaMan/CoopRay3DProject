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

    DrawTextEx(ListFonts[currentFontName], "WASD: Move camera", { 10, 60 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "Right mouse button or TAB: Free camera mode", { 10, 80 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "R: Reset camera", { 10, 100 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "ESC: Exit", { 10, 120 }, 16, 1, DARKGRAY);
    
    if (GuiButton({ 20, 10, 120, 30 }, "Add Shape")) { addMenuRequested = true; }
    if (GuiButton({ 150, 10, 120, 30 }, "Delete Shape")) 
    {
        if(isElementHighlighted())
            deleteMenuRequested = true; 
    }
    if (GuiButton({ 280, 10, 120, 30 }, "Edit Shape")) 
    { 
        if (isElementHighlighted())
            editMenuRequested = true; 
    }

    if (GuiButton({ (float)screenWidth - 140, 10, 120, 30 }, "Change Font"))
    {
        if (currentFontName == "Consolas") {
            GuiSetFont(ListFonts["Braille"]);

            currentFontName = "Braille";
        }
        else {
            GuiSetFont(ListFonts["Consolas"]);
            currentFontName = "Consolas";
        }
    }

    if (addMenuRequested) { DrawAddMenu(); }
    else if (editMenuRequested) { DrawEditMenu(); }
    else if(deleteMenuRequested) { DrawDeleteMenu(); }
    
    DrawRectangleLinesEx(bigRect, 1, DARKGRAY);
    DrawRectangleLinesEx(listFiguresRect, 1, DARKGRAY);

    DrawTextEx(ListFonts[currentFontName], "SHAPES LIST", { (float)screenWidth - 290, 65 }, 20, 1, BLACK);

    DrawTextEx(ListFonts[currentFontName], "ID", { (float)screenWidth - 290, 110 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "Type", { (float)screenWidth - 250, 110 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "Position", { (float)screenWidth - 190, 110 }, 16, 1, DARKGRAY);
    
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
    DrawTextEx(ListFonts[currentFontName], "Are you sure you want to exit program? [Y/N]", { 40, 270 }, 30, 1, WHITE);

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

    
    static float centerX = 5;
    static float centerY = 0;
    static float centerZ = 0;

    static float radiusC = 2;

    static float circleStepHelix = 2;
    static float heightHelix = 10;

    //Угол наклона принимать в градусах
    static float tiltAngleX = 90;
    static float tiltAngleY = 0;
    static float tiltAngleZ = 0;

    static float radiusElX = 8;
    static float radiusElY = 2;
    static float radiusElZ = 4;

    if (GuiButton({ menuRect.x + 375, menuRect.y, 25, 25 }, "X"))
    {
        addMenuRequested = false;

        //Пример создания диска
        /*Circle::CircleParams params;
        params.center = { centerX, centerY, centerZ };
        params.tiltAngles = { tiltAngleX , tiltAngleY , tiltAngleZ };
        params.color = GetRandomColor();
        params.radius = radiusC;

        Circle* circle = new Circle(params);
        vecFigures.emplace_back(circle);*/

        //Пример создания эллипса
        /*Ellipse::EllipseParams params;
        params.center = { centerX, centerY, centerZ };
        params.tiltAngles = { tiltAngleX , tiltAngleY , tiltAngleZ };
        params.color = GetRandomColor();
        params.radius = { radiusElX, radiusElY, radiusElZ };

        Ellipse* ellipse = new Ellipse(params);
        vecFigures.emplace_back(ellipse);*/

        //Пример создания хеликса
        Helix::HelixParams params;
        params.center = { centerX, centerY, centerZ };
        params.tiltAngles = { tiltAngleX , tiltAngleY , tiltAngleZ };
        params.color = GetRandomColor();
        params.radius = radiusC;
        params.circleStep = circleStepHelix;
        params.height = heightHelix;

        Helix* helix = new Helix(params);
        vecFigures.emplace_back(helix);

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
    for (auto& fig : vecFigures) {
        std::visit([&figureInMenuRect](auto&& arg) 
            {
                (*arg).Properties.figureInMenuRect = figureInMenuRect;
                (*arg).Properties.isHighlightedInMenu = false;
            },
            fig
        );
        figureInMenuRect.y += 29;
    }
}

void UI::UpdateFigureList(Rectangle excludingRect)
{
    Rectangle figureInMenuRect{ listFiguresRect.x, listFiguresRect.y, listFiguresRect.width, 30 };
    for (auto& fig : vecFigures) {
        if (excludingRect.y != figureInMenuRect.y) {
            std::visit([&figureInMenuRect](auto&& arg)
                {
                    (*arg).Properties.figureInMenuRect = figureInMenuRect;
                    (*arg).Properties.isHighlightedInMenu = false;
                },
                fig
            );
        }
        figureInMenuRect.y += 29;
    }
}

void UI::DrawFigureList()
{
    int index = 1;
    if (CheckCollisionPointRec(GetMousePosition(), listFiguresRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (auto& fig : vecFigures) {
            std::visit([&index](auto&& arg)
                {
                    if (CheckCollisionPointRec(GetMousePosition(), (*arg).Properties.figureInMenuRect)) {
                        if ((*arg).Properties.isHighlightedInMenu) {
                            UpdateFigureList();
                        }
                        else {
                            (*arg).Properties.isHighlightedInMenu = true;
                            UpdateFigureList((*arg).Properties.figureInMenuRect);
                            DrawRectangleLinesEx((*arg).Properties.figureInMenuRect, 2, BLUE);
                        }
                    }
                    else {
                        DrawRectangleLinesEx((*arg).Properties.figureInMenuRect, 1, BLACK);
                    }

                    DrawTextEx(
                        ListFonts[currentFontName],
                        std::to_string(index++).c_str(),
                        {
                            (*arg).Properties.figureInMenuRect.x + 10,
                            (*arg).Properties.figureInMenuRect.y + 10
                        },
                        16, 1,
                        BLACK
                    );
                    DrawTextEx(
                        ListFonts[currentFontName],
                        (*arg).getClassName().c_str(),
                        {
                            (*arg).Properties.figureInMenuRect.x + 50,
                            (*arg).Properties.figureInMenuRect.y + 10
                        }, 
                        16, 1,
                        BLACK
                    );
                },
                fig
            );
        }
    }
    else {
        for (auto& fig : vecFigures) {
            std::visit([&index](auto&& arg)
                {
                    if ((*arg).Properties.isHighlightedInMenu)
                        DrawRectangleLinesEx((*arg).Properties.figureInMenuRect, 2, BLUE);
                    else
                        DrawRectangleLinesEx((*arg).Properties.figureInMenuRect, 1, BLACK);

                    DrawTextEx(
                        ListFonts[currentFontName],
                        std::to_string(index++).c_str(),
                        {
                            (*arg).Properties.figureInMenuRect.x + 10,
                            (*arg).Properties.figureInMenuRect.y + 10
                        },
                        16, 1,
                        BLACK
                    );
                    DrawTextEx(
                        ListFonts[currentFontName],
                        (*arg).getClassName().c_str(),
                        {
                            (*arg).Properties.figureInMenuRect.x + 50,
                            (*arg).Properties.figureInMenuRect.y + 10
                        },
                        16, 1,
                        BLACK
                    );
                },
                fig
            );
        }
    }
}

bool UI::isElementHighlighted()
{
    for (auto fig : vecFigures) {
        std::visit([](auto arg)
            { if ((*arg).Properties.isHighlightedInMenu) return true; },
            fig
        );
    }
    return false;
}
