#pragma once

#include "../Helper/Helper.h"

#include <string>

namespace ELEMENTS {
    enum AlignmentOptions {
        LEFT, CENTER, RIGHT
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

	class Cell {
    public:
        enum Mode {
            INPUT_MODE, READ_MODE
        };

        HELPER::Coordinate position;
        HELPER::Coordinate textPosition;
        HELPER::Dimension textDimension;
        HELPER::Dimension dimension;
        AlignmentOptions align;
        Padding padding;
        Fill fill;
        bool active;
        Mode mode;
        int fontSize;
        int fontStyle;
        int textColor;
        int maxNumberOfCharacter;
        bool defaultFont;

        Cell();

        Cell(HELPER::Coordinate position, int maxNumberOfCharacter);
        
        void Log();

        void UpdateFont();

        /*virtual void ReadMode() = 0;

        virtual void InputMode() = 0;*/

        void ReadMode();

        void InputMode();
    };
}

