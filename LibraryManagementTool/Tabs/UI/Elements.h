#pragma once

#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "Button.h"

#include <string>

namespace ELEMENTS {
    enum Align {
        LEFT, CENTER, RIGHT, TOP, MIDDLE, BOTTOM
    };

    enum SpecialKey {
        ENTER = 13, BACKSPACE = 8, SPACE = 32, ESCAPE = 27,
        UP_ARROW = 72, DOWN_ARROW = 80, LEFT_ARROW = 75, RIGHT_ARROW = 77
    };

    struct Window {
        HELPER::Dimension dimension;
        std::string title;
        bool active;
        int backgroundColor;

        Window(const HELPER::Dimension& dimension, const std::string& title);

        int Activate();

        void RenderBackground();

        void Deactivate();
    };

    struct Padding {
        int top, bottom, left, right;

        Padding();

        Padding(int all);

        Padding(int top, int bottom, int left, int right);
    };



    struct CircleFill {
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        HELPER::Dimension dimension;
        int fillColor;
        int borderColor;

        CircleFill();

        CircleFill(HELPER::Coordinate topLeft, int width, int height, int fillColor = WHITE, int borderColor = WHITE);

        CircleFill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int fillColor = WHITE, int borderColor = WHITE);

        CircleFill(int left, int top, int right, int bottom, int fillColor = WHITE, int borderColor = WHITE);

        void Draw();
    };

    class CloseButton {
    private:
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        HELPER::Dimension dimension;
        CircleFill fill;
        int textColor;
        std::string placeholder;
        bool isPointed;
        bool rightClicked;
        bool leftClicked;
        bool active;

    public:
        CloseButton();

        CloseButton(HELPER::Coordinate topLeft, int with, int height, int textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR, int fillcolor = BUTTON_DEFAULT_PROPERTIES::FILL_COLOR, int borderColor = BUTTON_DEFAULT_PROPERTIES::BORDER_COLOR);

        CloseButton(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR, int fillcolor = BUTTON_DEFAULT_PROPERTIES::FILL_COLOR, int borderColor = BUTTON_DEFAULT_PROPERTIES::BORDER_COLOR);

        void SetFillColor(int color);

        int GetFillColor();

        void SetTextColor(int color);

        int GetTextColor();

        void SetBorderColor(int color);

        int GetBorderColor();

        void SetPlaceholder(std::string placeholder);

        std::string GetPlaceholder();

        void SetStatus(bool status);

        bool GetStatus();

        void Display();

        bool IsPointed();

        bool LeftMouseClicked();

        bool RightMouseClicked();
    };


    class InputModeController { //* Interface
    public:
        char inputKey;
        bool inputMode;
        bool acceptKey;
        int characterCount;
        int characterLimit;
        std::string inputString;
        Button* currentTextBox;
        Button* outputTextBox;

        bool acceptNum;
        bool acceptAlpha;
        bool acceptSpace;

        InputModeController();

        void Activate(Button* inputTextBox, Button* outputTextBox, int characterLimit, bool acceptAlpha, bool acceptNum, bool acceptSpace);

        void Deactivate();

        std::string GetInputString();

        bool InInputMode();

        bool KeyValidation(const char& chr);

        void ActionOnKey(const char& chr);
    };
}

namespace DATASHEET {
    struct Row {
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        int columnCount;
        Button* labels;
        std::string* labelPlaceholders;
        int* characterLimits;
        int rowHeight;

        Row();

        Row(int columnCount, HELPER::Coordinate topLeft, std::string* labelPlaceholders, int* characterLimits, int rowHeight);

        void SetPlaceHolder(std::string* labelPlaceholders);

        void Display();
    };

    struct Datasheet {
        int rowCount;
        int columnCount;
        int rowHeight;
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        std::string* labelPlaceholders;
        int* characterLimits;
        Row* rows;

        void DefaultLabelsProperties(Row& tbx);

        void DefaultDataFieldProperties(Row& tbx, int order);

        Datasheet();

        Datasheet(int rowCount, int columnCount, int rowHeight, HELPER::Coordinate topLeft, std::string* labelPlaceholders, int* characterLimits);

        void UpdateNewPlaceholder(std::string* newPlaceholder, int rowIndicator);

        void Display();
    };

    struct Controler {
        int rowCount;
        int columnCount;
        int rowHeight;
        HELPER::Coordinate topLeft;
        int datasheetCount;
        Datasheet* sheets;
        int activeSheet;

        Controler();

        Controler(int rowCount, int columnCount, int rowHeight, HELPER::Coordinate topLeft);

        ~Controler();

        void UpdateActiveSheet(int indicator);

        void Display();
    };
}
