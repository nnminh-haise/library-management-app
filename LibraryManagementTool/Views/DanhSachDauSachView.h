#pragma once

#include "../DauSach/DauSach.h"
#include <iostream>
#include <format>
#include <string>

namespace DANH_SACH_DAU_SACH_VIEW {
	DAU_SACH::LinearList database;

	struct Grid {
		int numberOfRow;
		int numberOfCol;
		int numberOfPage;

		Grid();

		int GetSize();

		void Render();
	};
}
