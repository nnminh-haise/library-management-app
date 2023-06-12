#pragma once

#ifndef TITLE_DETAIL
#define TITLE_DETAIL

#include "TitleDetailCard.hpp"
#include "TitleListTable.hpp"
#include "../UI/Component.hpp"
#include "../UI/Button.h"
#include "../UI/Table.hpp"
#include "../UI/Elements.h"
#include "../../DauSach/DauSach.h"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../Helper/Package.h"

namespace TITLE_DETAIL_VIEW_COMPONENTS
{
	class CreatingNewBooksSection : public View
	{
	public:
		CreatingNewBooksSection();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		int Run() override;

		void Reset();

		void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

		BOOK_TITLE::BookTitle* GetCurrentTitle();

		void SetPackage(Package* package);

	private:
		void Initialize();

		void InitializeElements();

		int Display();

		int InfomaticButtonOnAction();

		int ConfirmButtonOnAction();

		void CreateCatalogue(int catalogueSize);

		void InitializeNewBookCards();

		void NewBooksCardsOnAction();

		int SaveButtonOnAction();

	private:
		using View::status_;

		BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

		Package* package_ = nullptr;

	private:
		LinkedButton infomaticButtons_;

		Button confirmButton_;

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController newBooksCardsController_;

		bool allowCreatingNewBooks_ = false;

		Button saveButton_;

		LINKED_LIST::Pointer newBooks_ = nullptr;

	};

	class UpdateBookSection : public View
	{
	public:
		UpdateBookSection();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		int Run() override;

		void Reset();

		void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

		BOOK_TITLE::BookTitle* GetCurrentTitle();

		void SetBookPointer(BOOK::Book* bookPointer);

		BOOK::Book* GetBookPointer();

		void SetCurrentCatalogueCardPointer(TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard);

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* GetCurrentCatalogueCardPointer();

		void SetPackage(Package* package);

	private:
		void Initialize();

		void InitializeElements();

		int Display();

		int ConfirmButtonOnAction();

		int CatalogueCardOnAction();

	private:
		using View::status_;

		BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

		BOOK::Book* bookPointer_ = nullptr;

		Package* package_ = nullptr;

	private:
		LinkedButton infomaticButtons_;

		Button confirmButton_;

		bool allowUpdateBook_ = false;

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard_ = nullptr;
	};

	class DelateBookSection : public View
	{
	public:
		DelateBookSection();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		int Run() override;

		void Reset();

		void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

		BOOK_TITLE::BookTitle* GetCurrentTitle();

		void SetBookPointer(BOOK::Book* bookPointer);

		BOOK::Book* GetBookPointer();

		void SetCurrentCatalogueCardPointer(TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard);

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* GetCurrentCatalogueCardPointer();

		void SetPackage(Package* package);

	private:
		void Initialize();

		void InitializeElements();

		int Display();

		int ConfirmButtonOnAction();

	private:
		using View::status_;

		BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

		BOOK::Book* bookPointer_ = nullptr;

		Package* package_ = nullptr;

	private:
		LinkedButton infomaticButtons_;

		Button confirmButton_;

		bool allowDeleteBook_ = false;

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard_ = nullptr;
	};

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

		void SetCurrentBook(BOOK::Book* bookPointer);

		BOOK::Book* GetCurrentBook();

		void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

		BOOK_TITLE::BookTitle* GetCurrentTitle();

		void SetCurrentCatalogueCardPointer(TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard);

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* GetCurrentCatalogueCardPointer();

		void SetPackage(Package* package);

		int WorkingFunctionality();

	private:
		void Initialize();

		void InitializeElements();

		int Display();

		int FunctionalityButtonsOnAction();

		int FunctionButtonOnAction(int indicator);

	private:
		using View::status_;

		int workingFunction_ = -1;

		Button functionalButtons_[3];

		BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

		BOOK::Book* bookPointer_ = nullptr;

		Package* package_ = nullptr;

		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard_ = nullptr;
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

	void InitializeCatalogueCards();

	void CleanUp();

	void Display();

private:
	using View::status_;

	using View::goBackButton_;

	TitleDetailCard detailCard_;

	TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet functionalitySet_;

	BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

	Package* package_ = nullptr;

private:
	TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController catalogueSection_;

	TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection creatingNewBooksSection_;

	TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection updatingBookSection_;

	TITLE_DETAIL_VIEW_COMPONENTS::DelateBookSection deletingBookSection_;
};

#endif // !TITLE_DETAIL
