#pragma once

#ifndef SEARCH_BOX_H
#define SEARCH_BOX_H

#include "ReaderListTable.hpp"
#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../UI/SearchFilters.h"
#include "../UI/SelectedObject.h"
#include "../../Helper/Package.h"

namespace READER_SEARCH_BOX
{
	class SearchBox : public View
	{
	public:
		SearchBox();

		SearchBox(const SearchBox& other);

		SearchBox& operator=(const SearchBox& other);

		void SetPackage(Package* package);

		void SetSearchData(AVL_TREE::Pointer* searchData);

		void SetReaderDatasheetPackage(READER_TABLE::DatasheetProcessor* datasheetPackage);

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

		AVL_TREE::Pointer* searchData_ = nullptr;

		SearchFilters searchFilters_;

		READER_TABLE::DatasheetProcessor* readerTablePackage_ = nullptr;
	};
}

#endif // !SEARCH_BOX_H

