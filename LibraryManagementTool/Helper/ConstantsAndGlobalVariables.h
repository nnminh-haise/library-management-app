#pragma once

#include "Helper.h"
#include "../Graphics/graphics.h"

#include <string>

namespace CONSTANTS {
	inline extern const HELPER::Dimension WINDOW_DIMENSION(1920, 1080);
	inline extern const std::string WINDOW_TITLE = "LIBRARY MANAGEMENT TOOL";
	inline extern const std::string THE_DOC_GIA_DB = "Databases/DOC_GIA_DB.txt";
}

namespace GLOBAL_VARIABLES {
	inline extern textsettingstype defaultTextSetting{};
}
