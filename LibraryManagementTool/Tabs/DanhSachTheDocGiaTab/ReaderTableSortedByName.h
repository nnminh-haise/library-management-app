#pragma once

#ifndef READERS_TABLE_SORTED_BY_NAME_H
#define READERS_TABLE_SORTED_BY_NAME_H

#include "../UI/SelectedObject.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"
#include "../UI/SearchFilters.h"
#include "../UI/Component.hpp"
#include "../../Helper/Package.h"

namespace READER_TABLE_SORTED_BY_NAME
{
	class DatasheetProcessor : public View
	{
	public:
		DatasheetProcessor();

		DatasheetProcessor(const DatasheetProcessor& other);

		DatasheetProcessor(LinearList<AVL_TREE::Pointer>* dataList, DataFilter* dataFilter);

		DatasheetProcessor& operator= (const DatasheetProcessor& other);

		void SetSelectedObjectContainer(SelectedObject<AVL_TREE::Pointer>* datasheetSelectedObject);

		void AllowCreateDatasheet();

		void CreateDatasheet();

		void SetDataFilter(DataFilter* dataFilter);

		DataFilter* GetDataFilter();

		void SetDataList(LinearList<AVL_TREE::Pointer>* dataList);

		DataFilter*& AccessDataFilter();

		DATASHEET::Datasheet& AccessCurrentDatasheet();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		int Run() override;

	private:
		void Display();

		int DatasheetOnAction();

	public:
		using View::status_;

		bool allowCreateDatasheet_ = false;

		DATASHEET::Controller datasheetController_;

		DataFilter* dataFilter_ = nullptr;

		LinearList<AVL_TREE::Pointer>* dataList_ = nullptr;

		SelectedObject<AVL_TREE::Pointer>* datasheetSelectedObject_ = nullptr;
	};
}

#endif // !READERS_TABLE_SORTED_BY_NAME_H

