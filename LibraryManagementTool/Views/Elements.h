#pragma once

#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"

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

    struct Fill {
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        HELPER::Dimension dimension;
        int fillColor;
        int borderColor;

        Fill();

        Fill(HELPER::Coordinate topLeft, int width, int height, int fillColor = WHITE, int borderColor = WHITE);

        Fill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int fillColor = WHITE, int borderColor = WHITE);

        Fill(int left, int top, int right, int bottom, int fillColor = WHITE, int borderColor = WHITE);

        void Draw();
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

    class Cursor {
    public:
        HELPER::Coordinate coordinate;
        HELPER::Dimension dimension;
        int color;

        Cursor();

        Cursor(HELPER::Coordinate coordinate);

        void Log();

        void Update(HELPER::Coordinate newCoordinate);

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

    class Button {
    private:
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        HELPER::Dimension dimension;
        Fill fill;
        int textColor;
        std::string placeholder;
        bool isPointed;
        bool rightClicked;
        bool leftClicked;
        bool active;

    public:
        Button();

        Button(HELPER::Coordinate topLeft, int with, int height, int textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR, int fillcolor = BUTTON_DEFAULT_PROPERTIES::FILL_COLOR, int borderColor = BUTTON_DEFAULT_PROPERTIES::BORDER_COLOR);

        Button(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR, int fillcolor = BUTTON_DEFAULT_PROPERTIES::FILL_COLOR, int borderColor = BUTTON_DEFAULT_PROPERTIES::BORDER_COLOR);

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

    class TextBox {
    private:
        HELPER::Coordinate topLeft;
        HELPER::Coordinate bottomRight;
        HELPER::Dimension dimension;
        Fill fill;
        std::string placeholder;
        int textColor;
        int textSize;
        int textStyle;

    public:
        TextBox();

        TextBox(HELPER::Coordinate topLeft, int with, int height, int textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR, int fillcolor = BUTTON_DEFAULT_PROPERTIES::FILL_COLOR, int borderColor = BUTTON_DEFAULT_PROPERTIES::BORDER_COLOR);

        TextBox(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR, int fillcolor = BUTTON_DEFAULT_PROPERTIES::FILL_COLOR, int borderColor = BUTTON_DEFAULT_PROPERTIES::BORDER_COLOR);

        void SetFillColor(int color);

        int GetFillColor();

        void SetTextColor(int color);

        int GetTextColor();

        void SetBorderColor(int color);

        int GetBorderColor();

        void SetTextSize(int size);

        int GetTextSize();

        void SetTextStyle(int style);

        int GetTextStyle();

        void SetPlaceholder(std::string placeholder);

        std::string GetPlaceholder();

        void Display();
    };

	//struct Cell {
 //   public:
 //       enum Mode {
 //           INPUT_MODE, READ_MODE
 //       };
 //       
 //   private:
 //       HELPER::Coordinate position;
 //       HELPER::Dimension dimension;
 //       HELPER::Coordinate textPosition;
 //       HELPER::Dimension textDimension;
 //       Padding padding;
 //       Fill fill;
 //       Align horizontalAlign;
 //       Align verticalAlign;
 //       Cursor cursor;
 //       std::string placeholder;
 //       Mode mode;
 //       bool active;
 //       int fontSize;
 //       int fontStyle;
 //       int textColor;
 //       int characterLimit;
 //       bool customFont;

 //       bool ValidDimension();

 //   public:

 //       Cell();

 //       Cell (
 //           ELEMENTS::Cell::Mode mode, 
 //           const std::string& placeholder, 
 //           HELPER::Coordinate position, 
 //           int width, int height, 
 //           int characterLimit
 //       );

 //       Cell (
 //           ELEMENTS::Cell::Mode mode,
 //           const std::string& placeholder,
 //           HELPER::Coordinate position,
 //           HELPER::Dimension dimension,
 //           int characterLimit
 //       );

 //       void SetPosition(HELPER::Coordinate position);

 //       HELPER::Coordinate GetPosition();

 //       bool SetDimension(HELPER::Dimension dimension);

 //       HELPER::Dimension GetDimension();

 //       void SetPadding(ELEMENTS::Padding padding);

 //       ELEMENTS::Padding GetPadding();

 //       void SetHorizontalAlign(ELEMENTS::Align align);

 //       ELEMENTS::Align GetHorizontalAlign();

 //       void SetVerticalAlign(ELEMENTS::Align align);

 //       ELEMENTS::Align GetVerticalAlign();

 //       void SetPlaceHolder(const std::string& placeholder);

 //       std::string GetPlaceholder();

 //       void SetFontSize(int fontSize);

 //       int GetFontSize();

 //       void SetFontStyle(int fontStyle);

 //       int GetFontStyle();

 //       void SetTextColor(int color);

 //       int GetTextColor();

 //       void SetBackgroundColor(int color);

 //       int GetBackgroundColor();

 //       void SetBorderColor(int color);

 //       int GetBorderColor();

 //       void SetCharacterLimit(int limit);

 //       int GetCharacterLimit();

 //       void SetStatus(bool status);

 //       bool GetStatus();

 //       void SetTextPosition(HELPER::Coordinate position);

 //       HELPER::Coordinate GetTopLeft();

 //       HELPER::Coordinate GetBottomRight();

 //       HELPER::Coordinate GetTextPosition();

 //       void Log();

 //       bool FitContent();

 //       void UpdateTextDecoration();

 //       void UpdateAlignment();

 //       bool LoadContent(const std::string& content);

 //       bool ReadMode();

 //       std::string InputMode(bool(*validInput)(std::string), bool(*validKey)(char));
 //   };
}
