#include "ExitView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "Elements.h"

#include <iostream>
#include <string>
#include <format>

class CustomMessageBox : public ELEMENTS::Cell {
public:
	bool ReadMode(std::string content) {
		if (content.length() > this->maxNumberOfCharacter) {
			return false;
		}

		this->UpdateFont();
		this->UpdateAlignment(content);
		this->fill.Draw();
		outtextxy(this->textPosition.x, this->textPosition.y, (char*)content.c_str());

		return true;
	}
};

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
	CustomMessageBox message;
	message.Initialize(greetingCoordinate, greeting.length());

	bool escapeFlag = false;
	int milisecondCounter = 3000;
	char inputKey{};
	while (escapeFlag == false && milisecondCounter != 0) {
		message.ReadMode(greeting);

		while (!kbhit() && milisecondCounter != 0) {
			--milisecondCounter;
			std::cerr << std::format("time: {}\n", milisecondCounter);

			if (milisecondCounter == 999 || milisecondCounter == 1999 || milisecondCounter == 2999) {
				settextstyle(3, HORIZ_DIR, 3);
				std::string greeting = std::format("Press ENTER or ESC to close program! Program will close in {}s", milisecondCounter / 1000 + 1);
				HELPER::Dimension greetingDimension(greeting);
				HELPER::Coordinate greetingCoordinate(
					CONSTANTS::WINDOW_DIMENSION.width / 2 - greetingDimension.width / 2,
					CONSTANTS::WINDOW_DIMENSION.height / 2 - greetingDimension.height / 2 + 100
				);
				CustomMessageBox message;
				message.Initialize(greetingCoordinate, greeting.length());
				message.ReadMode(greeting);
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
