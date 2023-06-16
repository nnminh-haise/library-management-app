#pragma once

#ifndef BOOK_CIRCULATION_TABLE_H
#define BOOK_CIRCULATION_TABLE_H

#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../UI/SearchFilters.h"
#include "../UI/SelectedObject.h"
#include "../../Helper/Package.h"
#include "../../TheDocGia/TheDocGia.h"

namespace BOOK_CIRCULATION_TABLE
{
	class DatasheetProcessor : public View
	{
	public:
		DatasheetProcessor();

		DatasheetProcessor(const DatasheetProcessor& other);

		DatasheetProcessor(AVL_TREE::Pointer readerPointer, DataFilter* dataFilter);

		DatasheetProcessor& operator= (const DatasheetProcessor& other);

		void SetSelectedObjectContainer(SelectedObject<DOUBLE_LINKED_LIST::Pointer>* datasheetSelectedObject);

		void AllowCreateDatasheet();

		void CreateDatasheet();

		void SetPackage(Package* package);

		void SetDataFilter(DataFilter* dataFilter);

		DataFilter* GetDataFilter();

		void SetDataList(AVL_TREE::Pointer readerPointer);

		DataFilter*& AccessDataFilter();

		DATASHEET::Datasheet& AccessCurrentDatasheet();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		int Run() override;

	private:
		void Initialize();

		void Display();

		int DatasheetOnAction();

	public:
		using View::status_;

		Package* package_ = nullptr;

		bool allowCreateDatasheet_ = false;

		DATASHEET::Controller datasheetController_;

		DataFilter* dataFilter_ = nullptr;

		AVL_TREE::Pointer readerPointer_ = nullptr;

		SelectedObject<DOUBLE_LINKED_LIST::Pointer>* datasheetSelectedObject_ = nullptr;
	};
}

#endif // !BOOK_CIRCULATION_TABLE_H

