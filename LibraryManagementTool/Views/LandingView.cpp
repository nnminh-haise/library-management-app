#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "Elements.h"
#include "ExitView.h"
#include "DanhSachTheDocGia.h"

#include <iostream>
#include <string>
#include <format>

void LANDING_VIEW::RegisterDefaultSettings() {
	gettextsettings(&GLOBAL_VARIABLES::defaultTextSetting);
}

/*
* This is the program default running module.
* This module will render a selection menu for user to choose the next operations.
* User can use arrow keys to navigate through the available selections.
*/
void LANDING_VIEW::Run(AVL_TREE::Pointer& danhSachTheDocGia) {

	//* Create window.
	ELEMENTS::Window landing(CONSTANTS::WINDOW_DIMENSION, CONSTANTS::WINDOW_TITLE);
	landing.Activate();

	//* Setup all necessary default settings.
	LANDING_VIEW::RegisterDefaultSettings();
	const int BUTTON_HEIGHT = 50;

	//* RenderBackground background
	landing.RenderBackground();

	//* Create program's title box
	ELEMENTS::Cell programTitle(ELEMENTS::Cell::Mode::READ_MODE, "QUAN LI THU VIEN", HELPER::Coordinate(300, 200), 300, BUTTON_HEIGHT, 0);
	programTitle.SetHorizontalAlign(ELEMENTS::Align::CENTER);
	programTitle.SetBackgroundColor(14);


	//* Create list of buttons
	ELEMENTS::Cell buttons[6];

	//* Initialize each button with the coordinate on the graphic window
	buttons[0] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, "DANH SACH DAU SACH", HELPER::Coordinate(300, 300), 300, BUTTON_HEIGHT, 0);
	buttons[1] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, "DANH SACH THE DOC GIA", HELPER::Coordinate(300, 400), 300, BUTTON_HEIGHT, 0);
	buttons[2] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, "THONG KE", HELPER::Coordinate(300, 500), 300, BUTTON_HEIGHT, 0);
	buttons[3] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, "HUONG DAN", HELPER::Coordinate(150, 700), 300, BUTTON_HEIGHT, 0);
	buttons[4] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, "ABOUT US", HELPER::Coordinate(500, 700), 150, BUTTON_HEIGHT, 0);
	buttons[5] = ELEMENTS::Cell(ELEMENTS::Cell::Mode::READ_MODE, "EXIT", HELPER::Coordinate(700, 700), 150, BUTTON_HEIGHT, 0);

	//* Program loop 
	char inputKey{};
	int activeButtonIndicator = 0;

	while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {

		//* Default menu settings
		for (int i = 0; i < 6; ++i) {
			buttons[i].SetHorizontalAlign(ELEMENTS::Align::CENTER);
			buttons[i].SetBackgroundColor(9);
			buttons[i].SetTextColor(WHITE);
		}
		buttons[activeButtonIndicator].SetStatus(true);

		programTitle.ReadMode();

		for (int i = 0; i < 6; ++i) {
			buttons[i].ReadMode();
		}

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
					buttons[activeButtonIndicator].SetStatus(false);
					--activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].SetStatus(false);
					activeButtonIndicator = 5;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::DOWN_ARROW): {
				std::cerr << std::format("PRESSED DOWN ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator + 1 < 6) {
					buttons[activeButtonIndicator].SetStatus(false);
					++activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].SetStatus(false);
					activeButtonIndicator = 0;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::LEFT_ARROW): {
				std::cerr << std::format("PRESSED LEFT ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator - 1 >= 0) {
					buttons[activeButtonIndicator].SetStatus(false);
					--activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].SetStatus(false);
					activeButtonIndicator = 5;
				}
				break;
			}
			case (ELEMENTS::SpecialKey::RIGHT_ARROW): {
				std::cerr << std::format("PRESSED RIGHT ARROW!\n");

				//* Menu's button Indicator changes logic
				if (activeButtonIndicator + 1 < 6) {
					buttons[activeButtonIndicator].SetStatus(false);
					++activeButtonIndicator;
				}
				else {
					buttons[activeButtonIndicator].SetStatus(false);
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
						DANH_SACH_THE_DOC_GIA_VIEW::Run(danhSachTheDocGia);
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
						EXIT_VIEW::Run();
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
