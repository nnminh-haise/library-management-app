#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/ConstantsAndGlobalVariables.h"

#include <iostream>
#include <string>
#include <format>
#include <thread>

ELEMENTS::Window::Window(HELPER::Dimension dimension, std::string title) {
	this->dimension = dimension;
	this->title = title;
	this->active = false;
	this->backgroundColor = WHITE;
}

int ELEMENTS::Window::Activate() {
	this->active = true;
	return initwindow(this->dimension.width, this->dimension.height, (const char*)this->title.c_str());
}

void ELEMENTS::Window::RenderBackground() {
	setfillstyle(SOLID_FILL, this->backgroundColor);
	bar(0, 0, this->dimension.width, this->dimension.height);
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

void ELEMENTS::Cell::UpdateTextDecoration() {
	setcolor(this->textColor);
	if (this->customFont) {
		settextstyle(this->fontStyle, HORIZ_DIR, this->fontSize);
	}
	this->textDimension.width = textwidth((char*)this->placeholder.c_str());
	this->textDimension.height = textheight((char*)this->placeholder.c_str());
}

bool ELEMENTS::Cell::FitContent() {

	//* Cannot update cell's dimension with none or empty placeholder
	if (this->placeholder.length() == 0) {
		return false;
	}

	this->padding = ELEMENTS::Padding(10); //* Update all side of padding to 10px
	this->UpdateTextDecoration();
	this->dimension.width = this->padding.left + this->padding.right + this->textDimension.width;
	this->dimension.height = this->padding.top + this->padding.bottom + this->textDimension.height;
	return true;
}

void ELEMENTS::Cell::UpdateCellDimension() {
	this->UpdateTextDecoration();
	this->dimension.width = this->padding.left + this->padding.right + this->textDimension.width;
	this->dimension.height = this->padding.top + this->padding.bottom + this->textDimension.height;
}

void ELEMENTS::Cell::UpdateAlignment() {
	this->UpdateTextDecoration();
	int remainWidth = this->dimension.width - this->padding.left - this->padding.right - this->textDimension.width;
	int remainHeight = this->dimension.height - this->padding.top - this->padding.bottom - this->textDimension.height;

	switch (this->textAlign) {
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
	this->dimension = HELPER::Dimension();
	this->textPosition = HELPER::Coordinate();
	this->textDimension = HELPER::Dimension();
	this->padding = ELEMENTS::Padding();
	this->fill = ELEMENTS::Fill();
	this->textAlign = ELEMENTS::AlignmentOptions::LEFT;
	this->cursor = ELEMENTS::Cursor();
	this->mode = ELEMENTS::Cell::Mode::READ_MODE;
	this->active = false;
	this->fontSize = GLOBAL_VARIABLES::defaultTextSetting.charsize;
	this->fontStyle = GLOBAL_VARIABLES::defaultTextSetting.font;
	this->textColor = BLACK;
	this->backgroundColor = WHITE;
	this->characterLimit = -1;
	this->customFont = false;
}

ELEMENTS::Cell::Cell(ELEMENTS::Cell::Mode mode, const std::string& placeholder, HELPER::Coordinate position, int width, int height) {
	//* Default settings
	this->customFont = false;
	this->padding = ELEMENTS::Padding(10);
	this->textAlign = ELEMENTS::AlignmentOptions::LEFT;
	this->cursor = ELEMENTS::Cursor();
	this->active = false;
	this->fontSize = GLOBAL_VARIABLES::defaultTextSetting.charsize;
	this->fontStyle = GLOBAL_VARIABLES::defaultTextSetting.font;
	this->textColor = BLACK;
	this->backgroundColor = WHITE;
	this->characterLimit = placeholder.length();

	//* Argument settings
	this->mode = mode;
	this->placeholder = placeholder;
	this->position = position;

	//* Update cell's dimension
	this->FitContent();
	if (width > this->dimension.width) {
		this->dimension.width = width;
	}
	if (height > this->dimension.height) {
		this->dimension.height = height;
	}

	//* Follow up settings
	this->fill = ELEMENTS::Fill(this->position, this->dimension.width, this->dimension.height);
	this->textPosition = HELPER::Coordinate(this->position.x + this->padding.left, this->position.y + this->padding.top);
}

ELEMENTS::Cell::Cell(ELEMENTS::Cell::Mode mode, const std::string& placeholder, HELPER::Coordinate position, HELPER::Dimension dimension) {
	//* Default settings
	this->customFont = false;
	this->padding = ELEMENTS::Padding(10);
	this->textAlign = ELEMENTS::AlignmentOptions::LEFT;
	this->cursor = ELEMENTS::Cursor();
	this->active = false;
	this->fontSize = GLOBAL_VARIABLES::defaultTextSetting.charsize;
	this->fontStyle = GLOBAL_VARIABLES::defaultTextSetting.font;
	this->textColor = BLACK;
	this->backgroundColor = WHITE;
	this->characterLimit = placeholder.length();

	//* Argument settings
	this->mode = mode;
	this->placeholder = placeholder;
	this->position = position;
	this->dimension = dimension;

	//* Follow up settings
	this->fill = ELEMENTS::Fill(this->position, this->dimension.width, this->dimension.height);
	this->textPosition = HELPER::Coordinate(this->position.x + this->padding.left, this->position.y + this->padding.top);
}

void ELEMENTS::Cell::SetPosition(HELPER::Coordinate position) {
	this->position = position;
}

HELPER::Coordinate ELEMENTS::Cell::GetPosition() {
	return this->position;
}

bool ELEMENTS::Cell::SetDimension(HELPER::Dimension dimension) {
	if (dimension.width >= textDimension.width && dimension.height >= textDimension.height) {
		this->dimension = dimension;
		return true;
	}
	return false;
}

HELPER::Dimension ELEMENTS::Cell::GetDimension() {
	return this->dimension;
}

void ELEMENTS::Cell::SetPadding(ELEMENTS::Padding padding) {
	this->padding = padding;
}

ELEMENTS::Padding ELEMENTS::Cell::GetPadding() {
	return this->padding;
}

void ELEMENTS::Cell::SetTextAlign(ELEMENTS::AlignmentOptions align) {
	this->textAlign = align;
	this->UpdateAlignment();
}

ELEMENTS::AlignmentOptions ELEMENTS::Cell::GetTextAlign() {
	return this->textAlign;
}

void ELEMENTS::Cell::SetPlaceHolder(const std::string& placeholder) {
	this->placeholder = placeholder;
	this->UpdateTextDecoration();
	this->FitContent();
}

std::string ELEMENTS::Cell::GetPlaceholder() {
	return this->placeholder;
}

void ELEMENTS::Cell::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	this->customFont = true;
	this->FitContent();
}

int ELEMENTS::Cell::GetFontSize() {
	return this->fontSize;
}

void ELEMENTS::Cell::SetFontStyle(int fontStyle) {
	this->fontStyle = fontStyle;
	this->customFont = true;
	this->FitContent();
}

int ELEMENTS::Cell::GetFontStyle() {
	return this->fontStyle;
}

void ELEMENTS::Cell::SetTextColor(int color) {
	this->textColor = color;
	this->UpdateTextDecoration();
}

int ELEMENTS::Cell::GetTextColor() {
	return this->textColor;
}

void ELEMENTS::Cell::SetBackgroundColor(int color) {
	this->backgroundColor = color;
	this->fill.fillColor = this->backgroundColor;
}

int ELEMENTS::Cell::GetBackgroundColor() {
	return this->backgroundColor;
}

void ELEMENTS::Cell::SetCharacterLimit(int limit) {
	this->characterLimit = limit;
}

int ELEMENTS::Cell::GetCharacterLimit() {
	return this->characterLimit;
}

void ELEMENTS::Cell::SetStatus(bool status) {
	this->active = status;
}

bool ELEMENTS::Cell::GetStatus() {
	return this->active;
}

void ELEMENTS::Cell::SetTextPosition(HELPER::Coordinate position) {
	this->textPosition = position;
}

HELPER::Coordinate ELEMENTS::Cell::GetTextPosition() {
	return this->textPosition;
}

void ELEMENTS::Cell::Log() {
	std::clog << std::format("Position  : ");
	this->position.Log();
	std::clog << std::format("Dimension : [{} x {}]\n", this->dimension.width, this->dimension.height);
	std::clog << std::format("Text size : [{} x {}]\n", this->textDimension.width, this->textDimension.height);
	std::clog << std::format("Font size : {}\n", this->fontSize);
	std::clog << std::format("Font style: {}\n", this->fontStyle);
	std::clog << std::format("Status    : {}\n", this->active ? "Active" : "Inactive");
	std::clog << std::format("Cell mode : {}\n", this->mode == ELEMENTS::Cell::Mode::READ_MODE ? "READ" : "INPUT");
	std::clog << std::format("Text color: {}\n", this->textColor);
	std::clog << std::format("Alignment : {}\n", this->textAlign == ELEMENTS::AlignmentOptions::LEFT ? "LEFT" : this->textAlign == ELEMENTS::AlignmentOptions::CENTER ? "CENTER" : "RIGHT");
	std::clog << std::format("Coordinate: \n");
	this->fill.coordinates.Log();
	std::clog << std::format("Text posi : ");
	this->textPosition.Log();
}

bool ELEMENTS::Cell::ReadMode() {
	if (this->placeholder.length() > this->characterLimit) {
		std::cerr << std::format("[ERROR] Placeholder exceed character's limit!\n");
		return false;
	}

	if (this->active) {
		this->fill.fillColor = 12;
	}

	this->mode = ELEMENTS::Cell::Mode::READ_MODE;
	this->UpdateTextDecoration();
	this->UpdateAlignment();
	this->fill.Draw();
	moveto(this->textPosition.x, this->textPosition.y);
	outtext((char*)this->placeholder.c_str());

	return true;
}


