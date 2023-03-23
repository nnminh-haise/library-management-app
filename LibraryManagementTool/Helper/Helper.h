#pragma once

#include <iostream>
#include <ctime>
#include <string>

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
}
