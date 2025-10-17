#pragma once
#include <raylib.h>
#include "raygui.h"
#include"config.h"
#include"InitProgram.h"
#include"Drawer.h"

namespace UI {
    void DrawMainMenu();
    void DrawExitMenu();
    void DrawAddMenu();
    void DrawEditMenu();
    void DrawDeleteMenu();
    
    void UpdateFigureList();
    void UpdateFigureList(Rectangle excludingRect);
    void DrawFigureList();

    bool isElementHighlighted();
}

