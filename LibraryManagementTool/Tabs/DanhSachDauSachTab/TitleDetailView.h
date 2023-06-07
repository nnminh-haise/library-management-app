#pragma once

#ifndef TITLE_DETAIL
#define TITLE_DETAIL

#include "TitleDetailCard.hpp"
#include "../UI/Component.hpp"
#include "../UI/Button.h"
#include "../UI/Sheets.hpp"
#include "../UI/Elements.h"
#include "../../DauSach/DauSach.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"

namespace TITLE_DETAIL_VIEW_COMPONENTS
{
	class FunctionalitySet : public View
	{
	public:
		FunctionalitySet();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		using View::GoBackButtonOnAction;

		int Run() override;

		void Reset();

	private:
		void Initialize();

		void InitializeElements();

		void Display();

		int FunctionalityButtonsOnAction();

	private:
		using View::status_;

		int selectingFunction_ = -1;

		Button functionalButtons_[3];

		LinkedButton infomaticButtons_[3];

		Button confirmButtons_[3];

		HELPER::Fill confirmCovers_[3];
	};
}

class TitleDetail : public View
{
public:
	TitleDetail();

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	using View::GoBackButtonOnAction;

	void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

	int Run() override;

private:
	void Initialize();

	void InitializeElements();

	void CleanUp();

	void Display();

private:
	using View::status_;

	using View::goBackButton_;

	TitleDetailCard detailCard_;

	TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet functionalitySet_;

	BOOK_TITLE::BookTitle* titlePointer_ = nullptr;
};

#endif // !TITLE_DETAIL
