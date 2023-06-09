#pragma once

#ifndef TITLE_DETAIL_CARD
#define TITLE_DETAIL_CARD

#include "../../Helper/Package.h"
#include "../../DauSach/DauSach.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/Stack.h"
#include "../../Helper/Helper.h"
#include "../UI/Component.hpp"
#include "../UI/Button.h"
#include <string>
#include <format>
#include <sstream>

namespace TITLE_DETAIL_CARD_COMPONENTS
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

		void SetPackage(Package* package);

		HELPER::Fill& DA_Background();

		Button& DA_Heading();

		LinkedButton& DA_BookID();

		LinkedButton& DA_BookStatus();

		LinkedButton& DA_Row();

		LinkedButton& DA_Column();

		LinkedButton& DA_Section();

		int Run() override;

		int SectionOnAction();

		void SetRemovability(bool value);

		bool Removability();

		void SetBookPointer(BOOK::Book* bookPointer);

		BOOK::Book* GetBookPointer();

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

		Button removavilityIndicator_{ {0, 0}, {0, 0} };

		Package* package_;

		bool removable_ = true;

		BOOK::Book* bookPointer_ = nullptr;
	};

	class BookDetailCardsController : public View
	{
	public:
		BookDetailCardsController();

		BookDetailCardsController(int catalogueSize);

		BookDetailCardsController(const BookDetailCardsController& other);

		~BookDetailCardsController();

		BookDetailCardsController& operator=(const BookDetailCardsController& other);

		BookDetailCard& operator[] (int index);

		Button& DA_CardChangeButton(int index);

		Button& DA_CardCountIndicator();

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		void CreateCatalogueCards(LINKED_LIST::Pointer catalogue);

		LINKED_LIST::Pointer GetCatalogueData();

		void SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer);

		void SetPackage(Package* package);

		int Size();

		int Run() override;

		int CardElementsOnAction();

		bool Removability(int index);

		int CurrentCardIndex();

		void SetEmptyCatalogue(bool value);

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

		BOOK_TITLE::BookTitle* titlePointer_ = nullptr;

		LINKED_LIST::Pointer titleCatalogue_ = nullptr;

		Package* package_ = nullptr;

		bool emptyCatalogue_ = false;

		Button coverbutton_{ {36, 340}, {400, 240}, BLACK, rgb(217,217,217), rgb(217,217,217) };
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

	void SetPackage(Package* package);

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

	BOOK_TITLE::BookTitle* targetedTitle_;

	Package* package_;

	bool emptyCatalogue_ = false;
};

#endif // !TITLE_DETAIL_CARD
