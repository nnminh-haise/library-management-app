#pragma once

#include "Helper.h"
#include "../Graphics/graphics.h"

#include <string>

namespace CONSTANTS {
	inline extern const HELPER::Dimension WINDOW_DIMENSION(1920, 1080);
	inline extern const std::string WINDOW_TITLE = "LIBRARY MANAGEMENT TOOL";
	inline extern const std::string THE_DOC_GIA_DB = "Databases/DOC_GIA_DB.txt";
	inline extern const int BACKGROUND_COLOR = WHITE;
}

namespace GLOBAL_VARIABLES {
	inline extern textsettingstype defaultTextSetting{};
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