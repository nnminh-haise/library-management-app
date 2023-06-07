#include "Component.hpp"

void View::Activate()
{
	this->status_ = true;
}

void View::Deactivate()
{
	this->status_ = false;
}

bool View::InActive()
{
	return this->status_;
}

bool View::GoBackButtonOnAction()
{
	if (!this->status_) { return false; }

	if (this->goBackButton_.IsHover())
	{
		this->goBackButton_.SetTextColor(WHITE);
		this->goBackButton_.SetFillColor(rgb(130, 170, 227));
	}
	else if (this->goBackButton_.LeftMouseClicked())
	{
		delay(100);
		return true;
	}
	else
	{
		this->goBackButton_.SetTextColor(BLACK);
		this->goBackButton_.SetFillColor(rgb(236, 242, 255));
	}

	return false;
}

void View::Clear()
{
}

LinkedButton::LinkedButton()
{
}

void LinkedButton::Display(int index)
{
	if (!this->status_) { return; }

	if (index == -1)
	{
		this->description_.Display();
		this->content_.Display();
	}
	else if (index == 1)
	{
		this->description_.Display();
	}
	else if (index == 2)
	{
		this->content_.Display();
	}
}
