
#include "DanhSachDauSachStyling.h"

namespace DANH_SACH_DAU_SACH_SEARCH_FIELD_STYLING {
	void BackgroundStyling(HELPER::Fill* background) {
		background->fillColor = rgb(33, 42, 62);
		background->borderColor = rgb(33, 42, 62);
	}

	void TitleStyling(Button* title) {
		/*title->SetFillColor(rgb(87, 108, 188));
		title->SetBorderColor(BLACK);
		title->SetTextColor(rgb(247, 247, 247));*/
	}

	void SearchBoxStyling(Button* bx) {
		bx->SetFillColor(rgb(241, 246, 249));
		bx->SetBorderColor(rgb(241, 246, 249));
		bx->SetTextColor(rgb(57, 62, 70));
	}

	void StatusBoxStyling(Button* bx) {
		bx->SetFillColor(rgb(248, 246, 244));
		bx->SetBorderColor(rgb(155, 164, 181));
		bx->SetTextColor(rgb(57, 62, 70));
	}
}

namespace DANH_SACH_DAU_SACH_NEW_LIST_ITEM_FORM_STYLING {
	void BackgroundStyling(HELPER::Fill* background) {
		background->fillColor = rgb(238, 238, 238);
		background->borderColor = BLACK;
	}

	void TitleStyling(Button* title) {
		title->SetFillColor(rgb(87, 108, 188));
		title->SetBorderColor(BLACK);
		title->SetTextColor(rgb(247, 247, 247));
	}

	void InputBoxStyling(Button* btn) {
		btn->SetFillColor(rgb(255, 251, 245));
		btn->SetBorderColor(BLACK);
		btn->SetTextColor(rgb(57, 62, 70));
	}

	void SubmitButtonStyling(Button* btn) {
		btn->SetFillColor(rgb(3, 201, 136));
		btn->SetBorderColor(btn->GetFillColor());
		btn->SetTextColor(rgb(57, 62, 70));
	}

	void SubmutButtonHoverStyling(Button* btn) {
		btn->SetFillColor(rgb(217, 248, 196));
		btn->SetBorderColor(rgb(122, 168, 116));
		btn->SetTextColor(rgb(26, 18, 11));
	}

	void InputBoxHoverProperties(Button* btn) {
		btn->SetBorderColor(rgb(70, 73, 255));
		btn->SetFillColor(rgb(234, 253, 252));
	}
}

namespace DANH_SACH_DAU_SACH_STYLING {
	void ListManipulateButtonDefaultProperties(Button& btn) {
		btn.SetFillColor(rgb(219, 223, 253));
		btn.SetBorderColor(btn.GetFillColor());
		btn.SetTextColor(rgb(57, 62, 70));
	}

	void ListManipulateButtonHoverProperties(Button& btn) {
		btn.SetFillColor(rgb(155, 163, 235));
		btn.SetBorderColor(rgb(36, 47, 155));
		btn.SetTextColor(rgb(234, 253, 252));
	}

	void NewItemButtonActiveProperties(Button& btn) {
		btn.SetFillColor(rgb(130, 170, 227));
		btn.SetBorderColor(rgb(57, 62, 70));
		btn.SetTextColor(rgb(57, 62, 70));
	}
}