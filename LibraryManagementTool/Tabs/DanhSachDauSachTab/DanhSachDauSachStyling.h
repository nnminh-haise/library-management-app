
#pragma once

#include "../UI/Elements.h"

namespace DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING {
	void BackgroundStyling(HELPER::Fill* background);

	void TitleStyling(Button* title);

	void SearchBoxStyling(Button* bx);

	void StatusBoxStyling(Button* bx);
}

namespace DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING {
	void BackgroundStyling(HELPER::Fill* background);

	void TitleStyling(Button* title);

	void InputBoxStyling(Button* btn);

	void InputBoxHoverProperties(Button* btn);

	void SubmitButtonStyling(Button* btn);

	void SubmutButtonHoverStyling(Button* btn);
}

namespace DANH_SACH_DAU_SACH_STYLING {
	void ListManipulateButtonDefaultProperties(Button& btn);

	void ListManipulateButtonHoverProperties(Button& btn);

	void NewItemButtonActiveProperties(Button& btn);
}
