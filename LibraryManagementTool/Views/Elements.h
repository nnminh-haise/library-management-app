#pragma once

#include "../Helper/Helper.h"

#include <string>

namespace ELEMENTS {
    enum AlignmentOptions {
        LEFT, CENTER, RIGHT
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

        Window(HELPER::Dimension dimension, std::string title);

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
        HELPER::Coordinate position;
        HELPER::Rectangle coordinates;
        HELPER::Dimension dimension;
        int fillColor;
        int borderColor;

        Fill();

        Fill(HELPER::Coordinate position, int width, int height);

        Fill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight);

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

	struct Cell {
    public:
        enum Mode {
            INPUT_MODE, READ_MODE
        };
        
    private:
        HELPER::Coordinate position;
        HELPER::Dimension dimension;
        HELPER::Coordinate textPosition;
        HELPER::Dimension textDimension;
        Padding padding;
        Fill fill;
        AlignmentOptions textAlign;
        Cursor cursor;
        std::string placeholder;
        Mode mode;
        bool active;
        int fontSize;
        int fontStyle;
        int textColor;
        int backgroundColor;
        int characterLimit;
        bool customFont;

    public:

        Cell();

        Cell(ELEMENTS::Cell::Mode mode, const std::string& placeholder, HELPER::Coordinate position, int width, int height);

        Cell(ELEMENTS::Cell::Mode mode, const std::string& placeholder, HELPER::Coordinate position, HELPER::Dimension dimension);

        void SetPosition(HELPER::Coordinate position);

        HELPER::Coordinate GetPosition();

        bool SetDimension(HELPER::Dimension dimension);

        HELPER::Dimension GetDimension();

        void SetPadding(ELEMENTS::Padding padding);

        ELEMENTS::Padding GetPadding();

        void SetTextAlign(ELEMENTS::AlignmentOptions align);

        ELEMENTS::AlignmentOptions GetTextAlign();

        void SetPlaceHolder(const std::string& placeholder);

        std::string GetPlaceholder();

        void SetFontSize(int fontSize);

        int GetFontSize();

        void SetFontStyle(int fontStyle);

        int GetFontStyle();

        void SetTextColor(int color);

        int GetTextColor();

        void SetBackgroundColor(int color);

        int GetBackgroundColor();

        void SetCharacterLimit(int limit);

        int GetCharacterLimit();

        void SetStatus(bool status);

        bool GetStatus();

        void SetTextPosition(HELPER::Coordinate position);

        HELPER::Coordinate GetTextPosition();

        void Log();

        bool FitContent();

        void UpdateTextDecoration();

        void UpdateCellDimension();

        void UpdateAlignment();

        bool ReadMode();
    };
}
