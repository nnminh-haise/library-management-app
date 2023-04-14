#include "LandingView.h"
#include "../../Helper/Helper.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"

#include <iostream>
#include <string>
#include <format>
#include <ctime>



void LandingView::ConstructGraphicWindow() {
	this->graphicWindow = new ELEMENTS::Window { CONSTANTS::WINDOW_DIMENSION, CONSTANTS::WINDOW_TITLE };
	LANDING_VIEW_STYLING::GraphicalWindowDefaultProperties(this->graphicWindow);
}

void LandingView::ConstructNavigationBar() {

	//* Create a background for the navigation bar
	this->navigationBarBackground = new ELEMENTS::Fill (
		HELPER::Coordinate(0, 0),
		CONSTANTS::WINDOW_DIMENSION.width, 100, //* Background dimension
		rgb(11, 36, 71), //* Background color
		rgb(11, 36, 71)  //* Border color
	);

	this->programTitle = new ELEMENTS::Button{ //* Initiallize Title button
		HELPER::Coordinate(36, 25), HELPER::Dimension(440, 50)
	};
	LANDING_VIEW_STYLING::ProgramTitleProperties(this->programTitle); //* Apply styling for the button
	this->programTitle->SetPlaceholder("Q U A N   L I   T H U   V I E N"); //* Assign the title for the button

	std::string tabPlaceholders[3] { //* Tab's title
		"DANH SACH DAU SACH", "DANH SACH THE DOC GIA", "THONG KE"
	};
	HELPER::Dimension tabDimension { 300, 50 }; //* Tab's Dimension
	HELPER::Coordinate tabCoordinates[3] { //* Tab's Coordinates
		HELPER::Coordinate(640, 25),
		HELPER::Coordinate(980, 25),
		HELPER::Coordinate(1320, 25)
	};
	this->tabs = new ELEMENTS::Button[3]; //* Initialize tabs
	for (int i = 0; i < 3; ++i) { //* Assign coordinates and dimension to the tabs
		this->tabs[i] = ELEMENTS::Button(tabCoordinates[i], tabDimension);
		this->tabs[i].SetPlaceholder(tabPlaceholders[i]);
		LANDING_VIEW_STYLING::DefaultTabButtonProperties(this->tabs[i]); //* Assign the styling to the object
	}

	this->closeBtn = new ELEMENTS::CloseButton( //* Initialize the close button
		HELPER::Coordinate(1705, 25), 50, 50
	);
	LANDING_VIEW_STYLING::DefaultCloseButtonProperties(this->closeBtn); //* Assign the styling to the object
}

void LandingView::ConstructTabs(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach) {
	this->dauSachView = new DanhSachDauSachView(dsDauSach);
	this->theDocGiaView = new DanhSachTheDocGiaView(dsTheDocGia);
	this->thongKeView = new ThongKeView(dsTheDocGia, dsDauSach);
}

//* View Constructor function.
LandingView::LandingView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach) {

	THE_DOC_GIA_MODULES::LoadDanhSachTheDocGiaFromDB(CONSTANTS::THE_DOC_GIA_DB, dsTheDocGia);
	DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(CONSTANTS::DAU_SACH_DB, dsDauSach);

	this->ConstructGraphicWindow();
	this->graphicWindow->Activate();

	this->ConstructNavigationBar();
	this->ConstructTabs(dsTheDocGia, dsDauSach);
}

//* View Run function
void LandingView::Run(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach) {

	int currentTab = 0;
	bool programStopFlag = false;
	while (programStopFlag == false) {

		while (!kbhit() && programStopFlag == false) {

			//* Draw elements begin below
			setactivepage(1 - getactivepage());


			//* Draw elements
			this->graphicWindow->RenderBackground();
			this->navigationBarBackground->Draw();
			this->programTitle->Display();

			for (int i = 0; i < 3; ++i) {
				LANDING_VIEW_STYLING::CurrentActiveTabButtonProperties(this->tabs[currentTab]);
				this->tabs[i].Display();
			}
			this->closeBtn->Display();

			switch (currentTab) {
				case (0):
					this->dauSachView->Run();
					break;
				case (1):
					this->theDocGiaView->Run(dsTheDocGia, this->inpController);
					break;
				case (2):
					this->thongKeView->Run();
					break;
			}

			/**
			* The code below here will evaluate what will happened at the end of each frame.
			* The code should update each elements if necessary or stay the same at the frame before.
			* The code should be clear and simple but yet efficient!
			*/
			for (int i = 0; i < 3; ++i) {
				if (i != currentTab) {
					if (this->tabs[i].IsHover()) {
						LANDING_VIEW_STYLING::CurrentButtonHoverProperties(this->tabs[i]);
					}
					else if (this->tabs[i].LeftMouseClicked()) {
						currentTab = i;
					}
					else {
						LANDING_VIEW_STYLING::DefaultTabButtonProperties(this->tabs[i]);
					}
				}
			}

			if (this->closeBtn->IsPointed() && this->closeBtn->LeftMouseClicked() == false) {
				LANDING_VIEW_STYLING::CloseButtonHover(this->closeBtn);
			}
			else if (closeBtn->LeftMouseClicked()) {
				programStopFlag = true;
			}
			else {
				LANDING_VIEW_STYLING::DefaultCloseButtonProperties(this->closeBtn);
			}


			setvisualpage(getactivepage());
			//* Draw elements end above

			//* Clear mouseclick
			clearmouseclick(VK_LBUTTON);
			clearmouseclick(VK_RBUTTON);
		}

		//* Input processing start in this if statement
		if (programStopFlag == false && this->inpController.InInputMode()) {
			char tmp = std::toupper(getch());
			this->inpController.ActionOnKey(tmp);
		}

		//* This currently filter out the case where input mode is not on but user still press some key.
		else if (programStopFlag == false) {
			char emptychr = getch();//take an empty char then do nothing
		}
	}

	//* Update databse before closing the program
	THE_DOC_GIA_MODULES::UpdateListToDatabase(CONSTANTS::THE_DOC_GIA_DB, dsTheDocGia);
}

//* View destructor
LandingView::~LandingView() {
	this->graphicWindow->Deactivate();
	delete this->graphicWindow;
	delete this->navigationBarBackground;
	delete this->programTitle;
	delete this->closeBtn;
	delete this->dauSachView;
	delete this->theDocGiaView;
	delete this->thongKeView;
	delete[3] this->tabs;
}
