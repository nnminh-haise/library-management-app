#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../../DataStructures/DynamicArray.h"
#include "../../DataStructures/HashMap.h"
#include "../../DataStructures/Stack.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../../Helper/Package.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"

namespace STATISTIC_TAB_MEMBER
{
	struct OverdueReader
	{
		std::string readerID;
		std::string readerFullname;
		std::string bookID;
		std::string bookTitle;
		HELPER::Date borrowDate;
		int overdueDateCount = 0;
	};

	class Top10TitleDatasheet
	{
	public:
		Top10TitleDatasheet();

		Top10TitleDatasheet(Package* package);

		void CreateDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool GetStatus();

	private:
		bool status = false;

		Package* package_{ nullptr };

		DATASHEET::Controller top10TitlesDatasheetController;
	};

	class OverdueReadersDatasheet
	{
	public:
		OverdueReadersDatasheet();

		OverdueReadersDatasheet(Package* package);

		void CreateDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool GetStatus();

	private:
		bool status = false;

		Package* package_{ nullptr };

		DATASHEET::Controller overdueReaderDatasheetController;
	};
}

class StatisticTab : public View
{
public:
	StatisticTab(Package* package);

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	int Run() override;

private:
	void InittializeTitleButton();

	void TitleButtonOnAction();

private:
	using View::status_;

	STATISTIC_TAB_MEMBER::Top10TitleDatasheet top10TitlesDatasheet;
	STATISTIC_TAB_MEMBER::OverdueReadersDatasheet overdueReadersDatasheet;

	Button overdueReaderListButton;
	Button top10TitleButton;

	Package* package_{ nullptr };

	HashMap <int> titleBorrowedCountMap;
	HashMap <BOOK_TITLE::BookTitle*> titleListMap;
};

#endif // !THONG_KE_VIEW
