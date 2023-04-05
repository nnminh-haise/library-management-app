#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "Elements.h"
#include "ExitView.h"
#include "DanhSachTheDocGia.h"
#include "DanhSachDauSachView.h"

#include <iostream>
#include <string>
#include <format>
#include <ctime>

void DefaultButtonProperties(ELEMENTS::Button& button) {
	button.SetFillColor(rgb(87, 108, 188));
	button.SetBorderColor(BLACK);
	button.SetTextColor(WHITE);
}

void FocusOnCurrentTab(ELEMENTS::Button& button) {
	button.SetFillColor(rgb(210, 218, 255));
	button.SetTextColor(BLACK);
}

void ButtonHover(ELEMENTS::Button& button) {
	button.SetFillColor(rgb(83, 127, 231));
	button.SetTextColor(rgb(233, 248, 249));
}

void ProgramTitleProperties(ELEMENTS::TextBox& box) {
	box.SetFillColor(rgb(236, 242, 255));
	box.SetBorderColor(box.GetFillColor());
	box.SetTextColor(rgb(46, 56, 64));
}

void DefaultCloseButtonProperties(ELEMENTS::CloseButton& btn) {
	btn.SetPlaceholder("X");
	btn.SetFillColor(rgb(206, 89, 89));
	btn.SetBorderColor(btn.GetFillColor());
}

void CloseButtonHover(ELEMENTS::CloseButton& button) {
	button.SetFillColor(rgb(255, 3, 3));
}

void LANDING_VIEW::Run(AVL_TREE::Pointer& danhSachTheDocGia) {

	ELEMENTS::Window programWindow(HELPER::Dimension(1800, 1000), "CHUONG TRINH QUAN LI THU VIEN - PTITHCM");
	programWindow.backgroundColor = WHITE;
	programWindow.Activate();

	//* Navigation bar setups
	ELEMENTS::Fill navigationBar(HELPER::Coordinate(0, 0), 1800, 100, rgb(11, 36, 71), rgb(11, 36, 71));

	//* Program name setups
	ELEMENTS::TextBox programnTitle(HELPER::Coordinate(36, 25), 440, 50);
	programnTitle.SetPlaceholder("Q U A N   L I   T H U   V I E N");
	ProgramTitleProperties(programnTitle);

	//* Button setups
	std::string placeholders[3]{ "DANH SACH DAU SACH", "DANH SACH THE DOC GIA", "THONG KE" };
	ELEMENTS::Button buttons[3]{
		ELEMENTS::Button(HELPER::Coordinate(640, 25), 300, 50),
		ELEMENTS::Button(HELPER::Coordinate(980, 25), 300, 50),
		ELEMENTS::Button(HELPER::Coordinate(1320, 25), 300, 50)
	};
	for (int i = 0; i < 3; ++i) {
		buttons[i].SetPlaceholder(placeholders[i]);
		DefaultButtonProperties(buttons[i]);
	}

	//* Close button
	ELEMENTS::CloseButton closeBtn(HELPER::Coordinate(1705, 25), 50, 50);
	DefaultCloseButtonProperties(closeBtn);

	int currentTab = 0;
	bool stopFlag = false;
	while (stopFlag == false) {

		//* Draw elements begin below
		setactivepage(1 - getactivepage());
		
		//* Draw elements
		programWindow.RenderBackground();
		navigationBar.Draw();
		programnTitle.Display();

		for (int i = 0; i < 3; ++i) {
			buttons[currentTab].SetStatus(true);
			FocusOnCurrentTab(buttons[currentTab]);
			buttons[i].Display();
		}
		closeBtn.Display();

		switch (currentTab) {
		case (0):
			DANH_SACH_DAU_SACH_VIEW::Run();
			break;
		case (1):
			DANH_SACH_THE_DOC_GIA_VIEW::Run(danhSachTheDocGia);
			break;
		case (2):
			break;
		}

		//* Update elements session
		for (int i = 0; i < 3; ++i) {
			if (i == currentTab && (buttons[i].IsPointed() || buttons[i].LeftMouseClicked())) {
				continue;
			}
			else if (i != currentTab) {
				if (buttons[i].IsPointed() && buttons[i].LeftMouseClicked() == false) {
					ButtonHover(buttons[i]);
				}
				else if (buttons[i].LeftMouseClicked()) {
					currentTab = i;
				}
				else {
					DefaultButtonProperties(buttons[i]);
				}
			}
		}

		if (closeBtn.IsPointed() && closeBtn.LeftMouseClicked() == false) {
			CloseButtonHover(closeBtn);
		}
		else if (closeBtn.LeftMouseClicked()) {
			stopFlag = true;
		}
		else {
			DefaultCloseButtonProperties(closeBtn);
		}
		

		setvisualpage(getactivepage());
		//* Draw elements end above

		//* Clear mouseclick
		clearmouseclick(VK_LBUTTON);
		clearmouseclick(VK_RBUTTON);
	}

	programWindow.Deactivate();
}
