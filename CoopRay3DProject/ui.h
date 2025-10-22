#pragma once
#include <raylib.h>
#include "raygui.h"
#include"config.h"
#include"InitProgram.h"
#include"Drawer.h"

namespace UI {
    void DrawMainMenu();
    void DrawExitMenu();
    void DrawAddMenu
    (
        int currentFigureInDropdownBox    = 0,
        char* centerXT                    = new char[100] {'\0'},
        char* centerYT                    = new char[100] {'\0'},
        char* centerZT                    = new char[100] {'\0'},
        char* angleXT                     = new char[100] {'\0'},
        char* angleYT                     = new char[100] {'\0'},
        char* angleZT                     = new char[100] {'\0'},
        char* radT                        = new char[100] {'\0'},
        char* radElXT                     = new char[100] {'\0'},
        char* radElYT                     = new char[100] {'\0'},
        char* radElZT                     = new char[100] {'\0'},
        char* heightT                     = new char[100] {'\0'},
        char* circleStepT                 = new char[100] {'\0'}
    );
    void DrawEditMenu();
    void DrawDeleteMenu();
    
    void UpdateFigureList();
    void UpdateFigureList(Rectangle excludingRect);
    void DrawFigureList();

    bool isElementHighlighted();
    
    struct GuiTextBoxControl {
        char* str;
        Rectangle rect;
        bool editMode;

        GuiTextBoxControl(Rectangle r, char* s);

        void DrawControl();
    };
}

