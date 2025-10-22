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
            GuiSetFont(ListFonts["Minecraft"]);

            currentFontName = "Minecraft";
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

void UI::DrawAddMenu
    (
        int currentFigureInDropdownBox,
        char* centerXT,
        char* centerYT,
        char* centerZT,
        char* angleXT,
        char* angleYT,
        char* angleZT,
        char* radT,
        char* radElXT,
        char* radElYT,
        char* radElZT,
        char* heightT,
        char* circleStepT
    ) 
{
    static Rectangle menuRect = { 420.0, 160.0, 400, 400 };
    DrawRectanglePro(menuRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menuRect.x + 1, menuRect.y, menuRect.width - 1, menuRect.height - 1, BLACK);

    static bool isWrongFields = false;

    static Rectangle centerRectX = { menuRect.x + 40, menuRect.y + 65, 30, 20};
    static Rectangle centerRectY = { menuRect.x + 110, menuRect.y + 65, 30, 20 };
    static Rectangle centerRectZ = { menuRect.x + 180, menuRect.y + 65, 30, 20 };

    static Rectangle angleRectX = { menuRect.x + 40, menuRect.y + 115, 30, 20 };
    static Rectangle angleRectY = { menuRect.x + 110, menuRect.y + 115, 30, 20 };
    static Rectangle angleRectZ = { menuRect.x + 180, menuRect.y + 115, 30, 20 };

    static Rectangle radRect = { menuRect.x + 40, menuRect.y + 165, 170, 20 };

    static GuiTextBoxControl centerX = GuiTextBoxControl(centerRectX, centerXT);
    static GuiTextBoxControl centerY = GuiTextBoxControl(centerRectY, centerYT);
    static GuiTextBoxControl centerZ = GuiTextBoxControl(centerRectZ, centerZT);
    static GuiTextBoxControl angleX = GuiTextBoxControl(angleRectX, angleXT);
    static GuiTextBoxControl angleY = GuiTextBoxControl(angleRectY, angleYT);
    static GuiTextBoxControl angleZ = GuiTextBoxControl(angleRectZ, angleZT);
    static GuiTextBoxControl rad = GuiTextBoxControl(radRect, radT);

    static Rectangle btnRect = { menuRect.x + 160, menuRect.y + 350, 100, 30 };

    static const char* figStr = "Circle;Ellipse;Helix";
    static int selectedIndex = currentFigureInDropdownBox;
    static bool editMode = false;
    if (GuiDropdownBox({ menuRect.x + 250, menuRect.y + 65, 130, 20 }, figStr, &selectedIndex, editMode)) { editMode = !editMode; }
    if (selectedIndex == 0)
    {
        centerX.DrawControl();
        centerY.DrawControl();
        centerZ.DrawControl();
        angleX.DrawControl();
        angleY.DrawControl();
        angleZ.DrawControl();
        rad.DrawControl();

        GuiLabel({ menuRect.x + 20, menuRect.y + 40, 120, 15 }, "Center XYZ:");

        GuiLabel({ centerRectX.x - 20, centerRectX.y, 20, 20 }, "X:");
        GuiLabel({ centerRectY.x - 20, centerRectX.y, 20, 20 }, "Y:");
        GuiLabel({ centerRectZ.x - 20, centerRectX.y, 20, 20 }, "Z:");

        GuiLabel({ menuRect.x + 20, menuRect.y + 90, 120, 15 }, "Angle XYZ:");

        GuiLabel({ angleRectX.x - 20, angleRectX.y, 20, 20 }, "X:");
        GuiLabel({ angleRectY.x - 20, angleRectX.y, 20, 20 }, "Y:");
        GuiLabel({ angleRectZ.x - 20, angleRectX.y, 20, 20 }, "Z:");

        GuiLabel({ menuRect.x + 20, menuRect.y + 140, 120, 15 }, "Radius:");

        if (GuiButton(btnRect, "OK"))
        {
            try 
            {
                Circle::CircleParams params;
                params.center =
                {
                    strtof(centerX.str, NULL),
                    strtof(centerY.str, NULL),
                    strtof(centerZ.str, NULL)
                };
                params.tiltAngles =
                {
                    strtof(angleX.str, NULL),
                    strtof(angleY.str, NULL),
                    strtof(angleZ.str, NULL),
                };
                float radius = strtof(rad.str, NULL);
                if (radius == 0)
                    throw "";
                else
                    params.radius = radius;
                params.color = GetRandomColor();

                if (addMenuRequested)
                    addMenuRequested = false;
                else
                {
                    editMenuRequested = false;
                    DrawDeleteMenu();
                }

                Circle* circle = new Circle(params);
                vecFigures.emplace_back(circle);

                UpdateFigureList();
            }
            catch(...) 
            {
                isWrongFields = true;
            }
        }
    }
    else if (selectedIndex == 1)
    {
        static Rectangle radElRectX = { menuRect.x + 40, menuRect.y + 165, 30, 20 };
        static Rectangle radElRectY = { menuRect.x + 110, menuRect.y + 165, 30, 20 };
        static Rectangle radElRectZ = { menuRect.x + 180, menuRect.y + 165, 30, 20 };
        static GuiTextBoxControl radElX = GuiTextBoxControl(radElRectX, radElXT);
        static GuiTextBoxControl radElY = GuiTextBoxControl(radElRectY, radElYT);
        static GuiTextBoxControl radElZ = GuiTextBoxControl(radElRectZ, radElZT);

        centerX.DrawControl();
        centerY.DrawControl();
        centerZ.DrawControl();
        angleX.DrawControl();
        angleY.DrawControl();
        angleZ.DrawControl();
        radElX.DrawControl();
        radElY.DrawControl();
        radElZ.DrawControl();

        GuiLabel({ menuRect.x + 20, menuRect.y + 40, 120, 15 }, "Center XYZ:");

        GuiLabel({ centerRectX.x - 20, centerRectX.y, 20, 20 }, "X:");
        GuiLabel({ centerRectY.x - 20, centerRectX.y, 20, 20 }, "Y:");
        GuiLabel({ centerRectZ.x - 20, centerRectX.y, 20, 20 }, "Z:");

        GuiLabel({ menuRect.x + 20, menuRect.y + 90, 120, 15 }, "Angle XYZ:");

        GuiLabel({ angleRectX.x - 20, angleRectX.y, 20, 20 }, "X:");
        GuiLabel({ angleRectY.x - 20, angleRectX.y, 20, 20 }, "Y:");
        GuiLabel({ angleRectZ.x - 20, angleRectX.y, 20, 20 }, "Z:");

        GuiLabel({ menuRect.x + 20, menuRect.y + 140, 120, 15 }, "Radius XYZ:");

        GuiLabel({ radElRectX.x - 20, radElRectX.y, 20, 20 }, "X:");
        GuiLabel({ radElRectY.x - 20, radElRectX.y, 20, 20 }, "Y:");
        GuiLabel({ radElRectZ.x - 20, radElRectX.y, 20, 20 }, "Z:");
        
        if (GuiButton(btnRect, "OK"))
        {
            try {
                Ellipse::EllipseParams params;
                params.center =
                {
                    strtof(centerX.str, NULL),
                    strtof(centerY.str, NULL),
                    strtof(centerZ.str, NULL)
                };
                params.tiltAngles =
                {
                    strtof(angleX.str, NULL),
                    strtof(angleY.str, NULL),
                    strtof(angleZ.str, NULL)
                };
                Vector3 radius =
                {
                    strtof(radElX.str, NULL),
                    strtof(radElY.str, NULL),
                    strtof(radElZ.str, NULL)
                };
                if (
                    radius.x == 0 ||
                    radius.y == 0 ||
                    radius.z == 0
                    )
                    throw "";
                else
                    params.radius = radius;
                params.color = GetRandomColor();

                if (addMenuRequested)
                    addMenuRequested = false;
                else
                {
                    editMenuRequested = false;
                    DrawDeleteMenu();
                }

                Ellipse* ellipse = new Ellipse(params);
                vecFigures.emplace_back(ellipse);

                UpdateFigureList();
            }
            catch (...)
            {
                isWrongFields = true;
            }
        }
    }
    else if (selectedIndex == 2)
    {
        static Rectangle heightRect = { menuRect.x + 40, menuRect.y + 215, 170, 20 };
        static Rectangle stepRect = { menuRect.x + 40, menuRect.y + 265, 170, 20 };

        static GuiTextBoxControl height = GuiTextBoxControl(heightRect, heightT);
        static GuiTextBoxControl step = GuiTextBoxControl(stepRect, circleStepT);

        centerX.DrawControl();
        centerY.DrawControl();
        centerZ.DrawControl();
        angleX.DrawControl();
        angleY.DrawControl();
        angleZ.DrawControl();
        rad.DrawControl();
        height.DrawControl();
        step.DrawControl();

        GuiLabel({ menuRect.x + 20, menuRect.y + 40, 120, 15 }, "Center XYZ:");

        GuiLabel({ centerRectX.x - 20, centerRectX.y, 20, 20 }, "X:");
        GuiLabel({ centerRectY.x - 20, centerRectX.y, 20, 20 }, "Y:");
        GuiLabel({ centerRectZ.x - 20, centerRectX.y, 20, 20 }, "Z:");

        GuiLabel({ menuRect.x + 20, menuRect.y + 90, 120, 15 }, "Angle XYZ:");

        GuiLabel({ angleRectX.x - 20, angleRectX.y, 20, 20 }, "X:");
        GuiLabel({ angleRectY.x - 20, angleRectX.y, 20, 20 }, "Y:");
        GuiLabel({ angleRectZ.x - 20, angleRectX.y, 20, 20 }, "Z:");

        GuiLabel({ menuRect.x + 20, menuRect.y + 140, 80, 15 }, "Radius:");
        GuiLabel({ menuRect.x + 20, menuRect.y + 190, 80, 15 }, "Height:");
        GuiLabel({ menuRect.x + 20, menuRect.y + 240, 80, 15 }, "Step:");
        
        if (GuiButton(btnRect, "OK"))
        {
            try {
                Helix::HelixParams params;
                params.center =
                {
                    strtof(centerX.str, NULL),
                    strtof(centerY.str, NULL),
                    strtof(centerZ.str, NULL)
                };
                params.tiltAngles =
                {
                    strtof(angleX.str, NULL),
                    strtof(angleY.str, NULL),
                    strtof(angleZ.str, NULL),
                };
                float radius = strtof(rad.str, NULL);
                params.radius = (radius==0)?throw"":radius;

                float h = strtof(height.str, NULL);
                params.height = (h == 0)?throw"":h;

                float s = strtof(step.str, NULL);
                params.circleStep = (s == 0)?throw"":s;

                params.color = GetRandomColor();

                if (addMenuRequested)
                    addMenuRequested = false;
                else
                {
                    editMenuRequested = false;
                    DrawDeleteMenu();
                }

                Helix* helix = new Helix(params);
                vecFigures.emplace_back(helix);
                
                UpdateFigureList();
            }
            catch (...)
            {
                isWrongFields = true;
            }
        }
    }

    if (GuiButton({ menuRect.x + 375, menuRect.y, 25, 25 }, "X"))
    {
        addMenuRequested = false;
    }

    if (isWrongFields) {
        DrawTextEx(
            ListFonts[currentFontName],
            "All fields must be filled in\nand only with numbers",
            { btnRect.x - 60, btnRect.y - 40 }, 16, 0, BLACK);
    }
    

}

