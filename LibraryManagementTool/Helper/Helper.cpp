
#include "Helper.h"

#include "../Graphics/graphics.h"
#include "../Tabs/Elements.h"

#include <iostream>
#include <ctime>
#include <string>
#include <format>

HELPER::Date::Date() {
    std::time_t current_time = std::time(nullptr);
    struct std::tm local_time;
    localtime_s(&local_time, &current_time);
    this->year = local_time.tm_year + 1900;
    this->month = local_time.tm_mon + 1;
    this->day = local_time.tm_mday;
}

HELPER::Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

HELPER::Date HELPER::Date::Random() {
    int maxDaysInMonth[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    // Generate a random year between 1900 and 2100
    int year = rand() % 201 + 1900;

    // Generate a random month between 1 and 12
    int month = rand() % 12 + 1;

    // Check if it's a leap year and adjust max days in February accordingly
    if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)) {
        maxDaysInMonth[1] = 29;
    }

    // Generate a random day between 1 and the maximum number of days in the given month and year
    int maxDays = maxDaysInMonth[month - 1];
    int day = rand() % maxDays + 1;

    return HELPER::Date(day, month, year);
}

std::string HELPER::Date::Stringfy() {
    return std::format("{}/{}/{}", this->day, this->month, this->year);
}

HELPER::Dimension::Dimension() : width(0), height(0) {
}

HELPER::Dimension::Dimension(int width, int height) : width(width), height(height) {
}

HELPER::Dimension::Dimension(const std::string& target) {
    this->width = textwidth((char*)target.c_str());
    this->height = textheight((char*)target.c_str());
}

void HELPER::Dimension::Log() {
    std::clog << std::format("Dimention: [{}x{}]\n", this->width, this->height);
}

HELPER::Coordinate::Coordinate() : x(0), y(0) {
}

HELPER::Coordinate::Coordinate(int x, int y) : x(x), y(y) {
}

void HELPER::Coordinate::Log() {
    std::clog << std::format("({}, {})\n", this->x, this->y);
}

HELPER::Rectangle::Rectangle() {
    this->topLeft = this->topRight = this->bottomLeft = this->bottomRight = HELPER::Coordinate();
    this->dimension = HELPER::Dimension();
}

HELPER::Rectangle::Rectangle(Coordinate topLeft, Coordinate bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    this->topRight = HELPER::Coordinate(this->bottomRight.x, this->topLeft.y);
    this->bottomLeft = HELPER::Coordinate(this->topLeft.x, this->bottomRight.y);
    this->dimension = HELPER::Dimension(this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y);
}

HELPER::Rectangle::Rectangle(Coordinate topLeft, int width, int height) {
    this->dimension = HELPER::Dimension(width, height);
    this->topLeft = topLeft;
    this->topRight = HELPER::Coordinate(this->topLeft.x + width, this->topLeft.y);
    this->bottomLeft = HELPER::Coordinate(this->topLeft.x, this->topLeft.y + height);
    this->bottomRight = HELPER::Coordinate(this->topLeft.x + width, this->topLeft.y + height);
}

void HELPER::Rectangle::Log() {
    std::clog << std::format("A({}, {}); B({}, {});\n", this->topLeft.x, this->topLeft.y, this->topRight.x, this->topRight.y);
    std::clog << std::format("C({}, {}); D({}, {});\n", this->bottomLeft.x, this->bottomLeft.y, this->bottomRight.x, this->bottomRight.y);
}

HELPER::Coordinate HELPER::GetCurrentMouseCoordinate() {
    return {mousex(), mousey()};
}

void HELPER::GetKey() {
    ELEMENTS::Window trial(HELPER::Dimension(800, 300), "TRIAL KEY PRESS");

    trial.Activate();

    setfillstyle(SOLID_FILL, WHITE);
    bar(0, 0, 1920, 1080);

    char inputKey = -1;

    while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {
        while (!kbhit()) {
            
            setbkcolor(WHITE);
            setcolor(BLACK);

            moveto(100, 150);
            outtext((char*)"PRESS ANY KEY TO GET ASCII CODE OR PRESS ESC TO EXIT PRORGAM!");

            if (inputKey != -1) {
                std::string text = "PRESSED KEY CODE: " + std::to_string((int)inputKey);
                moveto(100, 190);
                outtext((char*)text.c_str());
            }
        }

        inputKey = getch();
    }

    trial.Deactivate();
}

void HELPER::ShowColorPallet() {
    ELEMENTS::Window window(HELPER::Dimension(1000, 500), "COLOR PALLET WINDOW");
    window.Activate();

    setfillstyle(SOLID_FILL, WHITE);
    bar(0, 0, 1000, 500);

    char inputKey{};
    while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {
        moveto(20, 20);
        outtext((char*)"BGI COLOR PALLET");

        for (int i = 0; i < 16; ++i) {
            std::cerr << std::format("({}, {})\n", 50, i * 20 + 50);
            moveto(50, i * 20 + 50);
            setbkcolor(i);
            std::string text = "THIS IS A SAMPLE STRING WITH THE CODED COLOR: " + std::to_string(i);
            std::cerr << text + "\n";
            outtext((char*)text.c_str());
        }

        inputKey = getch();

    }

    window.Deactivate();
}

std::string STR::Trim(std::string target) {
    if (target.length() == 0) {
        return target;
    }

    while (target[0] == ' ') {
        target.erase(0, 1);
    }
    while (target[target.length() - 1] == ' ') {
        target.erase(target.length() - 1, 1); 
    }
    for (int i = 0; i < target.length() - 1; ++i) {
        if (target[i] == ' ' && target[i + 1] == ' ') {
            target.erase(i, 1);
        }
    }
    return target;
}

int rgb(int r, int g, int b) {
    return COLOR(r, g, b);
}
