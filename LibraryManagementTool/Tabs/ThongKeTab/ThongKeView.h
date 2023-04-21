#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../../TheDocGia/TheDocGia.h"
#include "../../DauSach/DauSach.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"

class ThongKeView {
private:
	bool active;
	DATASHEET::Controller datasheetController;

private:
	void CreateDatasheets(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controller& datasheetController);

public:

	ThongKeView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach);

	void Run();
};

#endif // !THONG_KE_VIEW