void UI::DrawEditMenu() 
{
    for (auto fig : vecFigures) {
        std::visit([](auto&& arg) {
            if ((*arg).Properties.isHighlightedInMenu) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Circle*>) {
                    DrawAddMenu
                    (
                        0,
                        (char*)std::to_string((*arg).Properties.center.x).c_str(),
                        (char*)std::to_string((*arg).Properties.center.y).c_str(),
                        (char*)std::to_string((*arg).Properties.center.z).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.x).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.y).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.z).c_str(),
                        (char*)std::to_string((*arg).Properties.radius).c_str(),
                        nullptr,
                        nullptr,
                        nullptr,
                        nullptr,
                        nullptr
                    );
                }
                else if constexpr (std::is_same_v<T, Ellipse*>) {
                    DrawAddMenu
                    (
                        1,
                        (char*)std::to_string((*arg).Properties.center.x).c_str(),
                        (char*)std::to_string((*arg).Properties.center.y).c_str(),
                        (char*)std::to_string((*arg).Properties.center.z).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.x).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.y).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.z).c_str(),
                        nullptr,
                        (char*)std::to_string((*arg).Properties.radius.x).c_str(),
                        (char*)std::to_string((*arg).Properties.radius.y).c_str(),
                        (char*)std::to_string((*arg).Properties.radius.z).c_str(),
                        nullptr,
                        nullptr
                    );
                }
                else if constexpr (std::is_same_v<T, Helix*>) {
                    DrawAddMenu
                    (
                        2,
                        (char*)std::to_string((*arg).Properties.center.x).c_str(),
                        (char*)std::to_string((*arg).Properties.center.y).c_str(),
                        (char*)std::to_string((*arg).Properties.center.z).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.x).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.y).c_str(),
                        (char*)std::to_string((*arg).Properties.tiltAngles.z).c_str(),
                        (char*)std::to_string((*arg).Properties.radius).c_str(),
                        nullptr,
                        nullptr,
                        (char*)std::to_string((*arg).Properties.height).c_str(),
                        (char*)std::to_string((*arg).Properties.circleStep).c_str()

                    );
                }
            }
            }, fig);
    }
}

void UI::DrawDeleteMenu() 
{
    for (auto it = vecFigures.begin(); it != vecFigures.end();) {
        std::visit([&](auto&& arg) {
            if ((*arg).Properties.isHighlightedInMenu) {
                it = vecFigures.erase(it);
            }
            else {
                it++;
            }
            }, (*it));
    }
    /*static Rectangle menuRect = { 420.0, 160.0, 400, 400 };
    DrawRectanglePro(menuRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menuRect.x + 1, menuRect.y, menuRect.width - 1, menuRect.height - 1, BLACK);*/
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
    bool fl = false;
    for (auto& fig : vecFigures) {
        std::visit([&](auto&& arg)
            { if ((*arg).Properties.isHighlightedInMenu) fl=true; },
            fig
        );
    }
    return fl;
}

UI::GuiTextBoxControl::GuiTextBoxControl(Rectangle r, char* s)
{
    rect = r;
    editMode = false;
    str = s;
}

void UI::GuiTextBoxControl::DrawControl()
{
    if (GuiTextBox(rect, str, 100, editMode)) {
        editMode = !editMode;
    }
}
