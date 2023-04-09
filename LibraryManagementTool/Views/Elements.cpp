#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../Helper/Helper.h"

#include <iostream>
#include <string>
#include <format>
#include <thread>

ELEMENTS::Window::Window(const HELPER::Dimension& dimension, const std::string& title) {
	this->dimension = dimension;
	this->title = title;
	this->active = false;
	this->backgroundColor = WHITE;
}

int ELEMENTS::Window::Activate() {
	this->active = true;
	return initwindow(
		this->dimension.width, this->dimension.height, 
		(const char*)this->title.c_str(), 
		(getmaxwidth() - this->dimension.width) / 2, (getmaxheight() - this->dimension.height) / 2
	);
}

void ELEMENTS::Window::RenderBackground() {
	setfillstyle(SOLID_FILL, this->backgroundColor);
	bar(0, 0, this->dimension.width, this->dimension.height);
}

void ELEMENTS::Window::Deactivate() {
	this->active = false;
	closegraph();
}

ELEMENTS::Padding::Padding():
	top(0), bottom(0), left(0), right(0) {
}

ELEMENTS::Padding::Padding(int all):
	top(all), bottom(all), left(all), right(all) {
}

ELEMENTS::Padding::Padding(int top, int bottom, int left, int right):
	top(top), bottom(bottom), left(left), right(right) {
}

ELEMENTS::Fill::Fill():
	topLeft(HELPER::Coordinate()), bottomRight(HELPER::Coordinate()), dimension(HELPER::Dimension()),
	fillColor(WHITE), borderColor(WHITE) {
}

ELEMENTS::Fill::Fill(HELPER::Coordinate topLeft, int width, int height, int fillColor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension.width = width;
	this->dimension.height = height;
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fillColor = fillColor;
	this->borderColor = borderColor;
}

ELEMENTS::Fill::Fill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int fillColor, int borderColor) {
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->dimension.width = this->bottomRight.x - this->topLeft.x;
	this->dimension.height - this->bottomRight.y - this->topLeft.x;
	this->fillColor = fillColor;
	this->borderColor = borderColor;
}

ELEMENTS::Fill::Fill(int left, int top, int right, int bottom, int fillColor, int borderColor) {
	this->topLeft = { left, top };
	this->bottomRight = { right, bottom };
	this->dimension = { this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y };
	this->fillColor = fillColor;
	this->borderColor = borderColor;
}

void ELEMENTS::Fill::Draw() {
	setfillstyle(SOLID_FILL, this->fillColor);
	setcolor(borderColor);
	bar(this->topLeft.x, this->topLeft.y, this->bottomRight.x, this->bottomRight.y);
	rectangle(this->topLeft.x, this->topLeft.y, this->bottomRight.x, this->bottomRight.y);
}

ELEMENTS::CircleFill::CircleFill() :
	topLeft(HELPER::Coordinate()), bottomRight(HELPER::Coordinate()), dimension(HELPER::Dimension()),
	fillColor(WHITE), borderColor(WHITE) {
}

ELEMENTS::CircleFill::CircleFill(HELPER::Coordinate topLeft, int width, int height, int fillColor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension.width = width;
	this->dimension.height = height;
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fillColor = fillColor;
	this->borderColor = borderColor;
}

ELEMENTS::CircleFill::CircleFill(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int fillColor, int borderColor) {
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->dimension.width = this->bottomRight.x - this->topLeft.x;
	this->dimension.height - this->bottomRight.y - this->topLeft.x;
	this->fillColor = fillColor;
	this->borderColor = borderColor;
}

ELEMENTS::CircleFill::CircleFill(int left, int top, int right, int bottom, int fillColor, int borderColor) {
	this->topLeft = { left, top };
	this->bottomRight = { right, bottom };
	this->dimension = { this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y };
	this->fillColor = fillColor;
	this->borderColor = borderColor;
}

void ELEMENTS::CircleFill::Draw() {
	setfillstyle(SOLID_FILL, this->fillColor);
	setcolor(borderColor);
	fillellipse(this->topLeft.x + this->dimension.width / 2, this->topLeft.y + this->dimension.width / 2, 25, 25);
	circle(this->topLeft.x + this->dimension.width / 2, 50, 25);
}

ELEMENTS::CloseButton::CloseButton() {
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->fill = ELEMENTS::CircleFill();
	this->dimension = HELPER::Dimension();
	this->textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR;
	this->isPointed = false;
	this->rightClicked = false;
	this->leftClicked = false;
	this->placeholder = "BUTTON";
}

