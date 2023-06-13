#pragma once

#include "ReaderListTable.hpp"
#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../../Helper/Package.h"
#include "../../DauSach/DauSach.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/LinearList.h"


namespace READER_TAB_MEMBERS
{
	class MainView : public View
	{
	public:
		MainView();

		void SetPackage(Package* package);

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		int Run() override;

	private:
		void Initialize();

		void InitializeElements();

		void InitializeFilters();

		void InitializeReaderTable();

		void CreateSortedByNameReaderList();

		void Log();

		void LogSortedList();

	private:
		using View::status_;

		Package* package_ = nullptr;

	private:
		DataFilter defaultReaderListFilter_;

		LinearList<AVL_TREE::Pointer> sortedByNameReaderList_;

		DataFilter sortedByNameReaderListFilter_;

		READER_TABLE::DatasheetProcessor readerTablePackage_;

		SelectedObject<AVL_TREE::Pointer> tableSelectedObject_;
	};
}

class DanhSachTheDocGiaView : public View
{
public:
	DanhSachTheDocGiaView();

	DanhSachTheDocGiaView(Package* package);

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	int Run() override;

private:
	void Initialize();

	void InitializeElements();

private:
	using View::status_;

	Package* package_ = nullptr;

	READER_TAB_MEMBERS::MainView mainView_;
};
