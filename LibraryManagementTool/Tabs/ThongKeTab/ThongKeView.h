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
	struct OverdueReader
	{
		OverdueReader();

		OverdueReader(READER::Reader* reader, BOOK_CIRCULATION::BookCirculation* book);

		READER::Reader* reader_;
		BOOK_CIRCULATION::BookCirculation* book_;
	};

	class Top10TitleDatasheet
	{
	public:
		Top10TitleDatasheet();

		Top10TitleDatasheet(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

		void CreateDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool GetStatus();

	private:
		bool status;

		AVL_TREE::Pointer* readerList;
		LINEAR_LIST::LinearList* titleList;

		DATASHEET::Controller top10TitlesDatasheetController;
	};

	class OverdueReadersDatasheet
	{
	public:
		OverdueReadersDatasheet();

		OverdueReadersDatasheet(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

		void CreateDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool GetStatus();

	private:
		bool status;

		AVL_TREE::Pointer* readerList;
		LINEAR_LIST::LinearList* titleList;

		DATASHEET::Controller overdueReaderDatasheetController;
	};
}

class StatisticTab
{
public:
	StatisticTab(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

	void Run();

private:
	void InittializeTitleButton();

	void TitleButtonOnAction();

private:
	STATISTIC_TAB_MEMBER::Top10TitleDatasheet top10TitlesDatasheet;
	STATISTIC_TAB_MEMBER::OverdueReadersDatasheet overdueReadersDatasheet;

	Button overdueReaderListButton;
	Button top10TitleButton;

	AVL_TREE::Pointer* readerList;
	LINEAR_LIST::LinearList* titleList;

	HashMap <int> titleBorrowedCountMap;
	HashMap <BOOK_TITLE::BookTitle*> titleListMap;
};

#endif // !THONG_KE_VIEW