ELEMENTS::CloseButton::CloseButton(HELPER::Coordinate topLeft, int width, int height, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = { width, height };
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fill = ELEMENTS::CircleFill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "BUTTON";
}

ELEMENTS::CloseButton::CloseButton(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->dimension = { this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y };
	this->fill = ELEMENTS::CircleFill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "BUTTON";
}

void ELEMENTS::CloseButton::SetFillColor(int color) {
	this->fill.fillColor = color;
}

int ELEMENTS::CloseButton::GetFillColor() {
	return this->fill.fillColor;
}

void ELEMENTS::CloseButton::SetTextColor(int color) {
	this->textColor = color;
}

int ELEMENTS::CloseButton::GetTextColor() {
	return this->textColor;
}

void ELEMENTS::CloseButton::SetBorderColor(int color) {
	this->fill.borderColor = color;
}

int ELEMENTS::CloseButton::GetBorderColor() {
	return this->fill.borderColor;
}

void ELEMENTS::CloseButton::SetPlaceholder(std::string placeholder) {
	this->placeholder = placeholder;
}

std::string ELEMENTS::CloseButton::GetPlaceholder() {
	return this->placeholder;
}

void ELEMENTS::CloseButton::SetStatus(bool status) {
	this->active = status;
}

bool ELEMENTS::CloseButton::GetStatus() {
	return this->active;
}

void ELEMENTS::CloseButton::Display() {
	this->fill.Draw();
	setcolor(this->textColor);
	HELPER::Dimension textDimension(
		textwidth((char*)this->placeholder.c_str()),
		textheight((char*)this->placeholder.c_str())
	);
	HELPER::Coordinate textPosition(
		this->topLeft.x + (this->dimension.width / 2 - textDimension.width / 2),
		this->topLeft.y + (this->dimension.height / 2 - textDimension.height / 2)
	);
	setbkcolor(this->fill.fillColor);
	outtextxy(textPosition.x, textPosition.y, (char*)this->placeholder.c_str());
}

bool ELEMENTS::CloseButton::IsPointed() {
	HELPER::Coordinate currentMouse(HELPER::GetCurrentMouseCoordinate());
	if (this->topLeft.x <= currentMouse.x && this->topLeft.y <= currentMouse.y &&
		this->bottomRight.x >= currentMouse.x && this->bottomRight.y >= currentMouse.y) {
		this->isPointed = true;
		return true;
	}
	return false;
}

bool ELEMENTS::CloseButton::LeftMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		this->leftClicked = true;
		this->active = true;
		return true;
	}
	return false;
}

bool ELEMENTS::CloseButton::RightMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		this->leftClicked = true;
		return true;
	}
	return false;
}

ELEMENTS::Button::Button() {
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->fill = ELEMENTS::Fill();
	this->dimension = HELPER::Dimension();
	this->textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR;
	this->isPointed = false;
	this->rightClicked = false;
	this->leftClicked = false;
	this->placeholder = "BUTTON";
}

ELEMENTS::Button::Button(HELPER::Coordinate topLeft, int width, int height, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = { width, height };
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "BUTTON";
}

ELEMENTS::Button::Button(HELPER::Coordinate topLeft, HELPER::Dimension dimension, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = dimension;
	this->bottomRight = HELPER::Coordinate(topLeft.x + this->dimension.width, topLeft.y + this->dimension.height);
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "BUTTON";
}

ELEMENTS::Button::Button(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->dimension = {this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y};
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "BUTTON";
}

void ELEMENTS::Button::SetTopLeft(HELPER::Coordinate topLeft) {
	this->topLeft = topLeft;
	this->fill.topLeft = topLeft;
}

HELPER::Coordinate ELEMENTS::Button::GetTopLeft() {
	return this->topLeft;
}

void ELEMENTS::Button::SetDimension(HELPER::Dimension newDimension) {
	this->dimension = newDimension;
	this->fill.dimension = newDimension;
}

HELPER::Dimension ELEMENTS::Button::GetDimension() {
	return this->fill.dimension;
}

bool ELEMENTS::Button::UpdateWithNewTopLeft() {
	if (this->dimension.width == 0 && this->dimension.height == 0) {
		return false;
	}

	this->bottomRight.x = this->topLeft.x + this->dimension.width;
	this->bottomRight.y = this->topLeft.y + this->dimension.height;
	this->fill.bottomRight.x = this->topLeft.x + this->dimension.width;
	this->fill.bottomRight.y = this->topLeft.y + this->dimension.height;
	return true;
}

