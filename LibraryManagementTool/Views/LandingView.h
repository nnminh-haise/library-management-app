#pragma once

#include "../Graphics/graphics.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../TheDocGia/TheDocGia.h"

namespace LANDING_VIEW {
	void RegisterDefaultSettings();

	void Run(AVL_TREE::Pointer& danhSachTheDocGia);
}