#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../../DataStructures/HashMap.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"

class ThongKeView {
public:
	ThongKeView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

	void Run();

private:
	void TitleBorrowedCountProcess();

	void TitleButtonOnAction();

	void CreateOverdueReaderDatasheet();

	void CreateTop10TitlesDatasheet();

	void InittializeTitleButton();

private:
	DATASHEET::Controller overdueReaderDatasheetController;
	DATASHEET::Controller top10TitlesDatasheetController;

	Button overdueReaderListButton;
	Button top10TitleButton;

	int displayingDatasheet;

	AVL_TREE::Pointer* readerList;
	LINEAR_LIST::LinearList* titleList;

	HashMap < int > titleBorrowedCountMap;
	HashMap < BOOK_TITLE::BookTitle* > titleMap;
};

#endif // !THONG_KE_VIEW
