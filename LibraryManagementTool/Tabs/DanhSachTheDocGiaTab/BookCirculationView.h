#pragma once

#include "BookCirculationTable.h"
#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../UI/SearchFilters.h"
#include "../UI/SelectedObject.h"
#include "../../Helper/Package.h"
#include "../../TheDocGia/TheDocGia.h"

namespace BOOK_CIRCULATION_VIEW
{
	class SearchBox : public View
	{
	public:
		SearchBox();

		SearchBox(const SearchBox& other);

		SearchBox& operator=(const SearchBox& other);

		void SetPackage(Package* package);

		void SetSearchData(AVL_TREE::Pointer readerPointer);

		void SetReaderDatasheetPackage(BOOK_CIRCULATION_TABLE::DatasheetProcessor* datasheetPackage);

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

		AVL_TREE::Pointer readerPointer_ = nullptr;

		SearchFilters searchFilters_;

		BOOK_CIRCULATION_TABLE::DatasheetProcessor* readerTablePackage_ = nullptr;
	};

	class ToolSets : public View
	{
	public:
		ToolSets();

		void Activate();

		void Deactivate();

		bool InActive();

		int Run() override;

		void Reset();

		void SetPackage(Package* package);

		void SetReader(AVL_TREE::Pointer reader);

	private:
		void Initialize();

		void InitializeElements();

		int Display();

		int ToolButtonsOnAction();

	private:
		bool status_ = false;

		Button toolButtons_[3];

		Package* package_ = nullptr;

		AVL_TREE::Pointer reader_ = nullptr;
	};
}

class BookCirculationView : public View
{
public:
	BookCirculationView();

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	void SetPackage(Package* package);

	void SetReader(AVL_TREE::Pointer readerPointer);

	int Run() override;

private:
	void Initialize();

	void InitializeFilter();

	void InitializeTable();

	void InitializeSearchBox();

	void TargetBookOnAction();

	void BorrowBookProcess();

	void ReturnBookProcess();

	void LostBookProcess();

private:
	using View::status_;

	Package* package_ = nullptr;

	AVL_TREE::Pointer readerPointer_ = nullptr;

	DataFilter dataFilter_;

	BOOK_CIRCULATION_VIEW::ToolSets tools_;

private:
	BOOK_CIRCULATION_VIEW::SearchBox searchBox_;

	BOOK_CIRCULATION_TABLE::DatasheetProcessor tablePackage_;

	SelectedObject<DOUBLE_LINKED_LIST::Pointer> tableSelectedObject_;

private:
	HELPER::Fill background_;

	Button targetBook_{
		{1038, 390}, {120, 45}
	};
};

