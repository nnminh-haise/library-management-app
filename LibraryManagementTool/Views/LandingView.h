#pragma once

#include "../TheDocGia/TheDocGia.h"
#include "../DauSach/DauSach.h"
#include "Elements.h"
#include "DanhSachTheDocGia.h"
#include "DanhSachDauSachView.h"
#include "ThongKeView.h"


//class UniversalInputModeController : public ELEMENTS::InputModeController {
//public:
//	bool KeyValidation(const char& chr) override;
//
//	void ActionOnKey(const char& chr) override;
//};

class LandingView {
private:
	ELEMENTS::Window* graphicalWindow;
	ELEMENTS::Button* programTitle;
	ELEMENTS::Button* tabs;
	ELEMENTS::CloseButton* closeBtn;

	DanhSachDauSachView* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	ThongKeView* thongKeView;

	ELEMENTS::InputModeController inpController;

private:
	//* Elements styling methods
	void GraphicalWindowDefaultProperties(ELEMENTS::Window*& win);

	void DefaultButtonProperties(ELEMENTS::Button& button);
	
	void FocusOnCurrentTab(ELEMENTS::Button& button);
	
	void ButtonHover(ELEMENTS::Button& button);
	
	void ProgramTitleProperties(ELEMENTS::Button*& btn);
	
	void DefaultCloseButtonProperties(ELEMENTS::CloseButton*& btn);
	
	void CloseButtonHover(ELEMENTS::CloseButton*& button);
	
public:
	LandingView(AVL_TREE::Pointer& danhSachTheDocGia, LINEAR_LIST::LinearList& danhSachDauSach);

	~LandingView();

	void Run();
};