HELPER::Coordinate ELEMENTS::Button::GetBottomRight() {
	return this->bottomRight;
}

void ELEMENTS::Button::SetFillColor(int color) {
	this->fill.fillColor = color;
}

int ELEMENTS::Button::GetFillColor() {
	return this->fill.fillColor;
}

void ELEMENTS::Button::SetTextColor(int color) {
	this->textColor = color;
}

int ELEMENTS::Button::GetTextColor() {
	return this->textColor;
}

void ELEMENTS::Button::SetBorderColor(int color) {
	this->fill.borderColor = color;
}

int ELEMENTS::Button::GetBorderColor() {
	return this->fill.borderColor;
}

void ELEMENTS::Button::SetPlaceholder(std::string placeholder) {
	this->placeholder = placeholder;
}

std::string ELEMENTS::Button::GetPlaceholder() {
	return this->placeholder;
}

void ELEMENTS::Button::SetStatus(bool status) {
	this->active = status;
}

bool ELEMENTS::Button::GetStatus() {
	return this->active;
}

void ELEMENTS::Button::Display() {
	this->fill.Draw();
	setcolor(this->textColor);
	HELPER::Dimension textDimension(
		textwidth((char*)this->placeholder.c_str()),
		textheight((char*)this->placeholder.c_str())
	);
	HELPER::Coordinate textPosition(
		this->topLeft.x + (this->dimension.width / 2 - textDimension.width / 2), 
		this->topLeft.y + (this->dimension.height / 2 - textDimension.height / 2)
	);
	setbkcolor(this->fill.fillColor);
	outtextxy(textPosition.x, textPosition.y, (char*)this->placeholder.c_str());
}

bool ELEMENTS::Button::IsPointed() {
	HELPER::Coordinate currentMouse(HELPER::GetCurrentMouseCoordinate());
	if (this->topLeft.x <= currentMouse.x && this->topLeft.y <= currentMouse.y &&
		this->bottomRight.x >= currentMouse.x && this->bottomRight.y >= currentMouse.y) {
		this->isPointed = true;
		return true;
	}
	return false;
}

bool ELEMENTS::Button::LeftMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		this->SetLeftClicked();
		return true;
	}
	return false;
}

bool ELEMENTS::Button::RightMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		this->SetRightClicked();
		return true;
	}
	return false;
}

void ELEMENTS::Button::SetLeftClicked() {
	this->leftClicked = true;
}

void ELEMENTS::Button::SetRightClicked() {
	this->rightClicked = true;
}

void ELEMENTS::Button::ResetLeftClick() {
	this->leftClicked = false;
}

void ELEMENTS::Button::ResetRightClick() {
	this->rightClicked = false;
}

bool ELEMENTS::Button::GetLeftMouseStatus() {
	return this->leftClicked;
}

bool ELEMENTS::Button::GetRightMouseStatus() {
	return this->rightClicked;
}

ELEMENTS::InputBox::InputBox() {
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->fill = ELEMENTS::Fill();
	this->dimension = HELPER::Dimension();
	this->textColor = BUTTON_DEFAULT_PROPERTIES::TEXT_COLOR;
	this->isPointed = false;
	this->rightClicked = false;
	this->leftClicked = false;
	this->placeholder = "InputBox";
	this->inputMode = false;
}

ELEMENTS::InputBox::InputBox(HELPER::Coordinate topLeft, int width, int height, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = { width, height };
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "InputBox";
	this->inputMode = false;
}

ELEMENTS::InputBox::InputBox(HELPER::Coordinate topLeft, HELPER::Dimension dimension, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = dimension;
	this->bottomRight = HELPER::Coordinate(topLeft.x + this->dimension.width, topLeft.y + this->dimension.height);
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "InputBox";
	this->inputMode = false;
}

ELEMENTS::InputBox::InputBox(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->dimension = { this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y };
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->leftClicked = this->rightClicked = false;
	this->placeholder = "InputBox";
	this->inputMode = false;
}

void ELEMENTS::InputBox::SetTopLeft(HELPER::Coordinate topLeft) {
	this->topLeft = topLeft;
	this->fill.topLeft = topLeft;
}

