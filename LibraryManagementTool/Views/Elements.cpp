#include "Elements.h"
#include "../Graphics/graphics.h"

#include <iostream>
#include <string>
#include <format>

ELEMENTS::Window::Window(HELPER::Dimension dimension, std::string title) {
	this->dimension = dimension;
	this->title = title;
	this->active = false;
}

int ELEMENTS::Window::Activate() {
	this->active = true;
	return initwindow(this->dimension.width, this->dimension.height, (const char*)this->title.c_str());
}

void ELEMENTS::Window::Deactivate() {
	this->active = false;
	closegraph();
}

ELEMENTS::Padding::Padding() {
	this->top = this->bottom = this->left = this->right = 0;
}

ELEMENTS::Padding::Padding(int all) {
	this->top = this->bottom = this->left = this->right = all;
}

ELEMENTS::Padding::Padding(int top, int bottom, int left, int right) {
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
}

ELEMENTS::Fill::Fill() {
	this->position = HELPER::Coordinate();
	this->coordinates = HELPER::Rectangle();
	this->dimension = HELPER::Dimension();
	this->fillColor = WHITE;
	this->borderColor = WHITE;
}

ELEMENTS::Fill::Fill(HELPER::Coordinate position, int width, int height) {
	this->position = position;
	this->dimension = HELPER::Dimension(width, height);
	this->coordinates = HELPER::Rectangle(position, width, height);
	this->fillColor = WHITE;
	this->borderColor = WHITE;
}

ELEMENTS::Fill::Fill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight) {
	this->position = topLeft;
	this->coordinates = HELPER::Rectangle(topLeft, bottomRight);
	this->dimension = this->coordinates.dimension;
	this->fillColor = WHITE;
	this->borderColor = WHITE;
}

void ELEMENTS::Fill::Draw() {
	setfillstyle(SOLID_FILL, this->fillColor);
	setbkcolor(fillColor);
	bar(this->coordinates.topLeft.x, this->coordinates.topLeft.y, this->coordinates.bottomRight.x, this->coordinates.bottomRight.y);
}

void ELEMENTS::Cell::UpdateFont() {
	if (!this->defaultFont) {
		settextstyle(this->fontStyle, HORIZ_DIR, this->fontSize);
	}

	setcolor(this->textColor);
	this->textDimension = HELPER::Dimension(
		textwidth((char*)"W") * this->maxNumberOfCharacter,
		textheight((char*)"W")
	);
}

ELEMENTS::Cell::Cell() {
	this->position = HELPER::Coordinate();
	this->textPosition = HELPER::Coordinate();
	this->textDimension = HELPER::Dimension();
	this->dimension = HELPER::Dimension();
	this->padding = ELEMENTS::Padding();
	this->fill = ELEMENTS::Fill();
	this->active = false;
	this->mode = ELEMENTS::Cell::Mode::READ_MODE;
	this->align = ELEMENTS::AlignmentOptions::LEFT;
	this->fontSize = 3;
	this->fontStyle = 8;
	this->textColor = BLACK;
	this->defaultFont = true;
	this->maxNumberOfCharacter = 0;
	this->UpdateFont();
}

ELEMENTS::Cell::Cell(HELPER::Coordinate position, int maxNumberOfCharacter) {
	this->maxNumberOfCharacter = maxNumberOfCharacter;
	this->position = position;
	this->fontSize = 3;
	this->fontStyle = 8;
	this->textColor = BLACK;
	this->defaultFont = true;
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

void ELEMENTS::Cell::Log() {
	std::clog << std::format("Position  : ");
	this->position.Log();
	std::clog << std::format("Dimension : [{} x {}]\n", this->dimension.width, this->dimension.height);
	std::clog << std::format("Default f : {}\n", this->defaultFont);
	std::clog << std::format("Font size : {}\n", this->fontSize);
	std::clog << std::format("Font style: {}\n", this->fontStyle);
	std::clog << std::format("Status    : {}\n", this->active ? "Active" : "Inactive");
	std::clog << std::format("Cell mode : {}\n", this->mode == ELEMENTS::Cell::Mode::READ_MODE ? "READ" : "INPUT");
	std::clog << std::format("Text color: {}\n", this->textColor);
	std::clog << std::format("Coordinate: \n");
	this->fill.coordinates.Log();
}
