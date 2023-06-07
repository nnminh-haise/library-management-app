#pragma once

#ifndef TITLE_DETAIL_CARD
#define TITLE_DETAIL_CARD

#include "../../DauSach/DauSach.h"
#include "../../Helper/Helper.h"
#include "../UI/Component.hpp"
#include "../UI/Button.h"
#include <string>
#include <format>
#include <sstream>

namespace TITLE_DETAIL_COMPONENTS
{
	class BookDetailCard : public View
	{
	public:
		BookDetailCard();

		BookDetailCard(const BookDetailCard& other);

		BookDetailCard& operator=(const BookDetailCard& other);

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		void UpdateCard(BOOK::Book* bookPointer);

		int Run() override;

	private:
		void Initialize();

		void InitializeElements();

		void Display();

	private:
		using View::status_;

		HELPER::Fill background_;

		Button heading_;

		LinkedButton bookID_;

		LinkedButton bookStatus_;

		LinkedButton row_;

		LinkedButton column_;

		LinkedButton section_;
	};

	class BookDetailCardsController : public View
	{
	public:
		BookDetailCardsController();

		BookDetailCardsController(int catalogueSize);

		BookDetailCardsController(const BookDetailCardsController& other);

		~BookDetailCardsController();

		BookDetailCardsController& operator=(const BookDetailCardsController& other);

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		void CreateCatalogueCards(LINKED_LIST::Pointer catalogue);

		int Run() override;

	private:
		void Initialize();

		void InitializeElements();

		void Display();

		void UpdateCard(int cardIndex, BOOK::Book* bookPointer);

		void CardChangeButtonsOnAction();

	private:
		using View::status_;

		int catalogueSize_ = 0;

		int activeCardIndex_ = -1;

		BookDetailCard* cards_ = nullptr;

		Button cardChangeButtons_[2];

		Button cardCountIndicator_;
	};
}

class TitleDetailCard : public View
{
public:
	TitleDetailCard();

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	void UpdateCard(BOOK_TITLE::BookTitle* targetedTitle);

	int Run() override;

private:
	void Initialize();

	void InitializeElements();

	void Display();

private:
	using View::status_;

	HELPER::Fill background_;

	Button heading_;

	LinkedButton isbn_;

	LinkedButton title_;

	LinkedButton category_;

	LinkedButton author_;

	LinkedButton pageCount_;

	LinkedButton publication_;

	LinkedButton catalogueSize_;

	TITLE_DETAIL_COMPONENTS::BookDetailCardsController catalogueController_;
};

#endif // !TITLE_DETAIL_CARD
