
#include <iostream>
#include <string>
#include <format>
#include <thread>
#include "Graphics/graphics.h"
#pragma comment(lib, "Graphics/graphics.lib")


#include "Helper/Helper.h"
#include "Views/Elements.h"
#include "DauSach/DauSach.h"
#include "Views/LandingView.h"


class ID_Cell : public ELEMENTS::Cell {
public:
	bool ReadMode(std::string content) {
		if (content.length() > this->maxNumberOfCharacter) {
			this->fill.fillColor = RED;
			this->fill.Draw();
			return false;
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

int main() {
	//ELEMENTS::Window window(HELPER::Dimension(1920, 1080), "LIBRARY MANAGEMENT TOOL");

	//window.Activate();

	//ID_Cell idCell;
	//idCell.Initialize(HELPER::Coordinate(50, 100), 20);
	//idCell.characterDimension.width = textwidth((char*)"B");
	//std::string res = idCell.InputMode();
	//idCell.ReadMode(res);

	//window.Deactivate();

	//std::clog << "[INFO] PROGRAM STOPPED!\n";

	//LandingView::Run();

	HELPER::GetKey();
	return 0;
}

