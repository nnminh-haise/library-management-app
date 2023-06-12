#pragma once

#ifndef LANDING_VIEW
#define LANDING_VIEW

#include "../DanhSachTheDocGiaTab/DanhSachTheDocGia.h"
#include "../DanhSachDauSachTab/DanhSachDauSachView.h"
#include "../ThongKeTab/ThongKeView.h"
#include "../../Helper/Package.h"

class LandingView
{
public:
	LandingView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

	~LandingView();

	void Run();

private:
	void CreateTitleHashMap();

	void CreatePackage();

	void ConstructGraphicWindow();

	void ConstructNavigationBar();

	void TabsOnUpdate();

	void CloseButtonOnUpdate();

private:
	//* Internal storage's pointer
	AVL_TREE::Pointer* readerList;
	LINEAR_LIST::LinearList* titleList;

	//* Tabs
	DauSachTab* dauSachView;
	DanhSachTheDocGiaView* theDocGiaView;
	StatisticTab* thongKeView;

	//* Landing view elements
	Button tabs[3];
	
	ELEMENTS::Window* graphicWindow;
	
	HELPER::Fill navigationBarBackground;
	
	Button programTitle;
	
	ELEMENTS::CloseButton closeBtn;
	
	bool programStopFlag;

	int currentTab;
	
	//* Core
	ELEMENTS::InputModeController inpController;
	
	HashMap<BOOK_TITLE::BookTitle*> titleMap_;

	Package package_;
};



#endif // !LANDING_VIEW
