#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "Elements.h"

#include <iostream>
#include <string>
#include <format>

void LandingView::Run() {
	ELEMENTS::Window landing(HELPER::Dimension(1920, 1080), "LIBRARY MANAGEMENT TOOL");

	landing.Activate();

	//* Program loop
	char inputKey{};
	while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {
		while (!kbhit()) {
			moveto(100, 100);
			outtext((char*)"Hello world");
		}

		inputKey = getch();

		std::cout << std::format("key = {}\n", (int)inputKey);

		switch (inputKey) {
			case (ELEMENTS::SpecialKey::UP_ARROW): {
				std::cout << std::format("UP ARROW!\n");
				break;
			}
			case (ELEMENTS::SpecialKey::DOWN_ARROW): {
				std::cout << std::format("DOWN ARROW!\n");
				break;
			}
			case (ELEMENTS::SpecialKey::LEFT_ARROW): {
				std::cout << std::format("LEFT ARROW!\n");
				break;
			}
			case (ELEMENTS::SpecialKey::RIGHT_ARROW): {
				std::cout << std::format("RIGHT ARROW!\n");
				break;
			}
		}
	}

	landing.Deactivate();
}
