#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "Elements.h"
#include "ExitView.h"

#include <iostream>
#include <string>
#include <format>

void LANDING_VIEW::RegisterDefaultSettings() {
	gettextsettings(&GLOBAL_VARIABLES::defaultTextSetting);
}

class CustomCell : public ELEMENTS::Cell {
public:
	bool ReadMode(std::string content) {
		if (content.length() > this->maxNumberOfCharacter) {
			this->fill.fillColor = RED;
			this->fill.Draw();
			return false;
		}

		if (this->active) {
			this->fill.fillColor = 12;
		}

		this->UpdateFont();
		this->UpdateAlignment(content);
		this->fill.Draw();
		outtextxy(this->textPosition.x, this->textPosition.y, (char*)content.c_str());

		return true;
	}

	bool AcceptKeys(const char& key, const std::string& s) {
		if (isalpha(key)) {
			return true;
		}
		if (key == ELEMENTS::SpecialKey::SPACE && s.length() > 0 && s[s.length() - 1] != ' ') {
			return true;
		}
		return false;
	}

	std::string InputMode() {
		this->UpdateFont();
		std::string result = "";
		char keyPressed{};
		int counter = 0;
		this->cursor = ELEMENTS::Cursor(HELPER::Coordinate(this->textPosition.x, this->textPosition.y));

		while (keyPressed != ELEMENTS::SpecialKey::ENTER) {
			int colorSelector = 0;

			while (!kbhit()) {
				this->fill.Draw();
				outtextxy(this->textPosition.x, this->textPosition.y, (char*)result.c_str());

				this->cursor.coordinate.x = this->textPosition.x + textwidth((char*)result.c_str());

				this->cursor.color = (colorSelector++ % 2 == 0 ? BLACK : WHITE);

				this->cursor.Draw();
			}

			keyPressed = toupper(getch());

			if (result.length() > 0 && keyPressed == ELEMENTS::SpecialKey::BACKSPACE) {
				result.pop_back();
				--counter;
			}
			else if (keyPressed != ELEMENTS::SpecialKey::ENTER && counter < this->maxNumberOfCharacter && AcceptKeys(keyPressed, result)) {
				++counter;
				result += keyPressed;
			}
		}

		return STR::Trim(result);
	}
};

/*
* This is the program default running module. This module will render a selection menu for user to choose the next operations.
* User can use arrow keys to navigate through the available selections.
*/
void LANDING_VIEW::Run() {

	//* Create window.
	ELEMENTS::Window landing(CONSTANTS::WINDOW_DIMENSION, CONSTANTS::WINDOW_TITLE);
	landing.Activate();

	//* Get all necessary default settings.
	LANDING_VIEW::RegisterDefaultSettings();

	//* Setup view's background
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 1920, 1080);

	//* Create app's title box
	CustomCell programTitle;
	programTitle.Initialize(HELPER::Coordinate(300, 200), 25);
	programTitle.align = ELEMENTS::AlignmentOptions::CENTER;
	programTitle.fill.fillColor = 14;
	
	//* Create list of buttons
	CustomCell buttons[6];

	//* Initialize each button with the cooordinate on the graphic window
	buttons[0].Initialize(HELPER::Coordinate(300, 300), 25);
	buttons[1].Initialize(HELPER::Coordinate(300, 400), 25);
	buttons[2].Initialize(HELPER::Coordinate(300, 500), 25);
	buttons[3].Initialize(HELPER::Coordinate(150, 700), 22);
	buttons[4].Initialize(HELPER::Coordinate(500, 700), 11);
	buttons[5].Initialize(HELPER::Coordinate(700, 700), 11);

	//* Program loop 
	char inputKey{};
	int activeButtonIndicator = 0;

	while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {
		//* Default menu settings
		for (int i = 0; i < 6; ++i) {
			buttons[i].align = ELEMENTS::AlignmentOptions::CENTER;
			buttons[i].fill.fillColor = 9;
			buttons[i].textColor = WHITE;
		}
		buttons[activeButtonIndicator].active = true;

		programTitle.ReadMode("QUAN LI THU VIEN");
		buttons[0].ReadMode("DANH SACH DAU SACH");
		buttons[1].ReadMode("DANH SACH THE DOC GIA");
		buttons[2].ReadMode("THONG KE");
		buttons[3].ReadMode("HUONG DAN");
		buttons[4].ReadMode("ABOUT US");
		buttons[5].ReadMode("EXIT");

		//* You can uncomment this line to watch which button is currently active when the program is running.
		//std::cerr << std::format("[ACTIVE STATUS] ACTIVE BUTTON: BUTTON[{}]\n", activeButtonIndicator);

		//* Get user's pressed key.
		inputKey = getch();

		//* Menu's logic controller base on the user's pressed key.
		switch (inputKey) {
			case (ELEMENTS::SpecialKey::UP_ARROW): {
				std::cerr << std::format("PRESSED UP ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator - 1 >= 0) {
					buttons[activeButtonIndicator].active = false;
					--activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].active = false;
					activeButtonIndicator = 5;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::DOWN_ARROW): {
				std::cerr << std::format("PRESSED DOWN ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator + 1 < 6) {
					buttons[activeButtonIndicator].active = false;
					++activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].active = false;
					activeButtonIndicator = 0;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::LEFT_ARROW): {
				std::cerr << std::format("PRESSED LEFT ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator - 1 >= 0) {
					buttons[activeButtonIndicator].active = false;
					--activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].active = false;
					activeButtonIndicator = 5;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::RIGHT_ARROW): {
				std::cerr << std::format("PRESSED RIGHT ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator + 1 < 6) {
					buttons[activeButtonIndicator].active = false;
					++activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].active = false;
					activeButtonIndicator = 0;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::ESCAPE): {
				std::cerr << std::format("PRESSED ESCAPE KEY!\n");
				std::cerr << std::format("PROGRAM STOPPED!\n");
				break;
			}
			case (ELEMENTS::SpecialKey::ENTER): {
				//std::cerr << std::format("PRESSED ENTER KEY!\n");
				
				switch (activeButtonIndicator) {
					case (0): {
						break;
					}
					case (1): {
						break;
					}
					case (2): {
						break;
					}
					case (3): {
						break;
					}
					case (4): {
						break;
					}
					case (5): {
						ExitView::Run();
						return;
						break;
					}
				}

				break;
			}
		}
	}

	landing.Deactivate();
}
