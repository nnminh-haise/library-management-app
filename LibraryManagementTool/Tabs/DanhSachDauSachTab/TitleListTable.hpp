#pragma once

#include "../../DauSach/DauSach.h"
#include "../UI/Table.hpp"

namespace TITLE_LIST_TABLE
{
	class TitleRecord : public TABLE::Record<BOOK_TITLE::BookTitle, 6>
	{
	public:
		TitleRecord();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		TitleRecord(const TitleRecord& other);

		TitleRecord& operator=(const TitleRecord& other);

		bool Create(int recordIndex, BOOK_TITLE::BookTitle* objectPointer, HELPER::Coordinate topLeft) override;

	private:
		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::status_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::objectPointer_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::attributes_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::indexIndicator_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::recordIndex_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::attributeCount_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::topLeft_;

		using TABLE::Record<BOOK_TITLE::BookTitle, 6>::dimension_;
	};

	class TitleListTable : public TABLE::Table<TitleRecord, 15>
	{
	public:
		TitleListTable();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		TitleListTable(const TitleListTable& other);

		TitleListTable& operator=(const TitleListTable& other);

	private:
		using TABLE::Table<TitleRecord, 15>::status_;

		using TABLE::Table<TitleRecord, 15>::records_;

		using TABLE::Table<TitleRecord, 15>::recordCount_;

		using TABLE::Table<TitleRecord, 15>::topLeft_;

		using TABLE::Table<TitleRecord, 15>::dimension_;
	};

	typedef TABLE::Controller<TitleListTable> TitleListTableController;

	int CreateTables(LINEAR_LIST::LinearList* titleList, TitleListTableController* tables, HELPER::Coordinate topLeft);
}
