
#pragma once

#include "../UI/Elements.h"

namespace DANH_SACH_THE_DOC_GIA_SEARCH_FIELD_STYLING {
	void BackgroundStyling(ELEMENTS::Fill* background);

	void TitleStyling(ELEMENTS::Button* title);

	void SearchBoxStyling(ELEMENTS::Button* bx);

	void StatusBoxStyling(ELEMENTS::Button* bx);
}

namespace DANH_SACH_THE_DOC_GIA_NEW_LIST_ITEM_FORM_STYLING {
	void BackgroundStyling(ELEMENTS::Fill* background);

	void TitleStyling(ELEMENTS::Button* title);

	void InputBoxStyling(ELEMENTS::Button* btn);

	void InputBoxHoverProperties(ELEMENTS::Button* btn);

	void SubmitButtonStyling(ELEMENTS::Button* btn);

	void SubmutButtonHoverStyling(ELEMENTS::Button* btn);
}

namespace DANH_SACH_THE_DOC_GIA_STYLING {
	void DatasheetChangeButtonNHoverProperties(ELEMENTS::Button& btn);

	void DefaultDatasheetChangeButtonProperties(ELEMENTS::Button& btn);

	void ListManipulateButtonDefaultProperties(ELEMENTS::Button& btn);

	void ListManipulateButtonHoverProperties(ELEMENTS::Button& btn);

	void NewItemButtonActiveProperties(ELEMENTS::Button& btn);

	void DatasheetLabelsButtonHoverStyling(ELEMENTS::Button* btn);

	void DatasheetLabelsButtonDefaultStyling(ELEMENTS::Button* btn);
}
