#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"

#include <iostream>
#include <string>
#include <format>
#include <ctime>

void LandingView::GraphicalWindowDefaultProperties(ELEMENTS::Window*& win) {
	win->backgroundColor = WHITE;
}

void LandingView::DefaultButtonProperties(ELEMENTS::Button& button) {
	button.SetFillColor(rgb(87, 108, 188));
	button.SetBorderColor(BLACK);
	button.SetTextColor(WHITE);
}

void LandingView::FocusOnCurrentTab(ELEMENTS::Button& button) {
	button.SetFillColor(rgb(210, 218, 255));
	button.SetTextColor(BLACK);
}

void LandingView::ButtonHover(ELEMENTS::Button& button) {
	button.SetFillColor(rgb(83, 127, 231));
	button.SetTextColor(rgb(233, 248, 249));
}

void LandingView::ProgramTitleProperties(ELEMENTS::Button*& btn) {
	btn->SetFillColor(rgb(236, 242, 255));
	btn->SetBorderColor(btn->GetFillColor());
	btn->SetTextColor(rgb(46, 56, 64));
}

void LandingView::DefaultCloseButtonProperties(ELEMENTS::CloseButton*& btn) {
	btn->SetPlaceholder("X");
	btn->SetFillColor(rgb(206, 89, 89));
	btn->SetBorderColor(btn->GetFillColor());
}

void LandingView::CloseButtonHover(ELEMENTS::CloseButton*& button) {
	button->SetFillColor(rgb(255, 3, 3));
}

LandingView::LandingView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach) {
	
	//* Initializations
	this->graphicalWindow = new ELEMENTS::Window(CONSTANTS::WINDOW_DIMENSION, (std::string)CONSTANTS::WINDOW_TITLE);
	this->GraphicalWindowDefaultProperties(this->graphicalWindow);

	//* Program elements initialize
	this->graphicalWindow->Activate();
	this->programTitle = new ELEMENTS::Button(HELPER::Coordinate(36, 25), 440, 50);
	this->programTitle->SetPlaceholder("Q U A N   L I   T H U   V I E N");
	this->ProgramTitleProperties(this->programTitle);

	//* Tabs setup
	std::string tabPlaceholders[3]{ "DANH SACH DAU SACH", "DANH SACH THE DOC GIA", "THONG KE" };
	HELPER::Coordinate tabCoordinates[3]{
		HELPER::Coordinate(640, 25),
		HELPER::Coordinate(980, 25),
		HELPER::Coordinate(1320, 25)
	};
	HELPER::Dimension tabDimension(300, 50);

	this->tabs = new ELEMENTS::Button[3];
	for (int i = 0; i < 3; ++i) {
		this->tabs[i] = ELEMENTS::Button(tabCoordinates[i], tabDimension);
		this->tabs[i].SetPlaceholder(tabPlaceholders[i]);
		this->DefaultButtonProperties(this->tabs[i]);
	}

	//* Close button setup
	this->closeBtn = new ELEMENTS::CloseButton(HELPER::Coordinate(1705, 25), 50, 50);
	this->DefaultCloseButtonProperties(this->closeBtn);

	//* Views setup
	this->dauSachView = new DanhSachDauSachView(dsDauSach);
	this->theDocGiaView = new DanhSachTheDocGiaView(dsTheDocGia);
	this->thongKeView = new ThongKeView(dsTheDocGia, dsDauSach);
}

void LandingView::Run() {
	//* Navigation bar setup
	ELEMENTS::Fill navigationBar(HELPER::Coordinate(0, 0), 1800, 100, rgb(11, 36, 71), rgb(11, 36, 71));

	int currentTab = 0;
	bool stopFlag = false;
	while (stopFlag == false) {

		//* Draw elements begin below
		setactivepage(1 - getactivepage());

		//* Draw elements
		this->graphicalWindow->RenderBackground();
		navigationBar.Draw();
		this->programTitle->Display();

		for (int i = 0; i < 3; ++i) {
			this->tabs[currentTab].SetStatus(true);
			this->FocusOnCurrentTab(this->tabs[currentTab]);
			this->tabs[i].Display();
		}
		this->closeBtn->Display();

		switch (currentTab) {
		case (0):
			this->dauSachView->Run();
			break;
		case (1):
			this->theDocGiaView->Run();
			break;
		case (2):
			this->thongKeView->Run();
			break;
		}

		//* Update elements session
		for (int i = 0; i < 3; ++i) {
			if (i == currentTab && (this->tabs[i].IsPointed() || this->tabs[i].LeftMouseClicked())) {
				continue;
			}
			else if (i != currentTab) {
				if (this->tabs[i].IsPointed() && this->tabs[i].LeftMouseClicked() == false) {
					this->ButtonHover(this->tabs[i]);
				}
				else if (this->tabs[i].LeftMouseClicked()) {
					currentTab = i;
				}
				else {
					DefaultButtonProperties(this->tabs[i]);
				}
			}
		}

		if (this->closeBtn->IsPointed() && this->closeBtn->LeftMouseClicked() == false) {
			this->CloseButtonHover(this->closeBtn);
		}
		else if (closeBtn->LeftMouseClicked()) {
			stopFlag = true;
		}
		else {
			this->DefaultCloseButtonProperties(this->closeBtn);
		}


		setvisualpage(getactivepage());
		//* Draw elements end above

		//* Clear mouseclick
		clearmouseclick(VK_LBUTTON);
		clearmouseclick(VK_RBUTTON);
	}
}

LandingView::~LandingView() {
	this->graphicalWindow->Deactivate();
	delete this->graphicalWindow;
	delete this->programTitle;
	delete this->closeBtn;
	delete this->dauSachView;
	delete this->theDocGiaView;
	delete this->thongKeView;
	delete[3] this->tabs;
}

