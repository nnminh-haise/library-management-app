#include "Helper.h"

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
