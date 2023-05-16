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
		std::string readerID;
		std::string readerFullname;
		std::string bookID;
		std::string bookTitle;
		HELPER::Date borrowDate;
		int overdueDateCount;
	};

	class Top10TitleDatasheet
	{
	public:
		Top10TitleDatasheet();

		Top10TitleDatasheet(AVL_Tree<READER::Reader, int>* readerList, LINEAR_LIST::LinearList* titleList);

		void CreateDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool GetStatus();

	private:
		bool status;

		AVL_Tree<READER::Reader, int>* readerList;
		LINEAR_LIST::LinearList* titleList;

		DATASHEET::Controller top10TitlesDatasheetController;
	};

	class OverdueReadersDatasheet
	{
	public:
		OverdueReadersDatasheet();

		OverdueReadersDatasheet(AVL_Tree<READER::Reader, int>* readerList, LINEAR_LIST::LinearList* titleList);

		void CreateDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool GetStatus();

	private:
		bool status;

		AVL_Tree<READER::Reader, int>* readerList;
		LINEAR_LIST::LinearList* titleList;

		DATASHEET::Controller overdueReaderDatasheetController;
	};
}

class StatisticTab
{
public:
	StatisticTab(AVL_Tree<READER::Reader, int>* readerList, LINEAR_LIST::LinearList* titleList);

	void Run();

private:
	void InittializeTitleButton();

	void TitleButtonOnAction();

private:
	STATISTIC_TAB_MEMBER::Top10TitleDatasheet top10TitlesDatasheet;
	STATISTIC_TAB_MEMBER::OverdueReadersDatasheet overdueReadersDatasheet;

	Button overdueReaderListButton;
	Button top10TitleButton;

	AVL_Tree<READER::Reader, int>* readerList;
	LINEAR_LIST::LinearList* titleList;

	HashMap <int> titleBorrowedCountMap;
	HashMap <BOOK_TITLE::BookTitle*> titleListMap;
};

#endif // !THONG_KE_VIEW
