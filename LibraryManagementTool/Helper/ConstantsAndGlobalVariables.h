#pragma once

#include "Helper.h"
#include "../Graphics/graphics.h"

#include <string>

namespace CONSTANTS 
{	
	const std::string READER_DATABASE = "Databases/DOC_GIA_DB.txt";
	const std::string TITLES_DATABASE = "Databases/DAU_SACH_DB.txt";
	const std::string READER_INDICIES = "Databases/ReaderIndicies.bin";
	const int BACKGROUND_COLOR = WHITE;
	const int MAX_ROW_COUNT = 16;
}

namespace WINDOW_PROPERTIES 
{
	const HELPER::Dimension DIMENSION(1800, 1000);
	const std::string TITLE = "LIBRARY MANAGEMENT TOOL";
}

namespace NAVIGATION_BAR_PROPERTIES 
{	
	//* Navigation bar
	const HELPER::Dimension DIMENSION(1800, 100);
	const HELPER::Coordinate COORDINATE(0, 0);
	const int FILL_COLOR = rgb(11, 36, 71);
	const int BORDER_COLOR = rgb(11, 36, 71);

	//* Program's title
	const HELPER::Coordinate PROGRAM_TITLE_COORDINATE(36, 25);
	const HELPER::Dimension PROGRAM_TITLE_DIMENSION(440, 50);
	const int PROGRAM_TITLE_FILL_COLOR = rgb(236, 242, 255);
	const int PROGRAM_TITLE_BORDER_COLOR = rgb(236, 242, 255);
	const int PROGRAM_TITLE_TEXT_COLOR = rgb(46, 56, 64);
	const std::string PROGRAM_TITLE_PLACEHOLDER = "L I B R A R Y   M A N A G E M E N T   T O O L";
	
	//* Tabs 
	const std::string TAB_PLACEHOLDER[] = {
		"TITLES", "READERS", "STATISTICS"
	};
	const HELPER::Dimension TAB_DIMENSION { 300, 50 };
	const HELPER::Coordinate TAB_COORDINATE[] = {
		HELPER::Coordinate(640, 25),
		HELPER::Coordinate(980, 25),
		HELPER::Coordinate(1320, 25)
	};
	const int TAB_DEFAULT_FILL_COLOR = rgb(87, 108, 188);
	const int TAB_DEFAULT_BORDER_COLOR = BLACK;
	const int TAB_DEFAULT_TEXT_COLOR = WHITE;
	const int TAB_HOVER_FILL_COLOR = rgb(83, 127, 231);
	const int TAB_HOVER_BORDER_COLOR = BLACK;
	const int TAB_HOVER_TEXT_COLOR = rgb(233, 248, 249);
	const int TAB_ACTIVE_FILL_COLOR = rgb(210, 218, 255);
	const int TAB_ACTIVE_BORDER_COLOR = BLACK;
	const int TAB_ACTIVE_TEXT_COLOR = BLACK;

	const HELPER::Coordinate CLOSE_BUTTON_COORDINATE { 1705, 25 };
	const HELPER::Dimension CLOSE_BUTTON_DIMENSION { 50, 50 };
	const std::string CLOSE_BUTTON_PLACEHOLDER = "X";
	const int CLOSE_BUTTON_DEFAULT_FILL_COLOR = rgb(206, 89, 89);
	const int CLOSE_BUTTON_DEFAULT_BORDER_COLOR = rgb(206, 89, 89);
	const int CLOSE_BUTTON_HOVER_FILL_COLOR = rgb(255, 3, 3);
}

namespace GLOBAL_VARIABLES {
	inline extern textsettingstype defaultTextSetting{};
}

namespace DATASHEET_DEFAULT_PROPERTIES
{
	const int LETTER_WIDTH = 10;
	const int ROW_HEIGHT = 45;
	const int MAX_ROW = 16;
	const int PROPERTIES_COUNT = 6;
	const std::string LABEL_PLACEHOLDERS[] = { "ORDER", "PROP 1", "PROP 2", "PROP 3", "PROP 4", "PROP 5" };
	const int CHARACTER_LIMITS[] = { 3, 6, 6, 6, 6, 6 };
}

namespace READER_PROPERTIES
{
	const int PROPERTIES_COUNT = 6;
	const int CHARACTER_LIMITS[] = { 3, 4, 30, 15, 6, 9 };
	const int ROW_HEIGHT = 50;
	const std::string LABEL_PLACEHOLDERS[] = { "ORDER", "ID", "FIRST NAME", "LAST NAME", "SEX", "STATUS" };

	namespace READER_DETAIL_PROPERTIES
	{
		namespace BORROWED_BOOK_DATASHEET_PROPERTIES
		{
			const int MAX_ROW = 11;
			const int PROPERTIES_COUNT = 5;
			const std::string LABEL_PLACEHOLDERS[] = { "ORDER", "BOOK ID", "BORROW DATE", "RETURN DATE", "STATUS" };
			const int CHARACTER_LIMITS[] = { 3, 8, 10, 10, 8 };
			const HELPER::Coordinate TOP_LEFT{ 1115, 295 };
			const HELPER::Coordinate DATASHEET_CHANGE_BUTTON_TOP_LEFT{ 1115, 870 };
		}
	}
}

namespace TITLE_LIST_TABLE_PROPERTIES
{
	const int PROPERTIES_COUNT = 6;
	const int MAX_CHARACTERS[] = { 4, 50, 10, 40, 11, 20 };
	const int ROW_HEIGHT = 45;
	const std::string LABEL_PLACEHOLDERS[] = { "ISBN", "TITLE", "PAGE COUNT", "AUTHOR", "PUBLICATION", "CATEGORY" };
}

namespace STATISTIC_TAB_PROPERTIES
{
	namespace OVERDUE_READER_DATASHEET_PROPERTIES
	{
		const int MAX_ROW = 15;
		const int PROPERTIES_COUNT = 7;
		const std::string LABEL_PLACEHOLDERS[] = { "ORDER", "READER ID", "FULL NAME", "BOOK ID", "TITLE", "BORROW DATE", "OVERDUE DATE" };
		const int CHARACTER_LIMITS[] = { 5, 6, 40, 8, 30, 10, 10 };
		const HELPER::Coordinate TOP_LEFT{ 60, 180 };
		const HELPER::Coordinate DATASHEET_CHANGE_BUTTON_TOP_LEFT{ 850, 952 };
	}

	namespace TOP_10_TITLES_DATASHEET_PROPERTIES
	{
		const int MAX_ROW = 11;
		const int PROPERTIES_COUNT = 6;
		const std::string LABEL_PLACEHOLDERS[] = { "ORDER", "ISBN", "TITLE", "AUTHOR", "CATEGORY", "BORROWED COUNT" };
		const int CHARACTER_LIMITS[] = { 2, 4, 50, 40, 20, 6 };
		const HELPER::Coordinate TOP_LEFT{ 300, 180 };
		const HELPER::Coordinate DATASHEET_CHANGE_BUTTON_TOP_LEFT{ 300, 870 };
	}
}

namespace DAU_SACH_PROPERTIES {
	const int PROPERTIES_COUNT = 7;
	const int CHARACTER_LIMITS[] = { 3, 4, 50, 3, 40, 4, 20 };
	const int ROW_HEIGHT = 50;
	const std::string LABEL_PLACEHOLDERS[] = { "ORDER", "ISBN", "TITLE", "PAGE COUNT", "AUTHOR", "PUBLICATION", "CATEGORY" };
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

