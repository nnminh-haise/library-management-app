#pragma once

#include "../Graphics/graphics.h"
#include "../TheDocGia/TheDocGia.h"
#include "../DauSach/DauSach.h"
#include "Elements.h"
#include "DanhSachTheDocGia.h"
#include "DanhSachDauSachView.h"
#include "ThongKeView.h"


class LandingView {
private:
	ELEMENTS::Window* graphicalWindow;
	ELEMENTS::Button* programTitle;
	ELEMENTS::Button* tabs;
	ELEMENTS::CloseButton* closeBtn;

	DanhSachDauSachView* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	ThongKeView* thongKeView;

private:
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

