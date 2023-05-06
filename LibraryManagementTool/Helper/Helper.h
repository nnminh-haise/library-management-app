#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <format>
#include <chrono>

#include "../Graphics/graphics.h"

namespace HELPER {
    class Date {
    public:
        Date();
        Date(const std::string& dateString);
        Date(int day, int month, int year);
        static Date Random();
        std::string Stringify() const;
        int DaysBetween(const Date& other) const;
        void ParseFromString(const std::string& dateString);

        Date operator+(int days) const;
        Date operator-(int days) const;

        friend bool operator>(const Date& lhs, const Date& rhs);

    private:
        int day_;
        int month_;
        int year_;

        static bool IsLeapYear(int year);
        static int DaysInMonth(int month, int year);
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

    void Extract(std::string source, const std::string& seperator, std::string*& result, int& size);
}

namespace VALIDATOR {
    bool OnlyDigit(const std::string& str);
}
