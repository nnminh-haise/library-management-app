#ifndef THONG_KE_VIEW
#define THONG_KE_VIEW

#pragma once

#include "../TheDocGia/TheDocGia.h"
#include "../DauSach/DauSach.h"
#include "Elements.h"

class ThongKeView {
private:
	ELEMENTS::Button* txtbx;
	ELEMENTS::InputBox* inpbx;

public:
	ThongKeView(AVL_TREE::Pointer& dsTheDocGia, LINEAR_LIST::LinearList& dsDauSach);

	void Run();
};

#endif // !THONG_KE_VIEW
