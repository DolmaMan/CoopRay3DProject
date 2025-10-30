#include "ui.h"

namespace UI {
    bool addMenuRequested = false,
        editMenuRequested = false,
        deleteMenuRequested = false;
    bool showMessageBox;
    bool showExitMenu;
}

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

    DrawTextureRec(screenTexture.texture, screenTextureRect, { 0.0,50.0 }, RAYWHITE);

    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, 255);

    DrawTextEx(ListFonts[currentFontName], "WASD: Move camera", { 10, 60 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "Right mouse button or TAB: Free camera mode", { 10, 80 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "R: Reset camera", { 10, 100 }, 16, 1, DARKGRAY);
    DrawTextEx(ListFonts[currentFontName], "ESC: Exit", { 10, 120 }, 16, 1, DARKGRAY);
    
    if (GuiButton({ 20, 10, 120, 30 }, "Add Shape") &&
        !editMenuRequested && !deleteMenuRequested) 
    {
        addMenuRequested = true;
        ResetUiControls();
        UpdateUiControls();
    }
    if (GuiButton({ 150, 10, 120, 30 }, "Delete Shape") &&
        !editMenuRequested && !addMenuRequested)
    {
        if (isElementHighlighted()) {
            deleteMenuRequested = true;
            showMessageBox = true;
        }
        
    }
    if (GuiButton({ 280, 10, 120, 30 }, "Edit Shape") &&
        !addMenuRequested && !deleteMenuRequested)
    { 
        if (isElementHighlighted()) {
            editMenuRequested = true;
            ResetUiControls();
            UpdateUiControls();
        }
    }

    if (GuiButton({ (float)screenWidth - 140, 10, 120, 30 }, "Change Font")
        && !editMenuRequested && !deleteMenuRequested && ! addMenuRequested)
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

    DrawExitMenu();
    EndDrawing();

    if (!showExitMenu && (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))) {
        PlaySound(ListSounds["General_Quitgame.wav"]);
        showExitMenu = true;
    }
}

void UI::DrawExitMenu() {
    if (showExitMenu)
    {
        int MBresult = GuiMessageBox({ 470, 270, 320, 90 },
            "#191#Exit", "Are you sure you want to exit?", "Yes;No");

        if (MBresult == 1)
        {
            exitWindow = true;
        }
        else if (MBresult == 2 || MBresult == 0)
        {
            showExitMenu = false;
        }
    }
}

void UI::LoadUiControls() {
    menusRect = { 420.0, 160.0, 400, 400 };

    Rectangle centerRectX  = { menusRect.x + 40,  menusRect.y +  50, 90, 20 };
    Rectangle centerRectY  = { menusRect.x + 170, menusRect.y +  50, 90, 20 };
    Rectangle centerRectZ  = { menusRect.x + 300, menusRect.y +  50, 90, 20 };
    Rectangle angleRectX   = { menusRect.x + 40,  menusRect.y + 110, 90, 20 };
    Rectangle angleRectY   = { menusRect.x + 170, menusRect.y + 110, 90, 20 };
    Rectangle angleRectZ   = { menusRect.x + 300, menusRect.y + 110, 90, 20 };
    Rectangle radRect      = { menusRect.x + 40,  menusRect.y + 170, 90, 20 };
    Rectangle heightRect   = { menusRect.x + 170, menusRect.y + 170, 90, 20 };
    Rectangle stepRect     = { menusRect.x + 300, menusRect.y + 170, 90, 20 };
    Rectangle radElRectX   = { menusRect.x + 40,  menusRect.y + 170, 90, 20 };
    Rectangle radElRectY   = { menusRect.x + 170, menusRect.y + 170, 90, 20 };
    Rectangle radElRectZ   = { menusRect.x + 300, menusRect.y + 170, 90, 20 };

    mapUiControls["centerX"] = GuiTextBoxControl(centerRectX);
    mapUiControls["centerY"] = GuiTextBoxControl(centerRectY);
    mapUiControls["centerZ"] = GuiTextBoxControl(centerRectZ);

    mapUiControls["angleX"] = GuiTextBoxControl(angleRectX);
    mapUiControls["angleY"] = GuiTextBoxControl(angleRectY);
    mapUiControls["angleZ"] = GuiTextBoxControl(angleRectZ);

    mapUiControls["rad"] = GuiTextBoxControl(radRect);

    mapUiControls["radElX"] = GuiTextBoxControl(radElRectX);
    mapUiControls["radElY"] = GuiTextBoxControl(radElRectY);
    mapUiControls["radElZ"] = GuiTextBoxControl(radElRectZ);

    mapUiControls["height"] = GuiTextBoxControl(heightRect);
    mapUiControls["step"] = GuiTextBoxControl(stepRect);
}

