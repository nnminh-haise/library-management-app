
#include "Helper.h"

#include "../Graphics/graphics.h"
#include "../Tabs/UI/Elements.h"

#include <iostream>
#include <ctime>
#include <string>
#include <format>

HELPER::Date::Date() {
    auto now = std::chrono::system_clock::now();
    time_t currentTime = std::chrono::system_clock::to_time_t(now);
    struct tm timeinfo;
    localtime_s(&timeinfo, &currentTime);
    day_ = timeinfo.tm_mday;
    month_ = timeinfo.tm_mon + 1;  // tm_mon is 0-based
    year_ = timeinfo.tm_year + 1900;  // tm_year is years since 1900
}

HELPER::Date::Date(const std::string& dateString)
{
    std::istringstream iss(dateString);
    char delimiter;
    int day, month, year;

    if (!(iss >> day >> delimiter >> month >> delimiter >> year) || delimiter != '/')
        throw std::invalid_argument("Invalid date format");

    //* Validate day
    if (day < 1 || day > DaysInMonth(month, year))
        throw std::out_of_range("Invalid day");

    //* Validate month
    if (month < 1 || month > 12)
        throw std::out_of_range("Invalid month");

    //* Validate year
    if (year < 1900 || year > 2100)
        throw std::out_of_range("Invalid year");

    day_ = day;
    month_ = month;
    year_ = year;
}

HELPER::Date::Date(int day, int month, int year) : day_(day), month_(month), year_(year) {}

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

    return Date(day, month, year);
}

std::string HELPER::Date::Stringify() const {
    return std::format("{}/{}/{}", this->day_, this->month_, this->year_);
}

int HELPER::Date::DaysBetween(const HELPER::Date& other) const {
    int days1 = day_;
    for (int m = 1; m < month_; m++)
        days1 += DaysInMonth(m, year_);

    int days2 = other.day_;
    for (int m = 1; m < other.month_; m++)
        days2 += DaysInMonth(m, other.year_);

    for (int y = year_; y < other.year_; y++)
        days2 += IsLeapYear(y) ? 366 : 365;

    return std::abs(days2 - days1);
}

void HELPER::Date::ParseFromString(const std::string& dateString) 
{
    std::istringstream iss(dateString);
    char delimiter;
    int day, month, year;

    if (!(iss >> day >> delimiter >> month >> delimiter >> year) || delimiter != '/')
        throw std::invalid_argument("Invalid date format");

    //* Validate day
    if (day < 1 || day > DaysInMonth(month, year))
        throw std::out_of_range("Invalid day");

    //* Validate month
    if (month < 1 || month > 12)
        throw std::out_of_range("Invalid month");

    //* Validate year
    if (year < 1900 || year > 2100)
        throw std::out_of_range("Invalid year");

    day_ = day;
    month_ = month;
    year_ = year;
}

HELPER::Date HELPER::Date::operator+(int days) const {
    Date result(*this);
    int totalDays = day_ + days;

    while (totalDays > DaysInMonth(result.month_, result.year_)) {
        totalDays -= DaysInMonth(result.month_, result.year_);
        ++result.month_;
        if (result.month_ > 12) {
            result.month_ = 1;
            ++result.year_;
        }
    }

    result.day_ = totalDays;
    return result;
}

HELPER::Date HELPER::Date::operator-(int days) const {
    Date result(*this);
    int totalDays = day_ - days;

    while (totalDays < 1) {
        --result.month_;
        if (result.month_ < 1) {
            result.month_ = 12;
            --result.year_;
        }
        totalDays += DaysInMonth(result.month_, result.year_);
    }

    result.day_ = totalDays;
    return result;
}

bool HELPER::operator>(const Date& lhs, const Date& rhs) {
    if (lhs.year_ > rhs.year_)
        return true;
    else if (lhs.year_ == rhs.year_) {
        if (lhs.month_ > rhs.month_)
            return true;
        else if (lhs.month_ == rhs.month_)
            return lhs.day_ > rhs.day_;
    }
    return false;
}

bool HELPER::Date::IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int HELPER::Date::DaysInMonth(int month, int year) {
    static const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month < 1 || month > 12)
        throw std::out_of_range("Invalid month");
    int days = daysPerMonth[month - 1];
    if (month == 2 && IsLeapYear(year))
        days++;
    return days;
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

HELPER::Fill::Fill() :
    topLeft(HELPER::Coordinate()), bottomRight(HELPER::Coordinate()), dimension(HELPER::Dimension()),
    fillColor(WHITE), borderColor(WHITE) {
}

HELPER::Fill::Fill(HELPER::Coordinate topLeft, int width, int height, int fillColor, int borderColor) {
    this->topLeft = topLeft;
    this->dimension.width = width;
    this->dimension.height = height;
    this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
    this->fillColor = fillColor;
    this->borderColor = borderColor;
}

HELPER::Fill::Fill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int fillColor, int borderColor) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    this->dimension.width = this->bottomRight.x - this->topLeft.x;
    this->dimension.height - this->bottomRight.y - this->topLeft.x;
    this->fillColor = fillColor;
    this->borderColor = borderColor;
}

HELPER::Fill::Fill(int left, int top, int right, int bottom, int fillColor, int borderColor) {
    this->topLeft = { left, top };
    this->bottomRight = { right, bottom };
    this->dimension = { this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y };
    this->fillColor = fillColor;
    this->borderColor = borderColor;
}

void HELPER::Fill::Draw() {
    setfillstyle(SOLID_FILL, this->fillColor);
    setcolor(borderColor);
    bar(this->topLeft.x, this->topLeft.y, this->bottomRight.x, this->bottomRight.y);
    rectangle(this->topLeft.x, this->topLeft.y, this->bottomRight.x, this->bottomRight.y);
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

    while (inputKey != ELEMENTS::Keyboard::ESCAPE) {
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
    while (inputKey != ELEMENTS::Keyboard::ESCAPE) {
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

void STR::Extract(std::string source, const std::string& separator, std::string*& result, int& size) {
    if (source.length() == 0) {
        result = nullptr;
        size = 0;
        return;
    }

    size_t position = 0;
    int count = 0;
    while ((position = source.find(separator, position)) != std::string::npos) {
        ++count;
        position += separator.length();
    }
    size = count + 1;

    int index = 0;
    position = 0;
    result = new std::string[size];
    while ((position = source.find(separator)) != std::string::npos) {
        result[index++] = source.substr(0, position);
        source.erase(0, position + separator.length());
    }
    result[index] = source;
}

int rgb(int red, int green, int blue) {
    return COLOR(red, green, blue);
}

bool VALIDATOR::OnlyDigit(const std::string& str) {
    if (str.length() == 0) {
        return false;
    }

    for (const char& chr : str) {
        if (std::isdigit(chr) == false) {
            return false;
        }
    }
    return true;
}
