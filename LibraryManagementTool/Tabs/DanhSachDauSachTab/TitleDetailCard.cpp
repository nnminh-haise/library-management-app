#include "TitleDetailCard.hpp"

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::BookDetailCard()
{
	this->Initialize();
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::BookDetailCard(const BookDetailCard& other)
{
	if (this != &other)
	{
		this->~BookDetailCard();

		this->status_ = other.status_;

		this->background_ = other.background_;

		this->bookID_ = other.bookID_;

		this->bookStatus_ = other.bookStatus_;

		this->row_ = other.row_;

		this->column_ = other.column_;

		this->section_ = other.section_;
	}
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::operator=(const BookDetailCard& other)
{
	if (this == &other) { return *this; }

	this->~BookDetailCard();

	this->status_ = other.status_;

	this->background_ = other.background_;

	this->bookID_ = other.bookID_;

	this->bookStatus_ = other.bookStatus_;

	this->row_ = other.row_;

	this->column_ = other.column_;

	this->section_ = other.section_;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::UpdateCard(BOOK::Book* bookPointer)
{
	if (bookPointer == nullptr) { return; }

	std::string bookID = bookPointer->GetID();
	std::string bookStatus = bookPointer->StringfyStatus();
	std::string bookDescription = bookPointer->GetDescription();

	this->bookID_.content_.SetPlaceholder(bookID);
	this->bookStatus_.content_.SetPlaceholder(bookStatus);
	
	std::stringstream ss(bookDescription);
	std::string token{};
	std::string rowValue{}, colValue{}, sectionValue{};

	while (ss >> token)
	{
		if (token == "ROW") { ss >> rowValue; }
		else if (token == "COLUMN") { ss >> colValue; }
		else if (token == "SECTION") { ss >> sectionValue; }
	}

	this->row_.content_.SetPlaceholder(rowValue);
	this->column_.content_.SetPlaceholder(colValue);
	this->section_.content_.SetPlaceholder(sectionValue);

	Stack <AVL_Tree<READER::Reader, int>::Node*> stk;
	AVL_Tree<READER::Reader, int>::Node* p = this->package_->readerList->GetRoot();
	while (true)
	{
		while (p != nullptr)
		{
			stk.Push(p);
			p = p->left_;
		}

		if (stk.Empty() == false)
		{
			p = stk.Pop();
			// NODE MANIPULATION LOGIC PERFORM HERE ------

			auto bookCirculations = p->info_.GetBooksCirculation();
			for (auto bookCirculation = bookCirculations; bookCirculation.First != nullptr; bookCirculation.First = bookCirculation.First->right)
			{
				if (bookCirculation.First->info.GetID().compare(bookID) == 0)
				{
					this->removable_ = false;
				}
			}

			//--------------------------------------------
			p = p->right_;
		}
		else
		{
			break;
		}
	}
	if (!this->removable_)
	{
		this->removavilityIndicator_.SetPlaceholder("Can not be remove!");
	}
	else
	{
		this->removavilityIndicator_.SetPlaceholder("Removable!");
	}
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::SetPackage(Package* package)
{
	this->package_ = package;
}

HELPER::Fill& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_Background()
{
	return this->background_;
}

Button& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_Heading()
{
	return this->heading_;
}

LinkedButton& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_BookID()
{
	return this->bookID_;
}

LinkedButton& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_BookStatus()
{
	return this->bookStatus_;
}

LinkedButton& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_Row()
{
	return this->row_;
}

LinkedButton& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_Column()
{
	return this->column_;
}

LinkedButton& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::DA_Section()
{
	return this->section_;
}

int TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	return 0;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::Initialize()
{
	this->InitializeElements();
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::InitializeElements()
{
	this->background_ = HELPER::Fill(
		HELPER::Coordinate(36, 380),
		400, 160,
		rgb(238, 238, 238),
		rgb(24, 18, 43)
	);

	this->heading_ = Button({36, 340}, {400, 40}, WHITE, rgb(33, 42, 62), rgb(33, 42, 62));
	this->heading_.SetPlaceholder("BOOK'S DETAILS");

	this->bookID_.description_ = Button({ 46, 390 }, { 100, 20 });
	this->bookID_.description_.SetPlaceholder("Book's ID:");
	this->bookID_.content_ = Button({ 46, 410 }, { 120, 45 });
	this->bookID_.description_.SetFillColor(rgb(238, 238, 238));
	this->bookID_.content_.SetFillColor(WHITE);
	this->bookID_.description_.SetBorderColor(rgb(238, 238, 238));
	this->bookID_.content_.SetBorderColor(BLACK);
	this->bookID_.description_.SetTextColor(BLACK);
	this->bookID_.content_.SetTextColor(BLACK);

	this->bookStatus_.description_ = Button({ 176, 390 }, { 100, 20 });
	this->bookStatus_.description_.SetPlaceholder("Status:");
	this->bookStatus_.content_ = Button({ 176, 410 }, { 250, 45 });
	this->bookStatus_.description_.SetFillColor(rgb(238, 238, 238));
	this->bookStatus_.content_.SetFillColor(WHITE);
	this->bookStatus_.description_.SetBorderColor(rgb(238, 238, 238));
	this->bookStatus_.content_.SetBorderColor(BLACK);
	this->bookStatus_.description_.SetTextColor(BLACK);
	this->bookStatus_.content_.SetTextColor(BLACK);

	this->row_.description_ = Button({ 46, 465 }, { 70, 20 });
	this->row_.description_.SetPlaceholder("Row:");
	this->row_.content_ = Button({ 46, 485 }, { 120, 45 });
	this->row_.description_.SetFillColor(rgb(238, 238, 238));
	this->row_.content_.SetFillColor(WHITE);
	this->row_.description_.SetBorderColor(rgb(238, 238, 238));
	this->row_.content_.SetBorderColor(BLACK);
	this->row_.description_.SetTextColor(BLACK);
	this->row_.content_.SetTextColor(BLACK);

	this->column_.description_ = Button({ 176, 465 }, { 70, 20 });
	this->column_.description_.SetPlaceholder("Column:");
	this->column_.content_ = Button({ 176, 485 }, { 120, 45 });
	this->column_.description_.SetFillColor(rgb(238, 238, 238));
	this->column_.content_.SetFillColor(WHITE);
	this->column_.description_.SetBorderColor(rgb(238, 238, 238));
	this->column_.content_.SetBorderColor(BLACK);
	this->column_.description_.SetTextColor(BLACK);
	this->column_.content_.SetTextColor(BLACK);

	this->section_.description_ = Button({ 308, 465 }, { 70, 20 });
	this->section_.description_.SetPlaceholder("Section:");
	this->section_.content_ = Button({ 308, 485 }, { 120, 45 });
	this->section_.description_.SetFillColor(rgb(238, 238, 238));
	this->section_.content_.SetFillColor(WHITE);
	this->section_.description_.SetBorderColor(rgb(238, 238, 238));
	this->section_.content_.SetBorderColor(BLACK);
	this->section_.description_.SetTextColor(BLACK);
	this->section_.content_.SetTextColor(BLACK);

	this->removavilityIndicator_ = Button({ 296, 550 }, { 140, 30 }, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	this->removavilityIndicator_.SetPlaceholder("Removable!");
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::Display()
{
	if (!this->status_) { return; }

	this->background_.Draw();

	this->heading_.Display();
	this->bookID_.Display();
	this->bookStatus_.Display();
	this->row_.Display();
	this->column_.Display();
	this->section_.Display();

	if (this->removable_ == false) { this->removavilityIndicator_.Display(); }
}

int TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::SectionOnAction()
{
	if (!this->status_) { return 0; }

	if (!this->removable_) { return 0; }

	Button* cells[3] = {&this->row_.content_, &this->column_.content_, &this->section_.content_};
	for (int i = 0; i < 3; ++i)
	{
		if (cells[i]->IsHover())
		{
			cells[i]->SetFillColor(rgb(241, 246, 249));
		}
		else if (cells[i]->LeftMouseClicked())
		{
			delay(130);
			this->package_->inputController->Activate(cells[i], cells[i], 3, false, true, false);
		}
		else
		{
			cells[i]->SetFillColor(WHITE);
		}
	}

	return 0;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::SetRemovability(bool value)
{
	this->removable_ = value;
}

bool TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::Removability()
{
	return this->removable_;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::SetBookPointer(BOOK::Book* bookPointer)
{
	this->bookPointer_ = bookPointer;
}

BOOK::Book* TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard::GetBookPointer()
{
	return this->bookPointer_;
}

TitleDetailCard::TitleDetailCard()
{
	this->Initialize();
}

void TitleDetailCard::UpdateCard(BOOK_TITLE::BookTitle* targetedTitle)
{
	std::cerr << "[LOG] Update new card!\n";

	this->targetedTitle_ = targetedTitle;

	this->isbn_.content_.SetPlaceholder(std::format("{}",targetedTitle->GetISBN()));

	this->title_.content_.SetPlaceholder(std::format("{}", targetedTitle->GetTitle()));

	this->category_.content_.SetPlaceholder(targetedTitle->GetCategory());

	this->author_.content_.SetPlaceholder(targetedTitle->GetAuthor());

	this->pageCount_.content_.SetPlaceholder(std::to_string(targetedTitle->GetPageCount()));

	this->publication_.content_.SetPlaceholder(std::to_string(targetedTitle->GetPublicationYear()));

	this->emptyCatalogue_ = (LINKED_LIST::Size(targetedTitle->GetCatalogue()) == 0);
}

void TitleDetailCard::SetPackage(Package* package)
{
	this->package_ = package;
}

int TitleDetailCard::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	return 0;
}

void TitleDetailCard::Initialize()
{
	this->InitializeElements();
}

void TitleDetailCard::InitializeElements()
{
	this->background_ = HELPER::Fill(
		HELPER::Coordinate(36, 120),
		770, 200,
		rgb(238, 238, 238),
		rgb(24, 18, 43)
	);

	this->heading_ = Button({ 36, 120 }, {770, 40}, WHITE, rgb(33, 42, 62), rgb(33, 42, 62));
	this->heading_.SetPlaceholder("TITLE'S DETAILS");

	this->title_.description_ = Button({46, 170}, {100, 20});
	this->title_.description_.SetPlaceholder("Title:");
	this->title_.content_ = Button({ 46, 190 }, { 520, 45 });
	this->title_.description_.SetFillColor(rgb(238, 238, 238));
	this->title_.content_.SetFillColor(WHITE);
	this->title_.description_.SetBorderColor(rgb(238, 238, 238));
	this->title_.content_.SetBorderColor(BLACK);
	this->title_.description_.SetTextColor(BLACK);
	this->title_.content_.SetTextColor(BLACK);
	
	this->category_.description_ = Button({ 576, 170 }, { 100, 20 });
	this->category_.description_.SetPlaceholder("Category:");
	this->category_.content_ = Button({ 576, 190 }, { 220, 45 });
	this->category_.description_.SetFillColor(rgb(238, 238, 238));
	this->category_.content_.SetFillColor(WHITE);
	this->category_.description_.SetBorderColor(rgb(238, 238, 238));
	this->category_.content_.SetBorderColor(BLACK);
	this->category_.description_.SetTextColor(BLACK);
	this->category_.content_.SetTextColor(BLACK);

	this->isbn_.description_ = Button({ 476, 245 }, { 70, 20 });
	this->isbn_.description_.SetPlaceholder("ISBN:");
	this->isbn_.content_ = Button({ 476, 265 }, { 90, 45 });
	this->isbn_.description_.SetFillColor(rgb(238, 238, 238));
	this->isbn_.content_.SetFillColor(WHITE);
	this->isbn_.description_.SetBorderColor(rgb(238, 238, 238));
	this->isbn_.content_.SetBorderColor(BLACK);
	this->isbn_.description_.SetTextColor(BLACK);
	this->isbn_.content_.SetTextColor(BLACK);

	this->author_.description_ = Button({ 46, 245 }, { 100, 20 });
	this->author_.description_.SetPlaceholder("Author:");
	this->author_.content_ = Button({ 46, 265 }, { 420, 45 });
	this->author_.description_.SetFillColor(rgb(238, 238, 238));
	this->author_.content_.SetFillColor(WHITE);
	this->author_.description_.SetBorderColor(rgb(238, 238, 238));
	this->author_.content_.SetBorderColor(BLACK);
	this->author_.description_.SetTextColor(BLACK);
	this->author_.content_.SetTextColor(BLACK);

	this->pageCount_.description_ = Button({ 691, 245 }, { 105, 20 });
	this->pageCount_.description_.SetPlaceholder("Page count:");
	this->pageCount_.content_ = Button({ 691, 265 }, { 105, 45 });
	this->pageCount_.description_.SetFillColor(rgb(238, 238, 238));
	this->pageCount_.content_.SetFillColor(WHITE);
	this->pageCount_.description_.SetBorderColor(rgb(238, 238, 238));
	this->pageCount_.content_.SetBorderColor(BLACK);
	this->pageCount_.description_.SetTextColor(BLACK);
	this->pageCount_.content_.SetTextColor(BLACK);

	this->publication_.description_ = Button({ 576, 245 }, { 105, 20 });
	this->publication_.description_.SetPlaceholder("Publication:");
	this->publication_.content_ = Button({ 576, 265 }, { 105, 45 });
	this->publication_.description_.SetFillColor(rgb(238, 238, 238));
	this->publication_.content_.SetFillColor(WHITE);
	this->publication_.description_.SetBorderColor(rgb(238, 238, 238));
	this->publication_.content_.SetBorderColor(BLACK);
	this->publication_.description_.SetTextColor(BLACK);
	this->publication_.content_.SetTextColor(BLACK);
}

void TitleDetailCard::Display()
{
	if (!this->status_) { return; }

	this->background_.Draw();

	this->heading_.Display();
	this->title_.Display();
	this->isbn_.Display();
	this->category_.Display();
	this->author_.Display();
	this->pageCount_.Display();
	this->publication_.Display();
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::BookDetailCardsController()
{
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::BookDetailCardsController(int catalogueSize)
{
	if (catalogueSize == 0)
	{
		this->emptyCatalogue_ = true;

		this->catalogueSize_ = 0;
	}
	else
	{
		this->catalogueSize_ = catalogueSize;

		this->cards_ = new TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard[catalogueSize];
	}

	this->Initialize();
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::BookDetailCardsController(const BookDetailCardsController& other)
{
	if (this != &other)
	{
		this->~BookDetailCardsController();

		this->status_ = other.status_;

		this->catalogueSize_ = other.catalogueSize_;

		this->activeCardIndex_ = other.activeCardIndex_;

		this->cards_ = new TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard[this->catalogueSize_];
		for (int i = 0; i < this->catalogueSize_; ++i) { this->cards_[i] = other.cards_[i]; }

		for (int i = 0; i < 2; ++i) { this->cardChangeButtons_[i] = other.cardChangeButtons_[i]; }

		this->cardCountIndicator_ = other.cardCountIndicator_;

		this->titlePointer_ = other.titlePointer_;
		
		this->titleCatalogue_ = other.titleCatalogue_;

		this->emptyCatalogue_ = other.emptyCatalogue_;

		this->package_ = other.package_;
	}
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::~BookDetailCardsController()
{
	if (this->catalogueSize_ == 0) { return; }

	delete[] this->cards_;
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::operator=(const BookDetailCardsController& other)
{
	if (this == &other) { return *this; }

	this->~BookDetailCardsController();

	this->status_ = other.status_;

	this->catalogueSize_ = other.catalogueSize_;

	this->activeCardIndex_ = other.activeCardIndex_;

	this->cards_ = new TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard[this->catalogueSize_];
	for (int i = 0; i < this->catalogueSize_; ++i) { this->cards_[i] = other.cards_[i]; }

	for (int i = 0; i < 2; ++i) { this->cardChangeButtons_[i] = other.cardChangeButtons_[i]; }

	this->cardCountIndicator_ = other.cardCountIndicator_;

	this->titlePointer_ = other.titlePointer_;

	this->titleCatalogue_ = other.titleCatalogue_;

	this->emptyCatalogue_ = other.emptyCatalogue_;

	this->package_ = other.package_;
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::operator[](int index)
{
	if (index < 0 || index >= this->catalogueSize_)
	{
		throw std::logic_error("[ERROR] Index out of range! (TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::operator[])");
	}

	return this->cards_[index];
}

Button& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::DA_CardChangeButton(int index)
{
	if (index < 0 || index >= 2)
	{
		throw std::logic_error("[ERROR] Index out of range! (TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::DA_CardChangeButton)");
	}

	return this->cardChangeButtons_[index];
}

Button& TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::DA_CardCountIndicator()
{
	return this->cardCountIndicator_;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::UpdateCard(int cardIndex, BOOK::Book* bookPointer)
{
	if (cardIndex < 0 || cardIndex >= this->catalogueSize_) { throw std::logic_error("[ERROR] Index out of range! (TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::UpdateCard)"); }

	if (bookPointer == nullptr) { return; }

	this->cards_[cardIndex].UpdateCard(bookPointer);
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::CardChangeButtonsOnAction()
{
	int movements[] = { -1, 1 };

	for (int i = 0; i < 2; ++i)
	{
		if (this->cardChangeButtons_[i].IsHover())
		{
			this->cardChangeButtons_[i].SetTextColor(WHITE);
			this->cardChangeButtons_[i].SetFillColor(rgb(130, 170, 227));
		}
		else if (this->cardChangeButtons_[i].LeftMouseClicked())
		{
			delay(130);
			this->cards_[this->activeCardIndex_].Deactivate();
			this->activeCardIndex_ = (this->activeCardIndex_ + movements[i] + this->catalogueSize_) % this->catalogueSize_;
			this->cardCountIndicator_.SetPlaceholder(std::format("{}/{}", this->activeCardIndex_ + 1, this->catalogueSize_));
			this->cards_[this->activeCardIndex_].Activate();
		}
		else
		{
			this->cardChangeButtons_[i].SetTextColor(BLACK);
			this->cardChangeButtons_[i].SetFillColor(rgb(236, 242, 255));
		}
	}
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::CreateCatalogueCards(LINKED_LIST::Pointer catalogue)
{
	this->titleCatalogue_ = catalogue;

	for (int i = 0; i < this->catalogueSize_; ++i)
	{
		this->cards_[i].SetPackage(this->package_);
	}

	this->emptyCatalogue_ = true;

	if (catalogue != nullptr)
	{
		int index = 0;
		for (LINKED_LIST::Pointer currentBook = catalogue; currentBook != nullptr; currentBook = currentBook->next)
		{
			this->cards_[index].SetBookPointer(&currentBook->info);
			this->cards_[index].UpdateCard(&currentBook->info);
			++index;
		}

		this->emptyCatalogue_ = false;
	}

	this->activeCardIndex_ = 0;
	this->cards_[this->activeCardIndex_].Activate();
	this->cardCountIndicator_.SetPlaceholder(std::format("{}/{}", this->activeCardIndex_ + 1, this->catalogueSize_));
}

LINKED_LIST::Pointer TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::GetCatalogueData()
{
	if (!this->status_) { return nullptr; }

	if (this->titlePointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Title's pointer is NULL! (TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::GetCatalogueData)");
	}

	auto titleCatelogue = this->titlePointer_->GetCatalogue();
	int index = 0;
	for (auto p = titleCatelogue; p != nullptr; p = p->next)
	{
		p->info.SetDescription(std::format(
			"ROW {} COLUMN {} SECTION {}",
			this->cards_[index].DA_Row().content_.GetPlaceholder(),
			this->cards_[index].DA_Column().content_.GetPlaceholder(),
			this->cards_[index].DA_Section().content_.GetPlaceholder()
		));

		++index;
	}
	this->titlePointer_->SetCatalogue(titleCatelogue);

	return this->titlePointer_->GetCatalogue();
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::SetPackage(Package* package)
{
	this->package_ = package;

	if (this->cards_ == nullptr) { return; }

	for (int i = 0; i < this->catalogueSize_; ++i)
	{
		this->cards_[i].SetPackage(package);
	}
}

int TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::Size()
{
	return this->catalogueSize_;
}

int TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	if (this->emptyCatalogue_ == false)
	{
		this->CardChangeButtonsOnAction();
	}

	return 0;
}

int TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::CardElementsOnAction()
{
	if (!this->status_) { return 0; }

	int sectionRunningResult = this->cards_[this->activeCardIndex_].SectionOnAction();
	if (sectionRunningResult != 0) { return sectionRunningResult; }

	return 0;
}

bool TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::Removability(int index)
{
	if (index < 0 || index >= this->catalogueSize_)
	{
		throw std::logic_error("[ERROR] Index out of range! (TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::Removability)");
	}

	return this->cards_[index].Removability();
}

int TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::CurrentCardIndex()
{
	return this->activeCardIndex_;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::SetEmptyCatalogue(bool value)
{
	this->emptyCatalogue_ = value;
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::Initialize()
{
	this->InitializeElements();
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::InitializeElements()
{
	//* Initialize Cards
	for (int i = 0; i < this->catalogueSize_; ++i)
	{
		this->cards_[i].Deactivate();
	}

	//* Initialize card change buttons
	std::string placeholders[] = { "<", ">" };
	HELPER::Coordinate topLefts[] = { {36, 550}, {146, 550} };
	for (int i = 0; i < 2; ++i)
	{
		this->cardChangeButtons_[i] = Button(topLefts[i], {50, 30});
		this->cardChangeButtons_[i].SetPlaceholder(placeholders[i]);
		this->cardChangeButtons_[i].SetTextColor(BLACK);
		this->cardChangeButtons_[i].SetFillColor(rgb(236, 242, 255));
		this->cardChangeButtons_[i].SetBorderColor(BLACK);
	}

	this->cardCountIndicator_ = Button({ 86, 550 }, { 60, 30 }, BLACK, WHITE, WHITE);
	this->cardCountIndicator_.SetPlaceholder(std::format("{}/{}", this->activeCardIndex_ + 1, this->catalogueSize_));
}

void TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController::Display()
{
	if (!this->status_) { return; }

	if (this->emptyCatalogue_)
	{
		this->coverbutton_.SetPlaceholder("This title's book catalogue is EMPTY!");
		this->coverbutton_.Display();
		return;
	}

	this->cards_[this->activeCardIndex_].Run();

	this->cardCountIndicator_.Display();

	for (int i = 0; i < 2; ++i) { this->cardChangeButtons_[i].Display(); }
}
