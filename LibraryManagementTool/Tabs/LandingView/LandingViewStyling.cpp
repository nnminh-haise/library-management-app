#include "LandingViewStyling.h"

namespace LANDING_VIEW_STYLING {
	void GraphicalWindowDefaultProperties(ELEMENTS::Window*& win) {
		win->backgroundColor = WHITE;
	}

	void DefaultTabButtonProperties(ELEMENTS::Button& button) {
		button.SetFillColor(rgb(87, 108, 188));
		button.SetBorderColor(BLACK);
		button.SetTextColor(WHITE);
	}

	void CurrentActiveTabButtonProperties(ELEMENTS::Button& button) {
		button.SetFillColor(rgb(210, 218, 255));
		button.SetTextColor(BLACK);
	}

	void CurrentButtonHoverProperties(ELEMENTS::Button& button) {
		button.SetFillColor(rgb(83, 127, 231));
		button.SetTextColor(rgb(233, 248, 249));
	}

	void ProgramTitleProperties(ELEMENTS::Button* btn) {
		btn->SetFillColor(rgb(236, 242, 255));
		btn->SetBorderColor(btn->GetFillColor());
		btn->SetTextColor(rgb(46, 56, 64));
	}

	void DefaultCloseButtonProperties(ELEMENTS::CloseButton* btn) {
		btn->SetPlaceholder("X");
		btn->SetFillColor(rgb(206, 89, 89));
		btn->SetBorderColor(btn->GetFillColor());
	}

	void CloseButtonHover(ELEMENTS::CloseButton* button) {
		button->SetFillColor(rgb(255, 3, 3));
	}
}
