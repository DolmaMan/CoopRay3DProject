#pragma once
#include <raylib.h>
#include<iostream>
#include "raygui.h"
#include"config.h"
#include"InitProgram.h"
#include"Drawer.h"

namespace UI {
    struct GuiTextBoxControl {
        char str[100];
        char secStr[100];
        Rectangle rect;
        bool editMode;

        GuiTextBoxControl(Rectangle r, const char* s = "0");
        GuiTextBoxControl() : GuiTextBoxControl({0,0,0,0}){}

        void DrawControl();
        void SetSecStr(const char*);
    };

    static std::unordered_map<std::string, GuiTextBoxControl> mapUiControls;
    static Rectangle menusRect;

    void LoadUiControls();
    void ResetUiControls();
    void UpdateUiControls();

    void DrawMainMenu();
    void DrawExitMenu();
    void DrawAddMenu
    (
        bool isEdit                       = false,
        int currentFigureInDropdownBox    = 0,
        Color color                       = BLACK
    );

    void DrawEditMenu();
    void DrawDeleteMenu();
    
    void UpdateFigureList();
    void UpdateFigureList(Rectangle excludingRect);
    void DrawFigureList();

    bool isElementHighlighted();
}

