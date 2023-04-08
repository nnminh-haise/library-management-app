#pragma once

#include "Helper.h"
#include "../Graphics/graphics.h"

#include <string>

namespace CONSTANTS {
	inline extern const HELPER::Dimension WINDOW_DIMENSION(1920, 1080);
	inline extern const std::string WINDOW_TITLE = "LIBRARY MANAGEMENT TOOL";
	inline extern const std::string THE_DOC_GIA_DB = "Databases/DOC_GIA_DB.txt";
	inline extern const std::string DAU_SACH_DB = "Databases/DAU_SACH_DB.txt";
	inline extern const int BACKGROUND_COLOR = WHITE;
	inline extern const int MAX_ROW_COUNT = 16;

}

namespace GLOBAL_VARIABLES {
	inline extern textsettingstype defaultTextSetting{};
}

namespace THE_DOC_GIA_PROPERTIES {
	const int PROPERTIES_COUNT = 7;
	const int CHARACTER_LIMITS[] = { 3, 4, 30, 15, 3, 9, 10 };
	const int ROW_HEIGHT = 50;
	const std::string LABEL_PLACEHOLDERS[] = { "STT", "MA THE", "HO", "TEN", "PHAI", "TRANG THAI", "SACH DANG MUON" };
}

namespace DAU_SACH_PROPERTIES {
	const int PROPERTIES_COUNT = 8;
	const int CHARACTER_LIMITS[] = { 3, 4, 30, 3, 20, 4, 10, 8 };
	const int ROW_HEIGHT = 50;
	const std::string LABEL_PLACEHOLDERS[] = { "STT", "ISBN", "TEN SACH", "SO TRANG", "TAC GIA", "NXB", "THE LOAI", "DANH MUC SACH" };
}

namespace VIEW_ELEMENTS_PROPERTIES {
	const int BUTTON_COLOR = rgb(252, 221, 176);
	const int BUTTON_TEXT_COLOR = rgb(77, 77, 77);
	const int BUTTON_ACTIVE_COLOR = rgb(255, 217, 102);
	const int BUTTON_TEXT_ACTIVE_COLOR = rgb(77, 77, 77);
	const int NAVIGATION_BAR = rgb(252, 221, 176);
	const int BUTTON_HEIGHT = 50;
	const int BUTTON_WIDTH = 420;
};

namespace BUTTON_DEFAULT_PROPERTIES {
	const int FILL_COLOR = rgb(235, 69, 95);
	const int TEXT_COLOR = rgb(252, 255, 231);
	const int BORDER_COLOR = rgb(43, 52, 103);
}

