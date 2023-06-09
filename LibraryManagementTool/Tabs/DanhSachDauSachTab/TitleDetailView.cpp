#include "TitleDetailView.h"

TitleDetail::TitleDetail() : titlePointer_(nullptr)
{
	this->Initialize();
}

void TitleDetail::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;

	this->detailCard_.SetPackage(this->package_);
	this->detailCard_.UpdateCard(this->titlePointer_);
	this->functionalitySet_.SetPackage(this->package_);
	this->functionalitySet_.SetTitlePointer(this->titlePointer_);
}

void TitleDetail::SetPackage(Package* package)
{
	this->package_ = package;
}

int TitleDetail::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	if (this->GoBackButtonOnAction())
	{
		this->CleanUp();

		return -1;
	}

	return 0;
}

void TitleDetail::Initialize()
{
	this->InitializeElements();
}

void TitleDetail::InitializeElements()
{
	this->detailCard_.Activate();
	this->detailCard_.SetPackage(this->package_);

	this->functionalitySet_.SetPackage(this->package_);
	this->functionalitySet_.Activate();

	this->goBackButton_.SetTopLeft({ 1685, 940 });
	this->goBackButton_.UpdateWithNewTopLeft();
	this->goBackButton_.SetPlaceholder("Back");
}

void TitleDetail::CleanUp()
{
	this->functionalitySet_.Reset();
}

void TitleDetail::Display()
{
	if (!this->status_) { return; }

	this->detailCard_.Run();

	int currentCardIndex = this->detailCard_.DA_CatalogueController().CurrentCardIndex();
	bool bookRemovability = this->detailCard_.DA_CatalogueController().Removability(currentCardIndex);
	auto removingBook = this->detailCard_.DA_CatalogueController()[currentCardIndex].GetBookPointer();

	this->functionalitySet_.SetRemovability(bookRemovability);
	if (bookRemovability == false)
	{
		this->functionalitySet_.SetRemoveBook(nullptr);
	}
	else
	{
		this->functionalitySet_.SetRemoveBook(removingBook);
	}
	int FunctionalitySetRunningResult = this->functionalitySet_.Run();
	if (FunctionalitySetRunningResult == 11) //* Update cards after adding new books
	{
		this->detailCard_.UpdateCard(this->titlePointer_);
	}
	else if (FunctionalitySetRunningResult == 13) //* Update cards after remove book
	{
		this->detailCard_.UpdateCard(this->titlePointer_);
	}
	else if (FunctionalitySetRunningResult == 2)
	{
		std::cerr << "edit!\n";
		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController& catalogueController = this->detailCard_.DA_CatalogueController();
		catalogueController.SetPackage(this->package_);
		catalogueController.CardElementsOnAction();
	}
	else if (FunctionalitySetRunningResult == 3)
	{
		std::cerr << "delete!\n";
	}


	//! This section may cause performance bottle necking
	//! <
	TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController& catalogueController = this->detailCard_.DA_CatalogueController();
	if (catalogueController.Size())
	{
		int index = 0;
		auto updatedCatalogue = this->titlePointer_->GetCatalogue();

		for (auto p = updatedCatalogue; p != nullptr; p = p->next)
		{
			p->info.SetDescription(std::format(
				"ROW {} COLUMN {} SECTION {}",
				catalogueController[index].DA_Row().content_.GetPlaceholder(),
				catalogueController[index].DA_Column().content_.GetPlaceholder(),
				catalogueController[index].DA_Section().content_.GetPlaceholder()
			));
			++index;
		}
		this->titlePointer_->SetCatalogue(updatedCatalogue);
	}
	//! />

	this->goBackButton_.Display();
}

TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::FunctionalitySet()
{
	this->Initialize();
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Run()
{
	if (!this->status_) { return 0; }

	std::cerr << "Removability: " << this->removability_ << "\n";

	int displayingResult = this->Display(this->removability_);
	if (displayingResult == 11) // added new books -> re-create title's details
	{
		return 11;
	}
	else if (displayingResult == 13)
	{
		return 13;
	}

	int functionChoice = this->FunctionalityButtonsOnAction();
	if (functionChoice != 0)
	{
		return functionChoice;
	}

	return 0;
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Initialize()
{
	this->InitializeElements();
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::InitializeElements()
{
	std::string placeholders[] = { "NEW BOOK", "EDIT BOOK", "DELETE BOOK" };
	HELPER::Coordinate topLefts[] = { {446, 380}, {446, 436}, {446, 493} };
	for (int i = 0; i < 3; ++i)
	{
		this->functionalButtons_[i] = Button(topLefts[i], {120, 47});
		this->functionalButtons_[i].SetTextColor(BLACK);
		this->functionalButtons_[i].SetFillColor(rgb(236, 242, 255));
		this->functionalButtons_[i].SetBorderColor(BLACK);
		this->functionalButtons_[i].SetPlaceholder(placeholders[i]);
	}

	this->infomaticButtons_[0].description_ = Button({576, 360}, {150, 20}, BLACK, WHITE, WHITE);
	this->infomaticButtons_[0].description_.SetPlaceholder("Number of new books:");
	this->infomaticButtons_[0].content_ = Button({576, 380}, {150, 47}, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	this->infomaticButtons_[0].content_.SetPlaceholder("2");
	this->infomaticButtons_[0].status_ = false;

	this->infomaticButtons_[1].content_ = Button({576, 438}, {150, 47}, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	this->infomaticButtons_[1].content_.SetPlaceholder("Editing this book!");
	this->infomaticButtons_[0].status_ = false;

	this->infomaticButtons_[2].content_ = Button({ 576, 493 }, { 150, 47 }, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	this->infomaticButtons_[2].content_.SetPlaceholder("Delete this book?");
	this->infomaticButtons_[0].status_ = false;

	this->confirmButtons_[0] = Button({736, 380}, {70, 47}, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	this->confirmButtons_[0].SetPlaceholder("CREATE");

	this->confirmButtons_[2] = Button({ 736, 493 }, { 70, 47 }, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	this->confirmButtons_[2].SetPlaceholder("YES");

	this->addNewBooksButton_ = Button({ 176, 900 }, { 100, 40 }, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	this->addNewBooksButton_.SetPlaceholder("ADD BOOKS");
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::InitializeNewBookCards()
{
	int cardCount = this->newBookCards_.Size();
	for (int i = 0; i < cardCount; ++i)
	{
		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard& card = this->newBookCards_[i];

		HELPER::Fill& background = card.DA_Background();
		Button& heading = card.DA_Heading();
		LinkedButton& bookID = card.DA_BookID();
		LinkedButton& bookStatus = card.DA_BookStatus();
		LinkedButton& row = card.DA_Row();
		LinkedButton& column = card.DA_Column();
		LinkedButton& section = card.DA_Section();

		Button& leftCardChangeButton = this->newBookCards_.DA_CardChangeButton(0);
		Button& rightCardChangeButton = this->newBookCards_.DA_CardChangeButton(1);
		Button& cardCountIndicator = this->newBookCards_.DA_CardCountIndicator();

		background = HELPER::Fill(
			HELPER::Coordinate(36, 675),
			400, 160,
			rgb(238, 238, 238),
			rgb(24, 18, 43)
		);

		heading = Button({ 36, 635 }, { 400, 40 }, WHITE, rgb(33, 42, 62), rgb(33, 42, 62));
		heading.SetPlaceholder("BOOK'S DETAILS");

		bookID.description_.SetTopLeft({ 46, 685 });
		bookID.content_.SetTopLeft({ 46, 705 });

		bookStatus.description_.SetTopLeft({ 176, 685 });
		bookStatus.content_.SetTopLeft({ 176, 705 });

		row.description_.SetTopLeft({ 46, 760 });
		row.content_.SetTopLeft({ 46, 780 });

		column.description_.SetTopLeft({ 176, 760 });
		column.content_.SetTopLeft({ 176, 780 });

		section.description_.SetTopLeft({ 308, 760 });
		section.content_.SetTopLeft({ 308, 780 });

		leftCardChangeButton.SetTopLeft({36, 845});
		rightCardChangeButton.SetTopLeft({ 146, 845 });
		cardCountIndicator.SetTopLeft({ 86, 845 });
	}
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Reset()
{
	for (int i = 0; i < 3; ++i) { this->infomaticButtons_[i].status_ = false; }
	this->selectingFunction_ = -1;
	this->newBookCards_.Deactivate();
	this->infomaticButtons_[0].content_.SetPlaceholder("2");
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetPackage(Package* package)
{
	this->package_ = package;
}

bool TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetRemovability(bool value)
{
	return this->removability_ = value;
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetRemoveBook(BOOK::Book* bookPointer)
{
	this->bookPointer_ = bookPointer;
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Display(bool removable)
{
	if (!this->status_) { return 0; }

	for (int i = 0; i < 3; ++i)
	{
		if (i == 2 && removable == true && this->selectingFunction_ == i)
		{
			this->functionalButtons_[i].SetPlaceholder("NO");
		}
		else if (i == 2 && this->selectingFunction_ == 2 && this->removability_ == false)
		{
			this->functionalButtons_[i].SetPlaceholder("DELETE BOOK");
			this->functionalButtons_[i].SetTextColor(BLACK);
			this->functionalButtons_[i].SetFillColor(rgb(236, 242, 255));
			this->selectingFunction_ = -1;
		}
		else if (i == 2 && this->selectingFunction_ != 2)
		{
			this->functionalButtons_[i].SetPlaceholder("DELETE BOOK");
		}

		if (i == 1 && this->selectingFunction_ == i)
		{
			this->functionalButtons_[i].SetPlaceholder("SAVE");
		}
		else if (i == 1 && this->selectingFunction_ != 1)
		{
			this->functionalButtons_[i].SetPlaceholder("EDIT BOOK");
		}

		this->functionalButtons_[i].Display();
	}

	if (this->selectingFunction_ != -1)
	{
		if (this->removability_ == true)
		{
			int displayOptions[] = {-1, 2, 2};

			if (this->infomaticButtons_[this->selectingFunction_].status_)	
			{
				this->infomaticButtons_[this->selectingFunction_].Display(displayOptions[this->selectingFunction_]);
				if (this->selectingFunction_ == 0 || this->selectingFunction_ == 2) { this->confirmButtons_[this->selectingFunction_].Display(); }
				
				if (this->selectingFunction_ == 0)
				{
					this->NewBookFunctionOnAction();
				}
				else if (this->selectingFunction_ == 2)
				{
					if (this->RemoveBookFunctionOnAction())
					{
						return 13;
					}
				}
			}
		}
	}

	if (this->newBookCards_.InActive())
	{
		this->newBookCards_.Run();
		this->newBookCards_.CardElementsOnAction();

		this->addNewBooksButton_.Display();
		if (this->AddBooksButtonOnAction())
		{
			return 11;
		}
	}

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::FunctionalityButtonsOnAction()
{
	if (!this->status_) { return 0; }

	if (this->selectingFunction_ != -1)
	{
		if (this->functionalButtons_[this->selectingFunction_].IsHover())
		{

		}
		else if (this->functionalButtons_[this->selectingFunction_].LeftMouseClicked())
		{
			delay(130);

			if (this->selectingFunction_ == 0)
			{
				this->infomaticButtons_[0].status_ = false;
				this->newBookCards_.Deactivate();
			}


			this->selectingFunction_ = -1;
		}
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				if (i != this->selectingFunction_)
				{
					this->functionalButtons_[i].SetTextColor(BLACK);
					this->functionalButtons_[i].SetFillColor(rgb(236, 242, 255));
				}
			}
		}

		return this->selectingFunction_ + 1;
	}
	else
	{
		for (int i = 0; i < 3; ++i)
		{
			if (this->functionalButtons_[i].IsHover())
			{
				if (i == 2 && this->removability_ == false)
				{
					this->selectingFunction_ = -1;
					this->functionalButtons_[i].SetTextColor(BLACK);
					this->functionalButtons_[i].SetFillColor(rgb(236, 242, 255));

					continue;
				}

				this->selectingFunction_ = -1;
				this->functionalButtons_[i].SetTextColor(WHITE);
				this->functionalButtons_[i].SetFillColor(rgb(130, 170, 227));
			}
			else if (i == 0 && this->functionalButtons_[i].RightMouseClicked())
			{
				delay(130);
				this->selectingFunction_ = i;
				this->infomaticButtons_[i].status_ = true;

				return i + 1;
			}
			else if (i == 0 && this->functionalButtons_[i].LeftMouseClicked())
			{
				delay(130);
				this->selectingFunction_ = i;
				this->infomaticButtons_[i].status_ = false;

				this->newBookCards_ = TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController(1);
				this->newBookCards_.SetPackage(this->package_);
				this->InitializeNewBookCards();
				LINKED_LIST::Pointer lastNode = this->titlePointer_->GetCatalogue();
				
				if (lastNode == nullptr) { continue; }

				for (; lastNode->next != nullptr; lastNode = lastNode->next);
				std::string titleISBN = this->titlePointer_->GetISBN();
				std::string lastID = lastNode->info.GetID();
				int newIndex = std::stoi(lastID.substr(lastID.find("-") + 1)) + 1;

				this->newBooks_ = nullptr;
				LINKED_LIST::Initialize(newBooks_);
				for (int i = 0; i < 1; ++i)
				{
					LINKED_LIST::PushBack(newBooks_, BOOK::Book(std::format("{}-{}", titleISBN, newIndex++), BOOK::Status::AVAILABLE, "ROW 0 COLUMN 0 SECTION 0"));
				}
				
				this->newBookCards_.CreateCatalogueCards(newBooks_);
				this->newBookCards_.Activate();

				return i + 1;
			}
			else if (this->functionalButtons_[i].LeftMouseClicked())
			{
				delay(130);
				this->selectingFunction_ = i;
				this->infomaticButtons_[i].status_ = true;

				if (i == 2 && this->removability_ == false)
				{
					this->selectingFunction_ = -1;
					this->functionalButtons_[i].SetTextColor(BLACK);
					this->functionalButtons_[i].SetFillColor(rgb(236, 242, 255));
					return 0;
				}

				return i + 1;
			}
			else
			{
				this->selectingFunction_ = -1;
				this->functionalButtons_[i].SetTextColor(BLACK);
				this->functionalButtons_[i].SetFillColor(rgb(236, 242, 255));
			}
		}
	}

	return 0;
}

bool TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::NewBookFunctionOnAction()
{
	if (!this->status_) { return false; }

	if (this->infomaticButtons_[0].content_.IsHover())
	{
		this->infomaticButtons_[0].content_.SetFillColor(rgb(241, 246, 249));
	}
	else if (this->infomaticButtons_[0].content_.LeftMouseClicked())
	{
		delay(130);
		this->package_->inputController->Activate(
			&this->infomaticButtons_[0].content_, &this->infomaticButtons_[0].content_,
			3, false, true, false
		);
	}
	else
	{
		this->infomaticButtons_[0].content_.SetFillColor(rgb(238, 238, 238));
	}

	if (this->confirmButtons_[0].IsHover())
	{
		this->confirmButtons_[0].SetFillColor(rgb(145, 216, 228));
	}
	else if (this->confirmButtons_[0].LeftMouseClicked())
	{
		delay(130);
		int numberOfNewBook = std::stoi(this->infomaticButtons_[0].content_.GetPlaceholder());
		this->newBookCards_ = TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController(numberOfNewBook);
		this->newBookCards_.SetPackage(this->package_);
		this->InitializeNewBookCards();
		LINKED_LIST::Pointer lastNode = this->titlePointer_->GetCatalogue();

		for (; lastNode->next != nullptr; lastNode = lastNode->next);
		std::string titleISBN = this->titlePointer_->GetISBN();
		std::string lastID = lastNode->info.GetID();
		int newIndex = std::stoi(lastID.substr(lastID.find("-") + 1)) + 1;

		this->newBooks_ = nullptr;
		LINKED_LIST::Initialize(newBooks_);
		for (int i = 0; i < numberOfNewBook; ++i)
		{
			LINKED_LIST::PushBack(
				newBooks_, 
				BOOK::Book(
					std::format("{}-{}", titleISBN, newIndex++),
					BOOK::Status::AVAILABLE,
					std::format("ROW 0 COLUMN 0 SECTION 0")
				)
			);
		}

		this->newBookCards_.CreateCatalogueCards(newBooks_);
		this->newBookCards_.Activate();
	}
	else
	{
		this->confirmButtons_[0].SetFillColor(rgb(130, 170, 227));
	}

	return false;
}

bool TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::AddBooksButtonOnAction()
{
	if (!this->status_) { return false; }

	if (this->addNewBooksButton_.IsHover())
	{
		this->addNewBooksButton_.SetFillColor(rgb(145, 216, 228));
	}
	else if (this->addNewBooksButton_.LeftMouseClicked())
	{
		delay(130);
		LINKED_LIST::Pointer titleCatalogue = this->titlePointer_->GetCatalogue();

		int index = 0;
		for (auto p = this->newBooks_; p != nullptr; p = p->next)
		{
			p->info.SetDescription(
				std::format(
					"ROW {} COLUMN {} SECTION {}",
					this->newBookCards_[index].DA_Row().content_.GetPlaceholder(),
					this->newBookCards_[index].DA_Column().content_.GetPlaceholder(),
					this->newBookCards_[index].DA_Section().content_.GetPlaceholder()
				)
			);

			++index;
		}

		LINKED_LIST::Append(titleCatalogue, this->newBooks_);
		this->titlePointer_->SetCatalogue(titleCatalogue);
		this->Reset();

		return true;
	}
	else
	{
		this->addNewBooksButton_.SetFillColor(rgb(130, 170, 227));
	}

	return false;
}

bool TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::RemoveBookFunctionOnAction()
{
	if (!this->status_) { return false; }

	if (this->confirmButtons_[2].IsHover())
	{
		this->confirmButtons_[2].SetFillColor(rgb(33, 42, 62));
	}
	else if (this->confirmButtons_[2].LeftMouseClicked())
	{
		delay(130);
		
		if (this->bookPointer_ != nullptr)
		{
			std::cerr << "[LOG] Removing\n";

			auto titleCatalogue = this->titlePointer_->GetCatalogue();
			bool removeStatus = LINKED_LIST::DeleteAt(titleCatalogue, *this->bookPointer_);
			if (removeStatus)
			{
				std::cerr << "SUCCESS!\n";
			}
			else
			{
				std::cerr << "FAILED!\n";
			}
			this->titlePointer_->SetCatalogue(titleCatalogue);
		}
		return true;
	}
	else
	{
		this->confirmButtons_[2].SetFillColor(rgb(130, 170, 227));
	}

	return false;
}
