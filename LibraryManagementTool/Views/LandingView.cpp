#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "Elements.h"

#include <iostream>
#include <string>
#include <format>

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

void LandingView::Run() {
	ELEMENTS::Window landing(HELPER::Dimension(1920, 1080), "LIBRARY MANAGEMENT TOOL");
	landing.Activate();

	//* Setup background
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 1920, 1080);

	//* Create menu options
	CustomCell programTitle;
	programTitle.Initialize(HELPER::Coordinate(300, 200), 25);
	programTitle.align = ELEMENTS::AlignmentOptions::CENTER;
	programTitle.fill.fillColor = 14;
	
	CustomCell buttons[6];

	buttons[0].Initialize(HELPER::Coordinate(300, 300), 25);
	buttons[0].align = ELEMENTS::AlignmentOptions::CENTER;
	buttons[0].fill.fillColor = 9;
	buttons[0].textColor = WHITE;
	buttons[0].active = true;

	buttons[1].Initialize(HELPER::Coordinate(300, 400), 25);
	buttons[1].align = ELEMENTS::AlignmentOptions::CENTER;
	buttons[1].fill.fillColor = 9;
	buttons[1].textColor = WHITE;

	buttons[2].Initialize(HELPER::Coordinate(300, 500), 25);
	buttons[2].align = ELEMENTS::AlignmentOptions::CENTER;
	buttons[2].fill.fillColor = 9;
	buttons[2].textColor = WHITE;

	buttons[3].Initialize(HELPER::Coordinate(150, 700), 22);
	buttons[3].align = ELEMENTS::AlignmentOptions::CENTER;
	buttons[3].fill.fillColor = 9;
	buttons[3].textColor = WHITE;

	buttons[4].Initialize(HELPER::Coordinate(500, 700), 11);
	buttons[4].align = ELEMENTS::AlignmentOptions::CENTER;
	buttons[4].fill.fillColor = 9;
	buttons[4].textColor = WHITE;

	buttons[5].Initialize(HELPER::Coordinate(700, 700), 11);
	buttons[5].align = ELEMENTS::AlignmentOptions::CENTER;
	buttons[5].fill.fillColor = 9;
	buttons[5].textColor = WHITE;

	//* Program loop
	char inputKey{};

	while (inputKey != ELEMENTS::SpecialKey::ESCAPE) {
		// programTitle.ReadMode("QUAN LI THU VIEN");
		// danhSachDauSachView.ReadMode("DANH SACH DAU SACH");
		// danhSachTheDocGiaView.ReadMode("DANH SACH THE DOC GIA");
		// thongKeView.ReadMode("THONG KE");
		// huongDanView.ReadMode("HUONG DAN");
		// aboutView.ReadMode("ABOUT US");
		// exitView.ReadMode("EXIT");

		// std::cerr << std::format("[ACTIVE STATUS] DANH SACH DAU SACH BUTTON : {}\n", danhSachDauSachView.active);
		// std::cerr << std::format("[ACTIVE STATUS] DANH SACH THE DOC GIA BUTTON : {}\n", danhSachTheDocGiaView.active);
		// std::cerr << std::format("[ACTIVE STATUS] DANH SACH THONG KE BUTTON : {}\n", thongKeView.active);
		// std::cerr << std::format("[ACTIVE STATUS] DANH SACH HUONG DAN BUTTON : {}\n", huongDanView.active);
		// std::cerr << std::format("[ACTIVE STATUS] DANH SACH ABOUT US BUTTON : {}\n", aboutView.active);
		// std::cerr << std::format("[ACTIVE STATUS] DANH SACH EXIT BUTTON : {}\n", exitView.active);

		inputKey = getch();

		//std::cout << std::format("key = {}\n", (int)inputKey);

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
			case (ELEMENTS::SpecialKey::ESCAPE): {
				std::cout << std::format("PROGRAM STOPPED\n");
				break;
			}
		}
	}

	landing.Deactivate();
}
