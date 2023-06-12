#pragma once

#ifndef PACKAGE_HEADER
#define PACKAGE_HEADER

#include "../DataStructures/AVL_Tree.h"
#include "../DauSach/DauSach.h"
#include "../TheDocGia/TheDocGia.h"
#include "../Tabs/UI/Elements.h"
#include "../DataStructures/HashMap.h"
#include "../DataStructures/LinearList.h"

struct DataFilter
{
	bool* filters_ = nullptr;
	int filterSize_ = 0;
	int keep_ = 0;
};

struct Package
{
	AVL_TREE::Pointer* readerList = nullptr;

	LINEAR_LIST::LinearList* titleList = nullptr;

	ELEMENTS::InputModeController* inputController = nullptr;

	HashMap<BOOK_TITLE::BookTitle*>* titleMap = nullptr;
};

#endif // !PACKAGE_HEADER
