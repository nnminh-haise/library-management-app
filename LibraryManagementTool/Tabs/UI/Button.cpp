#include "Button.h"

Button::Button() {
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->fill = HELPER::Fill();
	this->dimension = HELPER::Dimension();
	this->textColor = BLACK;
	this->isPointed = false;
	this->placeholder = "BUTTON";
	this->inputMode = false;
	this->clickedCount = 0;
	this->leftClicked = false;
}

Button::Button(HELPER::Coordinate topLeft, int width, int height, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = { width, height };
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fill = HELPER::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->placeholder = "BUTTON";
	this->inputMode = false;
	this->clickedCount = 0;
	this->leftClicked = false;
}

Button::Button(HELPER::Coordinate topLeft, HELPER::Dimension dimension, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = dimension;
	this->bottomRight = HELPER::Coordinate(topLeft.x + this->dimension.width, topLeft.y + this->dimension.height);
	this->fill = HELPER::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->isPointed = false;
	this->placeholder = "BUTTON";
	this->inputMode = false;
	this->clickedCount = 0;
	this->leftClicked = false;
}

void Button::SetTopLeft(HELPER::Coordinate topLeft) {
	this->topLeft = topLeft;
	this->fill.topLeft = topLeft;
}

HELPER::Coordinate Button::GetTopLeft() {
	return this->topLeft;
}

void Button::SetDimension(HELPER::Dimension newDimension) {
	this->dimension = newDimension;
	this->fill.dimension = newDimension;
}

HELPER::Dimension Button::GetDimension() {
	return this->fill.dimension;
}

bool Button::UpdateWithNewTopLeft() {
	if (this->dimension.width == 0 && this->dimension.height == 0) {
		return false;
	}

	this->bottomRight.x = this->topLeft.x + this->dimension.width;
	this->bottomRight.y = this->topLeft.y + this->dimension.height;
	this->fill.bottomRight.x = this->topLeft.x + this->dimension.width;
	this->fill.bottomRight.y = this->topLeft.y + this->dimension.height;
	return true;
}

HELPER::Coordinate Button::GetBottomRight() {
	return this->bottomRight;
}

void Button::SetFillColor(int color) {
	this->fill.fillColor = color;
}

int Button::GetFillColor() {
	return this->fill.fillColor;
}

void Button::SetTextColor(int color) {
	this->textColor = color;
}

int Button::GetTextColor() {
	return this->textColor;
}

void Button::SetBorderColor(int color) {
	this->fill.borderColor = color;
}

int Button::GetBorderColor() {
	return this->fill.borderColor;
}

void Button::SetPlaceholder(std::string placeholder) {
	this->placeholder = placeholder;
}

std::string Button::GetPlaceholder() {
	return this->placeholder;
}

void Button::Activate() {
	this->active = true;
}

void Button::Deactivate() {
	this->active = false;
}

bool Button::IsActive() {
	return this->active == true;
}

void Button::Display() {
	HELPER::Dimension textDimension(
		textwidth((char*)this->placeholder.c_str()),
		textheight((char*)this->placeholder.c_str())
	);
	HELPER::Coordinate textPosition(
		this->topLeft.x + (this->dimension.width / 2 - textDimension.width / 2),
		this->topLeft.y + (this->dimension.height / 2 - textDimension.height / 2)
	);
	this->fill.Draw();
	setcolor(this->textColor);
	setbkcolor(this->fill.fillColor);
	outtextxy(textPosition.x, textPosition.y, (char*)this->placeholder.c_str());
}

bool Button::IsPointed() {
	HELPER::Coordinate currentMouse(HELPER::GetCurrentMouseCoordinate());
	if (this->topLeft.x <= currentMouse.x && this->topLeft.y <= currentMouse.y &&
		this->bottomRight.x >= currentMouse.x && this->bottomRight.y >= currentMouse.y) {
		this->isPointed = true;
		return true;
	}
	return false;
}

bool Button::IsHover() {
	return this->IsPointed() && this->LeftMouseClicked() == false && this->RightMouseClicked() == false;
}

bool Button::LeftMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
		this->leftClicked = true;
		return true;
	}
	return false;
}

bool Button::RightMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		this->clickedCount += 1;
		return true;
	}
	return false;
}
