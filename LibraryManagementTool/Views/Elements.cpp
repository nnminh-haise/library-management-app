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
	this->borderColor = this->fillColor;
}

ELEMENTS::Fill::Fill(HELPER::Coordinate position, int width, int height) {
	this->position = position;
	this->dimension = HELPER::Dimension(width, height);
	this->coordinates = HELPER::Rectangle(position, width, height);
	this->fillColor = WHITE;
	this->borderColor = this->fillColor;
}

ELEMENTS::Fill::Fill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight) {
	this->position = topLeft;
	this->coordinates = HELPER::Rectangle(topLeft, bottomRight);
	this->dimension = this->coordinates.dimension;
	this->fillColor = WHITE;
	this->borderColor = this->fillColor;
}

void ELEMENTS::Fill::Draw() {
	setfillstyle(SOLID_FILL, this->fillColor);
	setbkcolor(fillColor);
	setcolor(borderColor);
	bar(this->coordinates.topLeft.x, this->coordinates.topLeft.y, this->coordinates.bottomRight.x, this->coordinates.bottomRight.y);
	rectangle(this->coordinates.topLeft.x, this->coordinates.topLeft.y, this->coordinates.bottomRight.x, this->coordinates.bottomRight.y);
}

void ELEMENTS::Fill::SetFillColor(int color) {
	this->fillColor = color;
	this->borderColor = this->fillColor;
}

int ELEMENTS::Fill::GetFillColor() {
	return this->fillColor;
}

void ELEMENTS::Fill::SetBorderColor(int color) {
	this->borderColor = color;
}

int ELEMENTS::Fill::GetBorderColor() {
	return this->borderColor;
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
	
	//* As a fit content option, the cell's dimension is equal to the sum of the text's dimension + the padding option.
	this->dimension.width = this->padding.left + this->padding.right + this->textDimension.width;
	this->dimension.height = this->padding.top + this->padding.bottom + this->textDimension.height;
	return true;
}

void ELEMENTS::Cell::UpdateAlignment() {
	this->UpdateTextDecoration();
	int remainWidth = this->dimension.width - this->padding.left - this->padding.right - this->textDimension.width;
	int remainHeight = this->dimension.height - this->padding.top - this->padding.bottom - this->textDimension.height;

	switch (this->horizontalAlign) {
		case (ELEMENTS::Align::LEFT): {
			this->textPosition.x = this->position.x + this->padding.left;
			break;
		}
		case (ELEMENTS::Align::CENTER): {
			this->textPosition.x = this->position.x + this->padding.left + remainWidth / 2;
			break;
		}
		case (ELEMENTS::Align::RIGHT): {
			this->textPosition.x = this->position.x + this->padding.left + remainWidth;
			break;
		}
	}

	switch (this->verticalAlign) {
		case (ELEMENTS::Align::MIDDLE): {
			this->textPosition.y = this->position.y + this->padding.top + remainHeight / 2;
			break;
		}
		case (ELEMENTS::Align::TOP): {
			this->textPosition.y = this->position.y + this->padding.top;
			break;
		}
		case (ELEMENTS::Align::BOTTOM): {
			this->textPosition.y = this->position.y + this->padding.top + remainHeight;
			break;
		}
	}
}

bool ELEMENTS::Cell::ValidDimension() {
	if (this->dimension.width < this->padding.left + this->padding.right + this->textDimension.width) {
		return false;
	}
	
	if (this->dimension.height < this->padding.top + this->padding.bottom + this->textDimension.height) {
		return false;
	}

	return true;
}

ELEMENTS::Cell::Cell() {
	this->position = HELPER::Coordinate();
	this->dimension = HELPER::Dimension();
	this->textPosition = HELPER::Coordinate();
	this->textDimension = HELPER::Dimension();
	this->padding = ELEMENTS::Padding();
	this->fill = ELEMENTS::Fill();
	this->horizontalAlign = ELEMENTS::Align::LEFT;
	this->verticalAlign = ELEMENTS::Align::MIDDLE;
	this->cursor = ELEMENTS::Cursor();
	this->mode = ELEMENTS::Cell::Mode::READ_MODE;
	this->active = false;
	this->fontSize = GLOBAL_VARIABLES::defaultTextSetting.charsize;
	this->fontStyle = GLOBAL_VARIABLES::defaultTextSetting.font;
	this->textColor = BLACK;
	this->fill.SetFillColor(WHITE);
	this->characterLimit = -1;
	this->customFont = false;
}

