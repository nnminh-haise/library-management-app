#pragma once

#include "../UI/Elements.h"

namespace LANDING_VIEW_STYLING {

	void GraphicalWindowDefaultProperties(ELEMENTS::Window*& win);

	void DefaultTabButtonProperties(ELEMENTS::Button& button);

	void CurrentActiveTabButtonProperties(ELEMENTS::Button& button);

	void CurrentButtonHoverProperties(ELEMENTS::Button& button);

	void ProgramTitleProperties(ELEMENTS::Button* btn);

	void DefaultCloseButtonProperties(ELEMENTS::CloseButton* btn);

	void CloseButtonHover(ELEMENTS::CloseButton* button);
}
