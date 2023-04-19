#pragma once

#include "../UI/Elements.h"

namespace LANDING_VIEW_STYLING {

	void GraphicalWindowDefaultProperties(ELEMENTS::Window*& win);

	void DefaultTabButtonProperties(Button& button);

	void CurrentActiveTabButtonProperties(Button& button);

	void CurrentButtonHoverProperties(Button& button);

	void ProgramTitleProperties(Button* btn);

	void DefaultCloseButtonProperties(ELEMENTS::CloseButton* btn);

	void CloseButtonHover(ELEMENTS::CloseButton* button);
}
