#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../../DataStructures/DynamicArray.h"
#include "../../DataStructures/HashMap.h"
#include "../../DataStructures/Stack.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"

namespace STATISTIC_TAB_MEMBER
{
	struct OverdueReader {
		OverdueReader();

		OverdueReader(READER::Reader* reader, BOOK_CIRCULATION::BookCirculation* book);

		READER::Reader* reader_;
		BOOK_CIRCULATION::BookCirculation* book_;
	};
}

class StatisticTab {
public:
	StatisticTab(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

	void Run();

private:
	void TitleBorrowedCountProcess();

	void OverdueReaderCountProcess();

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
	HashMap < BOOK_TITLE::BookTitle* > titleListMap;

	DynamicArray <STATISTIC_TAB_MEMBER::OverdueReader> overdueReaders;
};

#endif // !THONG_KE_VIEW
