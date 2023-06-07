#pragma once

#ifndef VIEW
#define VIEW

#include "Button.h"

class View
{
public:
	void Activate();

	void Deactivate();

	bool InActive();

	bool GoBackButtonOnAction();

	void Clear();

	virtual int Run() = 0;

public:
	bool status_ = false;

	Button goBackButton_{ {0, 0}, {70, 40}, BLACK, rgb(236,242,255), BLACK };
};

struct LinkedButton
{
	LinkedButton();

	void Display(int index = -1);

	Button description_{ {0, 0}, {0, 0}, BLACK, WHITE, WHITE };
	Button content_{ {0, 0}, {0, 0}, BLACK, WHITE, BLACK };

	bool status_ = true;
};

#endif // !VIEW
