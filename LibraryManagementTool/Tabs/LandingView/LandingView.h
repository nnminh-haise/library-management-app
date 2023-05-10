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
	LandingView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

	~LandingView();

	void Run();

private:
	//* Internal storage's pointer
	AVL_TREE::Pointer* readerList;
	LINEAR_LIST::LinearList* titleList;

	//* Tabs
	DauSachTab* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	StatisticTab* thongKeView;

	//* Landing view elements
	ELEMENTS::Window* graphicWindow;
	HELPER::Fill* navigationBarBackground;
	Button* programTitle;
	Button* tabs;
	ELEMENTS::CloseButton* closeBtn;
	bool programStopFlag;
	int currentTab;
	
	//* Core
	ELEMENTS::InputModeController inpController;
};



#endif // !LANDING_VIEW
