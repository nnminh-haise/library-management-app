#include "Elements.h"
#include "../../Graphics/graphics.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../Helper/Helper.h"

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

//---

ELEMENTS::Padding::Padding():
	top(0), bottom(0), left(0), right(0) {
}

ELEMENTS::Padding::Padding(int all):
	top(all), bottom(all), left(all), right(all) {
}

ELEMENTS::Padding::Padding(int top, int bottom, int left, int right):
	top(top), bottom(bottom), left(left), right(right) {
}

//---

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

//---

ELEMENTS::InputModeController::InputModeController() {
	this->inputMode = false;
	this->acceptKey = false;
	this->characterCount = 0;
	this->characterLimit = 0;
	this->currentTextBox = nullptr;
	this->outputTextBox = nullptr;
	this->inputKey = NULL;
	this->inputString = "";
}

void ELEMENTS::InputModeController::Activate(Button* inputTextBox, Button* outputTextBox, int characterLimit, bool acceptAlpha, bool acceptNum, bool acceptSpace) {
	this->inputMode = true;
	this->acceptKey = true;
	this->characterCount = 0;
	this->characterLimit = characterLimit;
	this->currentTextBox = inputTextBox;
	this->outputTextBox = outputTextBox;
	this->inputKey = NULL;
	this->inputString = "";

	this->acceptAlpha = acceptAlpha;
	this->acceptNum = acceptNum;
	this->acceptSpace = acceptSpace;

	this->currentTextBox->SetPlaceholder("");
}

void ELEMENTS::InputModeController::Deactivate() {
	this->inputMode = false;
	this->acceptKey = false;
	this->characterCount = 0;
	this->characterLimit = 0;
	this->currentTextBox = nullptr;
	this->outputTextBox = nullptr;
	this->inputKey = NULL;
	this->inputString = "";
}

std::string ELEMENTS::InputModeController::GetInputString() {
	return this->inputString;
}

bool ELEMENTS::InputModeController::InInputMode() {
	return this->inputMode == true;
}

bool ELEMENTS::InputModeController::KeyValidation(const char& chr) {
	if (this->acceptSpace == false && chr == ELEMENTS::SpecialKey::SPACE) {
		return false;
	}

	if (this->acceptNum == false && isdigit(chr)) {
		return false;
	}

	if (this->acceptAlpha == false && isalpha(chr)) {
		return false;
	}

	return true;
}

void ELEMENTS::InputModeController::ActionOnKey(const char& chr) {
	if (chr == ELEMENTS::SpecialKey::ENTER || chr == ELEMENTS::SpecialKey::ESCAPE) {
		if (this->outputTextBox != nullptr) {
			this->outputTextBox->SetPlaceholder(this->inputString);
		}
		this->Deactivate();
	}
	else if (this->inputString.length() == 0 && chr == ' ') {
		return;
	}
	else if (this->inputString.length() != 0 && this->inputString[this->inputString.length() - 1] == ' ' && chr == ' ') {
		return;
	}
	else if (this->inputString.length() == 0 && chr == ELEMENTS::SpecialKey::BACKSPACE) {
		return;
	}
	else if (chr == ELEMENTS::SpecialKey::BACKSPACE) {
		this->inputString.pop_back();
		this->characterCount--;
		this->currentTextBox->SetPlaceholder(this->inputString);
	}
	else if (this->characterCount < this->characterLimit && this->KeyValidation(chr)) {
		this->inputString.push_back(chr);
		++this->characterCount;
		this->currentTextBox->SetPlaceholder(this->inputString);
	}
}

//---