/*
* This constructor will be automatically change to content fit dimension.
* Which means that the cell's dimension will equal to the text's dimension plus the padding of the cell which is 10px
*/
ELEMENTS::Cell::Cell(ELEMENTS::Cell::Mode mode, const std::string& placeholder, HELPER::Coordinate position, int width, int height, int characterLimit) {
	//* Default settings
	this->customFont = false;
	this->padding = ELEMENTS::Padding(10);
	this->horizontalAlign = ELEMENTS::Align::LEFT;
	this->verticalAlign = ELEMENTS::Align::MIDDLE;
	this->cursor = ELEMENTS::Cursor();
	this->active = false;
	this->fontSize = GLOBAL_VARIABLES::defaultTextSetting.charsize;
	this->fontStyle = GLOBAL_VARIABLES::defaultTextSetting.font;
	this->textColor = BLACK;
	this->fill.SetFillColor(WHITE);
	this->characterLimit = characterLimit;

	//* Argument settings
	this->mode = mode;
	this->placeholder = placeholder;
	this->position = position;

	/**
	* Firstly, the cell will be automatically in content fit mode.
	* Next the given width and height will be check.
	* If any of them are greater the fit content mode's dimension then the relating dimension will be updated.
	*/
	this->FitContent();
	if (width == -1) {
		this->dimension.width = max(textwidth((char*)"W") * this->characterLimit, textwidth((char*)"W") * this->placeholder.length());
	}
	else if (width > this->dimension.width) {
		this->dimension.width = width;
	}
	if (height == -1) {
		this->dimension.height = max(textheight((char*)"W") * this->characterLimit, textheight((char*)"W") * this->placeholder.length());
	}
	else if (height > this->dimension.height) {
		this->dimension.height = height;
	}

	//* Follow up settings
	this->fill = ELEMENTS::Fill(this->position, this->dimension.width, this->dimension.height);
	this->UpdateAlignment();
}