HELPER::Coordinate ELEMENTS::InputBox::GetTopLeft() {
	return this->topLeft;
}

void ELEMENTS::InputBox::SetDimension(HELPER::Dimension newDimension) {
	this->dimension = newDimension;
	this->fill.dimension = newDimension;
}

HELPER::Dimension ELEMENTS::InputBox::GetDimension() {
	return this->fill.dimension;
}

bool ELEMENTS::InputBox::UpdateWithNewTopLeft() {
	if (this->dimension.width == 0 && this->dimension.height == 0) {
		return false;
	}

	this->bottomRight.x = this->topLeft.x + this->dimension.width;
	this->bottomRight.y = this->topLeft.y + this->dimension.height;
	this->fill.bottomRight.x = this->topLeft.x + this->dimension.width;
	this->fill.bottomRight.y = this->topLeft.y + this->dimension.height;
	return true;
}

HELPER::Coordinate ELEMENTS::InputBox::GetBottomRight() {
	return this->bottomRight;
}

void ELEMENTS::InputBox::SetFillColor(int color) {
	this->fill.fillColor = color;
}

int ELEMENTS::InputBox::GetFillColor() {
	return this->fill.fillColor;
}

void ELEMENTS::InputBox::SetTextColor(int color) {
	this->textColor = color;
}

int ELEMENTS::InputBox::GetTextColor() {
	return this->textColor;
}

void ELEMENTS::InputBox::SetBorderColor(int color) {
	this->fill.borderColor = color;
}

int ELEMENTS::InputBox::GetBorderColor() {
	return this->fill.borderColor;
}

void ELEMENTS::InputBox::SetPlaceholder(std::string placeholder) {
	this->placeholder = placeholder;
}

std::string ELEMENTS::InputBox::GetPlaceholder() {
	return this->placeholder;
}

void ELEMENTS::InputBox::SetStatus(bool status) {
	this->active = status;
}

bool ELEMENTS::InputBox::GetStatus() {
	return this->active;
}

bool ELEMENTS::InputBox::IsPointed() {
	HELPER::Coordinate currentMouse(HELPER::GetCurrentMouseCoordinate());
	if (this->topLeft.x <= currentMouse.x && this->topLeft.y <= currentMouse.y &&
		this->bottomRight.x >= currentMouse.x && this->bottomRight.y >= currentMouse.y) {
		this->isPointed = true;
		return true;
	}
	return false;
}

bool ELEMENTS::InputBox::LeftMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		this->SetLeftClicked();
		return true;
	}
	return false;
}

bool ELEMENTS::InputBox::RightMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		this->SetRightClicked();
		return true;
	}
	return false;
}

void ELEMENTS::InputBox::SetLeftClicked() {
	this->leftClicked = true;
}

void ELEMENTS::InputBox::SetRightClicked() {
	this->rightClicked = true;
}

void ELEMENTS::InputBox::ResetLeftClick() {
	this->leftClicked = false;
}

void ELEMENTS::InputBox::ResetRightClick() {
	this->rightClicked = false;
}

bool ELEMENTS::InputBox::GetLeftMouseStatus() {
	return this->leftClicked;
}

bool ELEMENTS::InputBox::GetRightMouseStatus() {
	return this->rightClicked;
}

