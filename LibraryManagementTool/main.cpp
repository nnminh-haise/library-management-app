
#include <iostream>
#include <string>
#include "Graphics/graphics.h"
#pragma comment(lib, "Graphics/graphics.lib")

#include "Helper/Helper.h"
#include "Views/Elements.h"

class ID_Cell : public ELEMENTS::Cell {
public:
	ID_Cell(HELPER::Coordinate position, int maxNumberOfCharacter) {
		this->maxNumberOfCharacter = maxNumberOfCharacter;
		this->position = position;
		this->fontSize = 3;
		this->fontStyle = 8;
		this->textColor = BLACK;
		this->UpdateFont();
		this->padding = ELEMENTS::Padding(20);
		this->dimension = HELPER::Dimension(
			this->textDimension.width + this->padding.left + this->padding.right,
			this->textDimension.height + this->padding.top + this->padding.bottom
		);
		this->fill = ELEMENTS::Fill(this->position, this->dimension.width, this->dimension.height);
		this->active = false;
		this->mode = ELEMENTS::Cell::Mode::READ_MODE;
		this->textPosition = HELPER::Coordinate(
			this->position.x + this->padding.left,
			this->position.y + this->padding.top
		);
		this->align = ELEMENTS::AlignmentOptions::LEFT;
	}

	void ReadMode(std::string content) {
		this->UpdateFont();
		this->fill.Draw();
		outtextxy(this->textPosition.x, this->textPosition.y, (char*)content.c_str());
	}
};

int main() {

	ELEMENTS::Window window(HELPER::Dimension(1920, 1080), "LIBRARY MANAGEMENT TOOL");

	window.Activate();

	ID_Cell idCell(
		HELPER::Coordinate(100, 100), 50
	);

	idCell.ReadMode("NHAT MINH");
	idCell.Log();
	
	std::cin.get();

	window.Deactivate();

	std::clog << "[INFO] PROGRAM STOPPED!\n";
	return 0;
}
