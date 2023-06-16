#pragma once

#ifndef SECOND_SEARCH_BOX_H
#define SECOND_SEARCH_BOX_H

#include "ReaderTableSortedByName.h"
#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../UI/SearchFilters.h"
#include "../UI/SelectedObject.h"
#include "../../Helper/Package.h"

namespace READER_SECOND_SEARCH_BOX
{
	class SearchBox : public View
	{
	public:
		SearchBox();

		SearchBox(const SearchBox& other);

		SearchBox& operator=(const SearchBox& other);

		void SetPackage(Package* package);

		void SetSearchData(LinearList<AVL_TREE::Pointer>* searchData);

		void SetReaderDatasheetPackage(READER_TABLE_SORTED_BY_NAME::DatasheetProcessor* datasheetPackage);

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		bool SearchOperation();

		void SearchBoxOnAction();

		void Display();

		int Run() override;

	private:
		void Initialize();

		void InitializeSearchFilters();

	private:
		using View::status_;

		Button title_;

		Button searchBox_;

		Package* package_ = nullptr;

		LinearList<AVL_TREE::Pointer>* searchData_ = nullptr;

		SearchFilters searchFilters_;

		READER_TABLE_SORTED_BY_NAME::DatasheetProcessor* readerTablePackage_ = nullptr;
	};
}

#endif // !SECOND_SEARCH_BOX_H

