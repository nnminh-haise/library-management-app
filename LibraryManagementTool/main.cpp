
#include <iostream>
#include <string>
#include "Graphics/graphics.h"
#pragma comment(lib, "Graphics/graphics.lib")

#include "DauSach/DauSach.h"
#include "Helper/Helper.h"



int main() {
	HELPER::Date today;
	std::clog << "Today is: " << today.Stringfy() << std::endl;
	HELPER::Date randomDate = randomDate.Random();
	std::clog << "Today is: " << randomDate.Stringfy() << std::endl;




	return 0;
}
