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
		this->leftClicked = true;
		this->active = true;
		return true;
	}
	return false;
}

bool ELEMENTS::Button::RightMouseClicked() {
	if (this->IsPointed() && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		this->leftClicked = true;
		return true;
	}
	return false;
}

ELEMENTS::TextBox::TextBox() {
	this->topLeft = this->bottomRight = HELPER::Coordinate();
	this->dimension = HELPER::Dimension();
	this->fill = ELEMENTS::Fill();
	this->textColor = WHITE;
	this->textStyle = DEFAULT_FONT;
	this->textSize = 0;
}

ELEMENTS::TextBox::TextBox(HELPER::Coordinate topLeft, int width, int height, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->dimension = { width, height };
	this->bottomRight = HELPER::Coordinate(topLeft.x + width, topLeft.y + height);
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->placeholder = "TEXT BOX";
	this->textStyle = DEFAULT_FONT;
	this->textSize = 0;
}

ELEMENTS::TextBox::TextBox(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor, int fillcolor, int borderColor) {
	this->topLeft = topLeft;
	this->bottomRight = bottomRight;
	this->dimension = { this->bottomRight.x - this->topLeft.x, this->bottomRight.y - this->topLeft.y };
	this->fill = ELEMENTS::Fill(this->topLeft, this->bottomRight, fillcolor, borderColor);
	this->textColor = textColor;
	this->placeholder = "TEXT BOX";
	this->textStyle = DEFAULT_FONT;
	this->textSize = 0;
}

void ELEMENTS::TextBox::SetFillColor(int color) {
	this->fill.fillColor = color;
}

int ELEMENTS::TextBox::GetFillColor() {
	return this->fill.fillColor;
}

void ELEMENTS::TextBox::SetTextColor(int color) {
	this->textColor = color;
}

int ELEMENTS::TextBox::GetTextColor() {
	return this->textColor;
}

void ELEMENTS::TextBox::SetBorderColor(int color) {
	this->fill.borderColor = color;
}

int ELEMENTS::TextBox::GetBorderColor() {
	return this->fill.borderColor;
}

void ELEMENTS::TextBox::SetTextSize(int size) {
	this->textSize = size;
}

int ELEMENTS::TextBox::GetTextSize() {
	return this->textSize;
}

void ELEMENTS::TextBox::SetTextStyle(int style) {
	this->textStyle = style;
}

int ELEMENTS::TextBox::GetTextStyle() {
	return this->textStyle;
}

void ELEMENTS::TextBox::SetPlaceholder(std::string placeholder) {
	this->placeholder = placeholder;
}

std::string ELEMENTS::TextBox::GetPlaceholder() {
	return this->placeholder;
}

void ELEMENTS::TextBox::Display() {
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
	//settextstyle(this->textStyle, HORIZ_DIR, this->textSize);
	outtextxy(textPosition.x, textPosition.y, (char*)this->placeholder.c_str());

	//settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
}

