#pragma once

#ifndef LANDING_VIEW
#define LANDING_VIEW

#include "../DanhSachTheDocGiaTab/DanhSachTheDocGia.h"
#include "../DanhSachDauSachTab/DanhSachDauSachView.h"
#include "../ThongKeTab/ThongKeView.h"
#include "LandingViewStyling.h"

class LandingView {
private:
	ELEMENTS::Window* graphicWindow;
	ELEMENTS::Fill* navigationBarBackground;
	ELEMENTS::Button* programTitle;
	ELEMENTS::Button* tabs;
	ELEMENTS::CloseButton* closeBtn;

	DanhSachDauSachView* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	ThongKeView* thongKeView;

	ELEMENTS::InputModeController inpController;

private:
	void ConstructGraphicWindow();

	void ConstructNavigationBar();

	void ConstructTabs(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach);

public:
	LandingView(AVL_TREE::Pointer& danhSachTheDocGia, LINEAR_LIST::LinearList& danhSachDauSach);

	~LandingView();

	void Run(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach);
};



#endif // !LANDING_VIEW