std::string ELEMENTS::InputBox::InputMode(int characterLimit, bool(*KeyValidation)(const char&)) {

	this->fill.Draw();
	setcolor(this->textColor);
	setbkcolor(this->fill.fillColor);

	if (this->placeholder.length() != 0 && this->inputMode == true) {
		this->placeholder = "";
	}

	HELPER::Dimension textDimension(
		textwidth((char*)this->placeholder.c_str()),
		textheight((char*)this->placeholder.c_str())
	);
	HELPER::Coordinate textPosition(
		this->topLeft.x + (this->dimension.width / 2 - textDimension.width / 2),
		this->topLeft.y + (this->dimension.height / 2 - textDimension.height / 2)
	);
	
	if (this->inputMode == true) {
		int characterCount = 0;
		char inputKey{};

		while (inputKey != ELEMENTS::SpecialKey::ENTER && inputKey != ELEMENTS::SpecialKey::ESCAPE) {
			//std::cerr << "-------------------\n";
			//std::cerr << std::format("placeholder before: {}\n", this->placeholder);
			//textPosition.Log();
			//textDimension.Log();

			while (!kbhit()) {
				this->fill.Draw();
				std::cerr << this->placeholder << "\n";
				outtextxy(500, 345, (char*)"debuging");
				textPosition.Log();
				std::cerr << "bug: " << (char*)this->placeholder.c_str() << "\n";
				outtextxy(textPosition.x, textPosition.y, (char*)this->placeholder.c_str());
				bar(
					textPosition.x + textDimension.width, textPosition.y,
					textPosition.x + textDimension.width + 2, textPosition.y + textDimension.height
				);
			}

			std::cerr << "not debug\n";

			//std::cerr << std::format("{}, {}\n", textPosition.x + textDimension.width, textPosition.y);
			//std::cerr << std::format("{}, {}\n", textPosition.x + textDimension.width + 2, textPosition.y + textDimension.height);

			inputKey = toupper(getch());

			std::cerr << std::format("pressed key: {}\n", inputKey);
			

			//* If the pressed key is the ENTER key or ESCAPE key, then stop the input process and return the result string.
			if (inputKey == ELEMENTS::SpecialKey::ENTER || inputKey == ELEMENTS::SpecialKey::ESCAPE) {
				continue;
			}

			//* Filter out the case where there are more than two SPACE in the string.
			if (this->placeholder.length() != 0 && this->placeholder[this->placeholder.length() - 1] == ' ' && inputKey == ELEMENTS::SpecialKey::SPACE) {
				continue;
			}

			//* Filter out the case where the first pressed key is SPACE.
			if (this->placeholder.length() == 0 && inputKey == ELEMENTS::SpecialKey::SPACE) {
				continue;
			}

			if (characterCount + 1 < characterLimit && KeyValidation(inputKey)) {
				this->placeholder += inputKey;
				++characterCount;
				textDimension.width = textwidth((char*)this->placeholder.c_str());
			}

			std::cerr << std::format("placeholder after: {}\n", this->placeholder);
		}
	}
	else {
		outtextxy(textPosition.x, textPosition.y, (char*)this->placeholder.c_str());
	}


	return STR::Trim(this->placeholder);
}

void ELEMENTS::InputBox::ActivateInputMode() {
	this->inputMode = true;
}

void ELEMENTS::InputBox::DeactivateInputMode() {
	this->inputMode = false;
}

bool ELEMENTS::InputBox::InInputMode() {
	return this->inputMode;
}

DATASHEET::Row::Row() {
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->labels = nullptr;
	this->labelPlaceholders = nullptr;
	this->characterLimits = nullptr;
	this->columnCount = 0;
	this->rowHeight = 0;
}

DATASHEET::Row::Row(int columnCount, HELPER::Coordinate topLeft, std::string* labelPlaceholders, int* characterLimits, int rowHeight) {
	this->columnCount = columnCount;
	this->topLeft = topLeft;
	this->labelPlaceholders = labelPlaceholders;
	this->characterLimits = characterLimits;
	this->rowHeight = rowHeight;

	ELEMENTS::Padding padding(10);
	this->labels = new ELEMENTS::Button[this->columnCount];
	HELPER::Dimension boxDimension;
	for (int i = 0; i < this->columnCount; ++i) {
		boxDimension.width = max(textwidth((char*)this->labelPlaceholders[i].c_str()), textwidth((char*)"W") * this->characterLimits[i]) + padding.left + padding.right;
		boxDimension.height = this->rowHeight;
		if (i == 0) {
			this->labels[i].SetTopLeft(this->topLeft);
		}
		else {
			this->labels[i].SetTopLeft(HELPER::Coordinate(this->labels[i - 1].GetTopLeft().x + this->labels[i - 1].GetDimension().width, this->labels[i - 1].GetTopLeft().y));
		}
		this->labels[i].SetDimension(boxDimension);
		this->labels[i].UpdateWithNewTopLeft();
		this->labels[i].SetPlaceholder(this->labelPlaceholders[i]);
	}
	this->bottomRight = this->labels[columnCount - 1].GetBottomRight();
}

void DATASHEET::Row::SetPlaceHolder(std::string* labelPlaceholders) {
	this->labelPlaceholders = labelPlaceholders;
	for (int i = 0; i < this->columnCount; ++i) {
		this->labels[i].SetPlaceholder(this->labelPlaceholders[i]);
	}
}

void DATASHEET::Row::Display() {
	for (int i = 0; i < this->columnCount; ++i) {
		this->labels[i].Display();
	}
}