void UI::ResetUiControls()
{
    for (auto& pair : mapUiControls) {
        strncpy(pair.second.str, "0", 99);
        pair.second.str[99] = '\0';
        strncpy(pair.second.secStr, "0", 99);
        pair.second.secStr[99] = '\0';
    }
    for (auto& fig : vecFigures) {
        std::visit([&](auto&& arg) {
            if ((*arg).Properties.isHighlightedInMenu) {
                using T = std::decay_t<decltype(arg)>;
                char buffer[100];
                if constexpr (std::is_same_v<T, Circle*>) {
                    snprintf(buffer, 99, "%g", (*arg).Properties.center.x);
                    mapUiControls["centerX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.center.y);
                    mapUiControls["centerY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.center.z);
                    mapUiControls["centerZ"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.x);
                    mapUiControls["angleX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.y);
                    mapUiControls["angleY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.z);
                    mapUiControls["angleZ"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.radius);
                    mapUiControls["rad"].SetSecStr(buffer);
                }
                else if constexpr (std::is_same_v<T, Ellipse*>) {
                    snprintf(buffer, 99, "%g", (*arg).Properties.center.x);
                    mapUiControls["centerX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.center.y);
                    mapUiControls["centerY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.center.z);
                    mapUiControls["centerZ"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.x);
                    mapUiControls["angleX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.y);
                    mapUiControls["angleY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.z);
                    mapUiControls["angleZ"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.radius.x);
                    mapUiControls["radElX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.radius.y);
                    mapUiControls["radElY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.radius.z);
                    mapUiControls["radElZ"].SetSecStr(buffer);
                }
                else if constexpr (std::is_same_v<T, Helix*>) {
                    snprintf(buffer, 99, "%g", (*arg).Properties.center.x);
                    mapUiControls["centerX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.center.y);
                    mapUiControls["centerY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.center.z);
                    mapUiControls["centerZ"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.x);
                    mapUiControls["angleX"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.y);
                    mapUiControls["angleY"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.tiltAngles.z);
                    mapUiControls["angleZ"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.radius);
                    mapUiControls["rad"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.height);
                    mapUiControls["height"].SetSecStr(buffer);

                    snprintf(buffer, 99, "%g", (*arg).Properties.circleStep);
                    mapUiControls["step"].SetSecStr(buffer);
                }
            }
            }, fig);
    }
}

void UI::UpdateUiControls()
{
    for(auto& pair : mapUiControls)
    {
        strncpy(pair.second.str, pair.second.secStr, 99);
        pair.second.str[99] = '\0';
    }
}

void UI::DrawAddMenu
    (
        bool isEdit,
        int currentFigureInDropdownBox,
        Color oldColor 
    ) 
{
    DrawRectanglePro(menusRect, { 0, 0 }, 0, WHITE);
    DrawRectangleLines(menusRect.x + 1, menusRect.y, menusRect.width - 1, menusRect.height - 1, BLACK);

    static bool isWrongFields = false;

    static Rectangle btnRect = { menusRect.x + 160, menusRect.y + 350, 100, 30 };

    static const char* figStr = "Circle;Ellipse;Helix";
    static int selectedIndex = currentFigureInDropdownBox;
    static bool editMode = false;
    if (GuiDropdownBox({ menusRect.x + 145, menusRect.y + 210, 130, 20 }, figStr, &selectedIndex, editMode)) { editMode = !editMode; }
    if (selectedIndex == 0)
    {
        mapUiControls["centerX"].DrawControl();
        mapUiControls["centerY"].DrawControl();
        mapUiControls["centerZ"].DrawControl();
        mapUiControls["angleX"].DrawControl();
        mapUiControls["angleY"].DrawControl();
        mapUiControls["angleZ"].DrawControl();
        mapUiControls["rad"].DrawControl();

        GuiLabel({ menusRect.x + 20, menusRect.y + 30, 120, 15 }, "Center XYZ:");

        GuiLabel({ mapUiControls["centerX"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["centerY"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["centerZ"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "Z:");

        GuiLabel({ menusRect.x + 20, menusRect.y + 90, 120, 15 }, "Angle XYZ:");

        GuiLabel({ mapUiControls["angleX"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["angleY"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["angleZ"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "Z:");

        GuiLabel({ menusRect.x + 20, menusRect.y + 150, 120, 15 }, "Radius:");

        if (GuiButton(btnRect, "OK"))
        {
            try{
                Circle::CircleParams params;
                params.center =
                {
                    strtof(mapUiControls["centerX"].str, NULL),
                    strtof(mapUiControls["centerY"].str, NULL),
                    strtof(mapUiControls["centerZ"].str, NULL)
                };
                params.tiltAngles =
                {
                    strtof(mapUiControls["angleX"].str, NULL),
                    strtof(mapUiControls["angleY"].str, NULL),
                    strtof(mapUiControls["angleZ"].str, NULL),
                };
                float radius = strtof(mapUiControls["rad"].str, NULL);
                if (radius == 0)
                    throw "";
                else
                    params.radius = radius;

                params.color = (isEdit) ? oldColor : GetRandomColor();

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
            catch (...)
            {
                isWrongFields = true;
            }
        }
    }
    else if (selectedIndex == 1)
    {
        mapUiControls["centerX"].DrawControl();
        mapUiControls["centerY"].DrawControl();
        mapUiControls["centerZ"].DrawControl();
        mapUiControls["angleX"].DrawControl();
        mapUiControls["angleY"].DrawControl();
        mapUiControls["angleZ"].DrawControl();
        mapUiControls["radElX"].DrawControl();
        mapUiControls["radElY"].DrawControl();
        mapUiControls["radElZ"].DrawControl();

        GuiLabel({ menusRect.x + 20, menusRect.y + 30, 120, 15 }, "Center XYZ:");

        GuiLabel({ mapUiControls["centerX"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["centerY"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["centerZ"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "Z:");

        GuiLabel({ menusRect.x + 20, menusRect.y + 90, 120, 15 }, "Angle XYZ:");

        GuiLabel({ mapUiControls["angleX"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["angleY"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["angleZ"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "Z:");

        GuiLabel({ menusRect.x + 20, menusRect.y + 150, 120, 15 }, "Radius XYZ:");

        GuiLabel({ mapUiControls["radElX"].rect.x - 20, mapUiControls["radElX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["radElY"].rect.x - 20, mapUiControls["radElX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["radElZ"].rect.x - 20, mapUiControls["radElX"].rect.y, 20, 20 }, "Z:");
        
        if (GuiButton(btnRect, "OK"))
        {
            try {
                Ellipse::EllipseParams params;
                params.center =
                {
                    strtof(mapUiControls["centerX"].str, NULL),
                    strtof(mapUiControls["centerY"].str, NULL),
                    strtof(mapUiControls["centerZ"].str, NULL)
                };
                params.tiltAngles =
                {
                    strtof(mapUiControls["angleX"].str, NULL),
                    strtof(mapUiControls["angleY"].str, NULL),
                    strtof(mapUiControls["angleZ"].str, NULL)
                };
                Vector3 radius =
                {
                    strtof(mapUiControls["radElX"].str, NULL),
                    strtof(mapUiControls["radElY"].str, NULL),
                    strtof(mapUiControls["radElZ"].str, NULL)
                };
                if (
                    radius.x == 0 ||
                    radius.y == 0 ||
                    radius.z == 0
                    )
                    throw "";
                else
                    params.radius = radius;
                
                params.color = (isEdit) ? oldColor : GetRandomColor();

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
        mapUiControls["centerX"].DrawControl();
        mapUiControls["centerY"].DrawControl();
        mapUiControls["centerZ"].DrawControl();
        mapUiControls["angleX"].DrawControl();
        mapUiControls["angleY"].DrawControl();
        mapUiControls["angleZ"].DrawControl();
        mapUiControls["rad"].DrawControl();
        mapUiControls["height"].DrawControl();
        mapUiControls["step"].DrawControl();

        GuiLabel({ menusRect.x + 20, menusRect.y + 30, 120, 15 }, "Center XYZ:");

        GuiLabel({ mapUiControls["centerX"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["centerY"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["centerZ"].rect.x - 20, mapUiControls["centerX"].rect.y, 20, 20 }, "Z:");

        GuiLabel({ menusRect.x + 20, menusRect.y + 90, 120, 15 }, "Angle XYZ:");

        GuiLabel({ mapUiControls["angleX"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "X:");
        GuiLabel({ mapUiControls["angleY"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "Y:");
        GuiLabel({ mapUiControls["angleZ"].rect.x - 20, mapUiControls["angleX"].rect.y, 20, 20 }, "Z:");

        GuiLabel({ menusRect.x + 20, menusRect.y + 150, 120, 15 }, "Radius:");
        GuiLabel({ menusRect.x + 150, menusRect.y + 150, 80, 15 }, "Height:");
        GuiLabel({ menusRect.x + 280, menusRect.y + 150, 80, 15 }, "Step:");
        
        if (GuiButton(btnRect, "OK"))
        {
            try {
                Helix::HelixParams params;
                params.center =
                {
                    strtof(mapUiControls["centerX"].str, NULL),
                    strtof(mapUiControls["centerY"].str, NULL),
                    strtof(mapUiControls["centerZ"].str, NULL)
                };
                params.tiltAngles =
                {
                    strtof(mapUiControls["angleX"].str, NULL),
                    strtof(mapUiControls["angleY"].str, NULL),
                    strtof(mapUiControls["angleZ"].str, NULL),
                };
                float radius = strtof(mapUiControls["rad"].str, NULL);
                params.radius = (radius==0)?throw"":radius;

                float h = strtof(mapUiControls["height"].str, NULL);
                params.height = (h == 0)?throw"":h;

                float s = strtof(mapUiControls["step"].str, NULL);
                params.circleStep = (s == 0)?throw"":s;

                params.color = (isEdit) ? oldColor : GetRandomColor();

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

    if (GuiButton({ menusRect.x + 375, menusRect.y, 25, 25 }, "X"))
    {
        editMenuRequested = false;
        addMenuRequested = false;
    }

    if (isWrongFields) {
        DrawTextEx(
            ListFonts[currentFontName],
            "All fields must be filled in\n   and only with numbers",
            { btnRect.x - 60, btnRect.y - 40 }, 16, 0, BLACK);
    }
    

}

void UI::DrawEditMenu() 
{
    for (auto& fig : vecFigures) {
        std::visit([](auto&& arg) {
            if ((*arg).Properties.isHighlightedInMenu) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, Circle*>) {
                    DrawAddMenu
                    (
                        true,
                        0,
                        (*arg).Properties.color
                    );
                }
                else if constexpr (std::is_same_v<T, Ellipse*>) {
                    DrawAddMenu
                    (
                        true,
                        1,
                        (*arg).Properties.color
                    );
                }
                else if constexpr (std::is_same_v<T, Helix*>) {
                    DrawAddMenu
                    (
                        true,
                        2,
                        (*arg).Properties.color
                    );
                }
            }
            }, fig);
    }
}

void UI::DrawDeleteMenu()
{
    if (showMessageBox) {
        int delMBres = GuiMessageBox({ 470, 270, 320, 90 },
            "#191#Delete", "Delete figure?", "Yes;No");
        if (delMBres == 1)
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
            showMessageBox = false;
            deleteMenuRequested = false;
            UpdateFigureList();
        }
  
        else if (delMBres == 2 || delMBres == 0)
        {
            showMessageBox = false;
            deleteMenuRequested = false;
            UpdateFigureList();
        }
    }
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

UI::GuiTextBoxControl::GuiTextBoxControl(Rectangle r, const char* s)
{
    rect = r;
    editMode = false;
    strncpy(str, s, 99);
    str[0] = '0';
    str[99] = '\0';
    strncpy(secStr, s, 99);
    secStr[99] = '\0';
    secStr[0] = '0';
}

void UI::GuiTextBoxControl::DrawControl()
{
    if (GuiTextBox(rect, str, 100, editMode)) {
        editMode = !editMode;
    }
}

void UI::GuiTextBoxControl::SetSecStr(const char* s) 
{
    strncpy(secStr, s, 99);
    secStr[99] = '\0';
}
