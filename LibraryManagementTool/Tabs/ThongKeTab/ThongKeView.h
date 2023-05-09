#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"

class Map {
public:
	Map();

private:
	int HashFunction(std::string combination);

private:
	const int MAX_VALUE = 456975;


};

class ThongKeView {
public:
	ThongKeView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList);

	void Run();

private:
	void TitleButtonOnAction();

	void CreateOverdueReaderDatasheet();

	void CreateTop10TitlesDatasheet();

	void InittializeTitleButton();

private:
	DATASHEET::Controller overdueReaderDatasheetController;
	DATASHEET::Controller top10TitlesDatasheetController;

	Button overdueReaderListButton;
	Button top10TitleButton;

	int displayingDatasheet;

	AVL_TREE::Pointer* readerList;
	LINEAR_LIST::LinearList* titleList;
};

#endif // !THONG_KE_VIEW
