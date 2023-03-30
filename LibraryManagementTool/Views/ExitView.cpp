#include "ExitView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "Elements.h"

#include <iostream>
#include <string>
#include <format>

void ExitView::Run() {
	
	//* Setup view's background
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 1920, 1080);

	//* Setup
	settextstyle(3, HORIZ_DIR, 6);
	std::string greeting = "THANK YOU FOR USING LIBRARY MANAGEMENT TOOL!";
	HELPER::Dimension greetingDimension(greeting);
	HELPER::Coordinate greetingCoordinate(
		CONSTANTS::WINDOW_DIMENSION.width / 2 - greetingDimension.width / 2,
		CONSTANTS::WINDOW_DIMENSION.height / 2 - greetingDimension.height / 2 - 100
	);
	ELEMENTS::Cell greetingBox(ELEMENTS::Cell::Mode::READ_MODE, greeting, greetingCoordinate, greetingDimension);

	bool escapeFlag = false;
	int milisecondCounter = 3000;
	char inputKey{};
	while (escapeFlag == false && milisecondCounter != 0) {
		greetingBox.ReadMode();

		while (!kbhit() && milisecondCounter != 0) {
			--milisecondCounter;
			std::cerr << std::format("time: {}\n", milisecondCounter);

			if (milisecondCounter == 999 || milisecondCounter == 1999 || milisecondCounter == 2999) {
				settextstyle(3, HORIZ_DIR, 3);
				std::string notifyMessage = std::format("Press ENTER or ESC to close program! Program will close in {}s", milisecondCounter / 1000 + 1);
				HELPER::Dimension notifyMessageDimension(greeting);
				HELPER::Coordinate notifyMessageCoordinate(
					CONSTANTS::WINDOW_DIMENSION.width / 2 - notifyMessageDimension.width / 2,
					CONSTANTS::WINDOW_DIMENSION.height / 2 - notifyMessageDimension.height / 2 + 100
				);
				ELEMENTS::Cell notifyBox(ELEMENTS::Cell::Mode::READ_MODE, notifyMessage, notifyMessageCoordinate, notifyMessageDimension);
				notifyBox.ReadMode();
			}
		}

		if (milisecondCounter != 0) {
			inputKey = getch();

			if (inputKey == ELEMENTS::SpecialKey::ENTER || inputKey == ELEMENTS::SpecialKey::ESCAPE) {
				escapeFlag = true;
			}
		}
	}

	system("cls");
	exit(0);
}
