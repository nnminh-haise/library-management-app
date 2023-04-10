#include "LandingView.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"

#include <iostream>
#include <string>
#include <format>
#include <ctime>


//* Input Controller
//bool UniversalInputModeController::KeyValidation(const char& chr) {
//	if (chr == ' ') {
//		return true;
//	}
//
//	if (isalnum(chr)) {
//		return true;
//	}
//
//	return false;
//}
//
//void UniversalInputModeController::ActionOnKey(const char& chr) {
//	if (chr == ELEMENTS::SpecialKey::ENTER || chr == ELEMENTS::SpecialKey::ESCAPE) {
//		if (this->outputTextBox != nullptr) {
//			this->outputTextBox->SetPlaceholder(this->inputString);
//		}
//		this->Deactivate();
//	}
//	else if (this->inputString.length() == 0 && chr == ' ') {
//		return;
//	}
//	else if (this->inputString.length() != 0 && this->inputString[this->inputString.length() - 1] == ' ' && chr == ' ') {
//		return;
//	}
//	else if (this->inputString.length() == 0 && chr == ELEMENTS::SpecialKey::BACKSPACE) {
//		return;
//	}
//	else if (chr == ELEMENTS::SpecialKey::BACKSPACE) {
//		this->inputString.pop_back();
//		this->characterCount--;
//		this->currentTextBox->SetPlaceholder(this->inputString);
//	}
//	else if (this->characterCount < this->characterLimit && this->KeyValidation(chr)) {
//		this->inputString.push_back(chr);
//		++this->characterCount;
//		this->currentTextBox->SetPlaceholder(this->inputString);
//	}
//}



//* Styling elements session start below

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

//--- Styling elements end above!



//* View Constructor function.

LandingView::LandingView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach) {

	//* Elements initialization start below
	this->graphicalWindow = new ELEMENTS::Window(CONSTANTS::WINDOW_DIMENSION, (std::string)CONSTANTS::WINDOW_TITLE);
	this->GraphicalWindowDefaultProperties(this->graphicalWindow);
	this->graphicalWindow->Activate();

	this->programTitle = new ELEMENTS::Button(HELPER::Coordinate(36, 25), 440, 50);
	this->programTitle->SetPlaceholder("Q U A N   L I   T H U   V I E N");
	this->ProgramTitleProperties(this->programTitle);

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

	this->closeBtn = new ELEMENTS::CloseButton(HELPER::Coordinate(1705, 25), 50, 50);
	this->DefaultCloseButtonProperties(this->closeBtn);

	//* Views initialization
	this->dauSachView = new DanhSachDauSachView(dsDauSach);
	this->theDocGiaView = new DanhSachTheDocGiaView(dsTheDocGia);
	this->thongKeView = new ThongKeView(dsTheDocGia, dsDauSach);
}



//* View Run function

void LandingView::Run() {
	//* Create a background for the navigation bar
	ELEMENTS::Fill navigationBar(
		HELPER::Coordinate(0, 0),
		CONSTANTS::WINDOW_DIMENSION.width, 100, //* Background dimension
		rgb(11, 36, 71), //* Background color
		rgb(11, 36, 71)  //* Border color
	);

	int currentTab = 0;
	bool stopFlag = false;
	while (stopFlag == false) {

		while (!kbhit() && stopFlag == false) {

			//std::cerr << std::format("last key: {}\n", this->inpController.inputKey);
			//std::cerr << std::format("inpStr  : {}\n", this->inpController.inputString);

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
				this->theDocGiaView->Run(this->inpController);
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

		//std::cerr << std::format("global input mode: {}\n", this->inpController.InInputMode());

		//* Input processing start in this if statement
		if (stopFlag == false && this->inpController.InInputMode()) {
			char tmp = std::toupper(getch());
			this->inpController.ActionOnKey(tmp);
		}

		//* This currently filter out the case where input mode is not on but user still press some key.
		else if (stopFlag == false) {
			char emptychr = getch();//take an empty char then do notthing
		}
	}
}



//* View destructor

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

