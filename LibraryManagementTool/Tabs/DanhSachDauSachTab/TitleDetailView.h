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
#include "../../Helper/Package.h"

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

		void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

		void SetPackage(Package* package);

		bool SetRemovability(bool value);

		void SetRemoveBook(BOOK::Book* bookPointer);

	private:
		void Initialize();

		void InitializeElements();

		void InitializeNewBookCards();

		int Display(bool removable = true);

		int FunctionalityButtonsOnAction();

		bool NewBookFunctionOnAction();

		bool AddBooksButtonOnAction();

		bool RemoveBookFunctionOnAction();

	private:
		using View::status_;

		int selectingFunction_ = -1;

		Button functionalButtons_[3];

		LinkedButton infomaticButtons_[3];

		Button confirmButtons_[3];

		Button addNewBooksButton_;

		LINKED_LIST::Pointer newBooks_ = nullptr;

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController newBookCards_;

		BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

		Package* package_ = nullptr;

		bool removability_ = true;

		BOOK::Book* bookPointer_ = nullptr;
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

	void SetPackage(Package* package);

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

	Package* package_ = nullptr;
};

#endif // !TITLE_DETAIL