ELEMENTS::Cell::Cell(ELEMENTS::Cell::Mode mode, const std::string& placeholder, HELPER::Coordinate position, HELPER::Dimension dimension, int characterLimit) {
	//* Default settings
	this->customFont = false;
	this->padding = ELEMENTS::Padding(10);
	this->horizontalAlign = ELEMENTS::Align::LEFT;
	this->verticalAlign = ELEMENTS::Align::MIDDLE;
	this->cursor = ELEMENTS::Cursor();
	this->active = false;
	this->fontSize = GLOBAL_VARIABLES::defaultTextSetting.charsize;
	this->fontStyle = GLOBAL_VARIABLES::defaultTextSetting.font;
	this->textColor = BLACK;
	this->fill.SetFillColor(WHITE);
	this->characterLimit = characterLimit;

	//* Argument settings
	this->mode = mode;
	this->placeholder = placeholder;
	this->position = position;
	this->dimension = dimension;

	//* Follow up settings
	this->fill = ELEMENTS::Fill(this->position, this->dimension.width, this->dimension.height);
	this->UpdateTextDecoration();
	this->UpdateAlignment();
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

void ELEMENTS::Cell::SetHorizontalAlign(ELEMENTS::Align align) {
	this->horizontalAlign = align;
	this->UpdateAlignment();
}

ELEMENTS::Align ELEMENTS::Cell::GetHorizontalAlign() {
	return this->horizontalAlign;
}

void ELEMENTS::Cell::SetVerticalAlign(ELEMENTS::Align align) {
	this->verticalAlign = align;
	this->UpdateAlignment();
}

ELEMENTS::Align ELEMENTS::Cell::GetVerticalAlign() {
	return this->verticalAlign;
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
	this->fill.SetFillColor(color);
}

int ELEMENTS::Cell::GetBackgroundColor() {
	return this->fill.GetFillColor();
}

void ELEMENTS::Cell::SetBorderColor(int color) {
	this->fill.SetBorderColor(color);
}

int ELEMENTS::Cell::GetBorderColor() {
	return this->fill.GetBorderColor();
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
	std::clog << std::format("Alignment : {}\n", this->horizontalAlign == ELEMENTS::Align::LEFT ? "LEFT" : this->horizontalAlign == ELEMENTS::Align::CENTER ? "CENTER" : "RIGHT");
	std::clog << std::format("Coordinate: \n");
	this->fill.coordinates.Log();
	std::clog << std::format("Text posi : ");
	this->textPosition.Log();
}

bool ELEMENTS::Cell::LoadContent(const std::string& content) {
	if ((int)content.length() > this->characterLimit) {
		std::cerr << "[ERROR] Content too long!\n";
		return false;
	}
	
	if (this->padding.left + this->padding.right + textwidth((char*)content.c_str()) > this->dimension.width) {
		std::cerr << "[ERROR] Cannot fit content to cell!\n";
		return false;
	}

	this->placeholder = content;
	return true;
}

bool ELEMENTS::Cell::ReadMode() {
	if (this->active) {
		this->fill.SetFillColor(12);
	}

	this->mode = ELEMENTS::Cell::Mode::READ_MODE;
	this->fill.Draw();
	this->UpdateTextDecoration();
	this->UpdateAlignment();
	outtextxy(this->textPosition.x, this->textPosition.y, (char*)this->placeholder.c_str());
	return true;
}

std::string ELEMENTS::Cell::InputMode(bool(*validInput)(std::string), bool(*validKey)(char)) {
	//* Draw background
	this->fill.Draw();

	//* Update text settings and change the text's position to the left and middle.
	this->UpdateTextDecoration();

	/**
	* Create a string to hold the user's input string.
	* We will control the coordinate of the graphical string which get drown onto the graphic window.
	* We will animated a blinking cursor at the end of the input field. Therefore we need to get 
	* control over the coordinate of the input field which is the coordinate of the output text to
	* the graphic window.
	*/
	std::string resultString{};
	const unsigned int characterWidth = textwidth((char*)"W");
	const unsigned int characterHeight = textheight((char*)"W");
	int remainHeight = this->dimension.height - characterHeight - this->padding.top - this->padding.bottom;
	HELPER::Coordinate topLeft(this->position.x + this->padding.left, this->position.y + this->padding.top + remainHeight / 2);
	HELPER::Coordinate bottomRight = topLeft;

	//* Draw loop, each loop will be a frame.
	char inputKey{};
	bool inputLoopStopFlag = false;
	do {
		this->fill.Draw();
		outtextxy(topLeft.x, topLeft.y, (char*)resultString.c_str());

		inputKey = std::toupper(getch());

		//* Control logic
		switch (inputKey) {
			//* When ESCAPE key is pressed, the operation will stop and return an empty string.
			case (ELEMENTS::SpecialKey::ESCAPE): {
				return std::string();
			}

			//* When ENTER key is pressed, the operation will stop and return the input string.
			case (ELEMENTS::SpecialKey::ENTER): {
				inputLoopStopFlag = true;
				break;
			}

			//* When BACKSPACE is pressed, the will remove the latest input key get input by the user.
			case (ELEMENTS::SpecialKey::BACKSPACE): {
				if (resultString.length() > 0) {
					bottomRight.x -= textwidth(&resultString[resultString.length() - 1]);
					resultString.pop_back();
					bar(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
				}
				break;
			}
		}

		/**
		* We only accept a character if that character is valid and the number of valid character does not exceed the character limit of the cell.
		*/
		bool inputKeyValidationResult = validKey(inputKey);
		if (inputKeyValidationResult == true && resultString.length() < this->characterLimit) {
			resultString.push_back(inputKey);
			bottomRight.x += textwidth(&inputKey);
		}

	} while (inputLoopStopFlag == false);

	return resultString;
}


