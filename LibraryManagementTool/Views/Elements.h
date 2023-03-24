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

        Window(HELPER::Dimension dimension, std::string title);

        int Activate();

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

	class Cell {
    public:
        enum Mode {
            INPUT_MODE, READ_MODE
        };

        HELPER::Coordinate position;
        HELPER::Coordinate textPosition;
        HELPER::Dimension textDimension;
        HELPER::Dimension dimension;
        HELPER::Dimension characterDimension;
        AlignmentOptions align;
        Padding padding;
        Fill fill;
        Cursor cursor;
        Mode mode;
        bool active;
        int fontSize;
        int fontStyle;
        int textColor;
        int maxNumberOfCharacter;
        bool defaultFont;

        Cell();
        
        void Initialize(HELPER::Coordinate position, int maxNumberOfCharacter);

        void Log();

        void UpdateFont();

        void UpdateAlignment(std::string content);
    }; 
}