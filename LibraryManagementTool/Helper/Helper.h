#pragma once

#include <iostream>
#include <ctime>
#include <string>

#include "../Graphics/graphics.h"

namespace HELPER {
    struct Date {
        int day;
        int month;
        int year;

        Date();

        Date(int day, int month, int year);

        static Date Random();

        std::string Stringfy();
    };

    struct Dimension {
        int width;
        int height;

        Dimension();

        Dimension(int width, int height);

        Dimension(const std::string& target);

        void Log();
    };

    struct Coordinate {
        int x;
        int y;

        Coordinate();

        Coordinate(int x, int y);

        void Log();
    };

    struct Rectangle {
        Coordinate topLeft, topRight, bottomLeft, bottomRight;
        Dimension dimension;

        Rectangle();

        Rectangle(Coordinate topLeft, Coordinate bottomRight);

        Rectangle(Coordinate topLeft, int width, int height);

        void Log();
    };

    struct Fill {
        Coordinate topLeft;
        Coordinate bottomRight;
        Dimension dimension;
        int fillColor;
        int borderColor;

        Fill();

        Fill(Coordinate topLeft, int width, int height, int fillColor = WHITE, int borderColor = WHITE);

        Fill(Coordinate topLeft, Coordinate bottomRight, int fillColor = WHITE, int borderColor = WHITE);

        Fill(int left, int top, int right, int bottom, int fillColor = WHITE, int borderColor = WHITE);

        void Draw();
    };

    Coordinate GetCurrentMouseCoordinate();

    void GetKey();

    void ShowColorPallet();
}

int rgb(int r, int g, int b);

namespace STR {
    std::string Trim(std::string target);
}

namespace VALIDATOR {
    bool OnlyDigit(const std::string& str);
}
