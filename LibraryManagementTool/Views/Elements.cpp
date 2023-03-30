#include "Elements.h"
#include "../Graphics/graphics.h"

#include <iostream>
#include <string>
#include <format>
#include <thread>

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

ELEMENTS::Cursor::Cursor() {
	this->coordinate = HELPER::Coordinate();
	this->dimension = HELPER::Dimension();
	this->color = BLACK;
}

ELEMENTS::Cursor::Cursor(HELPER::Coordinate coordinate) {
	this->coordinate = coordinate;
	this->dimension = HELPER::Dimension(2, textheight((char*)"H"));
	this->color = BLACK;
}

void ELEMENTS::Cursor::Log() {
	std::clog << std::format("Cursor   : ");
	this->coordinate.Log();
	std::clog << std::format("Dimension: [{} x {}]\n", this->dimension.width, this->dimension.height);
	std::clog << std::format("Color    : {}\n", this->color);
}

void ELEMENTS::Cursor::Update(HELPER::Coordinate newCoordinate) {
	this->coordinate = newCoordinate;
}

void ELEMENTS::Cursor::Draw() {
	setfillstyle(SOLID_FILL, this->color);
	setbkcolor(this->color);
	bar(
		this->coordinate.x,
		this->coordinate.y,
		this->coordinate.x + this->dimension.width,
		this->coordinate.y + this->dimension.height
	);
	Sleep(80);
}

void ELEMENTS::Cell::UpdateFont() {
	if (!this->defaultFont) {
		settextstyle(this->fontStyle, HORIZ_DIR, this->fontSize);
	}

	setcolor(this->textColor);
	this->dimension = HELPER::Dimension(
		this->padding.left + this->padding.right + this->characterDimension.width * this->maxNumberOfCharacter,
		this->padding.top + this->padding.bottom + this->characterDimension.height
	);
}

void ELEMENTS::Cell::UpdateAlignment(std::string content) {
	int remainWidth = this->characterDimension.width * this->maxNumberOfCharacter - textwidth((char*)content.c_str());
	int remainHeight = this->characterDimension.height * this->maxNumberOfCharacter - textheight((char*)content.c_str());

	switch (this->align) {
		case (ELEMENTS::AlignmentOptions::LEFT): {
			this->textPosition.x = this->position.x + this->padding.left;
			this->textPosition.y = this->position.y + this->padding.top;
			break;
		}
		case (ELEMENTS::AlignmentOptions::CENTER): {
			this->textPosition.x = this->position.x + this->padding.left + remainWidth / 2;
			this->textPosition.y = this->position.y + this->padding.top;
			break;
		}
		case (ELEMENTS::AlignmentOptions::RIGHT): {
			this->textPosition.x = this->position.x + this->padding.left + remainWidth;
			this->textPosition.y = this->position.y + this->padding.top;
			break;
		}
	}
}

ELEMENTS::Cell::Cell() {
	this->position = HELPER::Coordinate();
	this->textPosition = HELPER::Coordinate();
	this->textDimension = HELPER::Dimension();
	this->dimension = HELPER::Dimension();
	this->characterDimension = HELPER::Dimension();
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
	this->cursor = ELEMENTS::Cursor();
}

void ELEMENTS::Cell::Initialize(HELPER::Coordinate position, int maxNumberOfCharacter) {
	this->maxNumberOfCharacter = maxNumberOfCharacter;
	this->position = position;
	this->characterDimension = HELPER::Dimension(textwidth((char*)"H"), textheight((char*)"H"));
	this->fontSize = 3;
	this->fontStyle = 8;
	this->textColor = BLACK;
	this->defaultFont = true;
	this->padding = ELEMENTS::Padding(10);
	this->UpdateFont();
	this->fill = ELEMENTS::Fill(this->position, this->dimension.width, this->dimension.height);
	this->active = false;
	this->mode = ELEMENTS::Cell::Mode::READ_MODE;
	this->textPosition = HELPER::Coordinate(
		this->position.x + this->padding.left,
		this->position.y + this->padding.top
	);
	this->cursor = this->textPosition;
	this->align = ELEMENTS::AlignmentOptions::LEFT;
}

void ELEMENTS::Cell::Log() {
	std::clog << std::format("Position  : ");
	this->position.Log();
	std::clog << std::format("Dimension : [{} x {}]\n", this->dimension.width, this->dimension.height);
	std::clog << std::format("Text size : [{} x {}]\n", this->textDimension.width, this->textDimension.height);
	std::clog << std::format("Default f : {}\n", this->defaultFont);
	std::clog << std::format("Font size : {}\n", this->fontSize);
	std::clog << std::format("Font style: {}\n", this->fontStyle);
	std::clog << std::format("Status    : {}\n", this->active ? "Active" : "Inactive");
	std::clog << std::format("Cell mode : {}\n", this->mode == ELEMENTS::Cell::Mode::READ_MODE ? "READ" : "INPUT");
	std::clog << std::format("Text color: {}\n", this->textColor);
	std::clog << std::format("Alignment : {}\n", this->align == ELEMENTS::AlignmentOptions::LEFT ? "LEFT" : this->align == ELEMENTS::AlignmentOptions::CENTER ? "CENTER" : "RIGHT");
	std::clog << std::format("Coordinate: \n");
	this->fill.coordinates.Log();
}


