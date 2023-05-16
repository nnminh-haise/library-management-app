#pragma once

#ifndef LANDING_VIEW
#define LANDING_VIEW

#include "../DanhSachTheDocGiaTab/DanhSachTheDocGia.h"
#include "../DanhSachDauSachTab/DanhSachDauSachView.h"
#include "../ThongKeTab/ThongKeView.h"

class LandingView {
private:
	void ConstructGraphicWindow();

	void ConstructNavigationBar();

	void TabsOnUpdate();

	void CloseButtonOnUpdate();

public:
	LandingView(AVL_Tree<READER::Reader, int>* readerList, LINEAR_LIST::LinearList* titleList);

	~LandingView();

	void Run();

private:
	//* Internal storage's pointer
	AVL_Tree<READER::Reader, int>* readerList;
	LINEAR_LIST::LinearList* titleList;

	//* Tabs
	DauSachTab* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	StatisticTab* thongKeView;

	//* Landing view elements
	Button* tabs;
	ELEMENTS::Window* graphicWindow;
	HELPER::Fill navigationBarBackground;
	Button programTitle;
	ELEMENTS::CloseButton closeBtn;
	bool programStopFlag;
	int currentTab;
	
	//* Core
	ELEMENTS::InputModeController inpController;
};



#endif // !LANDING_VIEW