void DATASHEET::Datasheet::DefaultLabelsProperties(DATASHEET::Row& field) {
	for (int i = 0; i < field.columnCount; ++i) {
		field.labels[i].SetFillColor(rgb(210, 218, 255));
		field.labels[i].SetBorderColor(rgb(25, 24, 37));
		field.labels[i].SetTextColor(rgb(25, 24, 37));
	}
}

void DATASHEET::Datasheet::DefaultDataFieldProperties(DATASHEET::Row& field, int order) {
	for (int i = 0; i < field.columnCount; ++i) {
		if (order % 2 != 0) {
			field.labels[i].SetFillColor(rgb(255, 251, 245));
		}
		else {
			field.labels[i].SetFillColor(rgb(238, 238, 238));
		}
		field.labels[i].SetBorderColor(rgb(25, 24, 37));
		field.labels[i].SetTextColor(rgb(25, 24, 37));
	}
}

DATASHEET::Datasheet::Datasheet() {
	this->rowCount = this->columnCount = 0;
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->labelPlaceholders = nullptr;
	this->characterLimits = nullptr;
	this->rows = nullptr;
	this->rowHeight = 0;
}

DATASHEET::Datasheet::Datasheet(int rowCount, int columnCount, int rowHeight, HELPER::Coordinate topLeft, std::string* labelPlaceholders, int* characterLimits) {
	//* Assign parameterized field
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	this->topLeft = topLeft;
	this->labelPlaceholders = labelPlaceholders;
	this->characterLimits = characterLimits;
	this->rowHeight = rowHeight;

	//* Some references for easy coding
	std::string* defaultData = new std::string[this->columnCount];
	for (int i = 0; i < this->columnCount; ++i) {
		defaultData[i] = "...";
	}

	//* Create Datasheet logic
	this->rows = new DATASHEET::Row[this->rowCount];
	for (int i = 0; i < this->rowCount; ++i) {
		DATASHEET::Row& currentRow = this->rows[i];

		if (i == 0) {//* Create labels
			currentRow = DATASHEET::Row(this->columnCount, this->topLeft, this->labelPlaceholders, this->characterLimits, this->rowHeight);
			currentRow.SetPlaceHolder(this->labelPlaceholders);
			DATASHEET::Datasheet::DefaultLabelsProperties(currentRow);
		}
		else {//* Create data's field
			currentRow = DATASHEET::Row(this->columnCount,
				HELPER::Coordinate(this->rows[i - 1].topLeft.x, this->rows[i - 1].bottomRight.y),
				this->labelPlaceholders, this->characterLimits,
				this->rowHeight
			);
			currentRow.SetPlaceHolder(defaultData);
			DATASHEET::Datasheet::DefaultDataFieldProperties(currentRow, i);
		}
	}

	delete[this->columnCount] defaultData;
}

void DATASHEET::Datasheet::UpdateNewPlaceholder(std::string* newPlaceholder, int rowIndicator) {
	if (rowIndicator <= 0 || rowIndicator >= CONSTANTS::MAX_ROW_COUNT) {
		return;
	}

	for (int i = 0; i < this->columnCount; ++i) {
		this->rows[rowIndicator].labels[i].SetPlaceholder(newPlaceholder[i]);
	}
}

void DATASHEET::Datasheet::Display() {
	for (int i = 0; i < this->rowCount; ++i) {
		this->rows[i].Display();
	}
}

DATASHEET::Controler::Controler() {
	this->datasheetCount = 0;
	this->sheets = nullptr;
	this->activeSheet = -1;
	this->columnCount = 0;
	this->rowCount = 0;
	this->rowHeight = 0;
}

DATASHEET::Controler::Controler(int rowCount, int columnCount, int rowHeight, HELPER::Coordinate topLeft) {
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	this->rowHeight = rowHeight;
	this->topLeft = topLeft;

	this->datasheetCount = 0;
	this->sheets = nullptr;
	this->activeSheet = -1;
}

DATASHEET::Controler::~Controler() {
	delete[this->datasheetCount] this->sheets;
}

void DATASHEET::Controler::UpdateActiveSheet(int indicator) {
	if (indicator < 0 || indicator >= this->datasheetCount) {
		return;
	}
	this->activeSheet = indicator;
}

void DATASHEET::Controler::Display() {
	//std::cerr << std::format("[INFO] CURRENT ACTIVE SHEET: {}\n", this->activeSheet);
	this->sheets[this->activeSheet].Display();
}
