#include "TitleDetailView.h"

TitleDetail::TitleDetail() : titlePointer_(nullptr)
{
	this->Initialize();
}

void TitleDetail::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->CleanUp();

	this->titlePointer_ = titlePointer;

	this->detailCard_.Clear();
	this->detailCard_.UpdateCard(this->titlePointer_);

	this->catalogueSection_.SetTitlePointer(this->titlePointer_);
	this->InitializeCatalogueCards();

	this->functionalitySet_.Reset();
	this->functionalitySet_.SetTitlePointer(this->titlePointer_);
	this->functionalitySet_.SetCurrentBook(nullptr);

	this->creatingNewBooksSection_.Reset();
	this->creatingNewBooksSection_.SetTitlePointer(this->titlePointer_);	

	this->updatingBookSection_.Reset();
	this->updatingBookSection_.SetTitlePointer(this->titlePointer_);
}

void TitleDetail::SetPackage(Package* package)
{
	this->package_ = package;

	this->detailCard_.SetPackage(this->package_);

	this->catalogueSection_.SetPackage(this->package_);

	this->functionalitySet_.SetPackage(this->package_);

	this->creatingNewBooksSection_.SetPackage(this->package_);

	this->updatingBookSection_.SetPackage(this->package_);
}

int TitleDetail::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	this->detailCard_.Run();
	if (this->catalogueSection_.Size())
	{
		int currentCatalogueCardIndex = this->catalogueSection_.CurrentCardIndex();
		std::cerr << "[LOG] Displaying book: " << this->catalogueSection_[currentCatalogueCardIndex].DA_BookID().content_.GetPlaceholder() << "\n";
		this->functionalitySet_.SetCurrentBook(
			this->catalogueSection_[currentCatalogueCardIndex].GetBookPointer()
		);
		this->updatingBookSection_.SetBookPointer(this->catalogueSection_[currentCatalogueCardIndex].GetBookPointer());
		this->updatingBookSection_.SetCurrentCatalogueCardPointer(&this->catalogueSection_[currentCatalogueCardIndex]);
	}

	this->catalogueSection_.Run();

	int functionalityReturnSignal = this->functionalitySet_.Run();

	//* Displaying working functionality
	int workingFunction = this->functionalitySet_.WorkingFunctionality();
	switch (workingFunction)
	{
		case (1): {
			this->creatingNewBooksSection_.Activate();
			this->updatingBookSection_.Deactivate();
			
			int creatingNewBooksSectionReturnSignal = this->creatingNewBooksSection_.Run();
			if (creatingNewBooksSectionReturnSignal == 1)
			{
				std::cerr << "[LOG] Recreate title's catalogue display section!\n";
				this->InitializeCatalogueCards();
				this->functionalitySet_.Reset();
			}

			break;
		}
		case (2): { //! External title's catalogue update (external saving)
			this->creatingNewBooksSection_.Deactivate();
			this->updatingBookSection_.Activate();

			int updatingBookSectionReturnSignal = this->updatingBookSection_.Run();
			if (updatingBookSectionReturnSignal == 1)
			{
				std::cerr << "[LOG] Recreate title's catalogue display section!\n";

				LINKED_LIST::Pointer newCatalogue = nullptr;
				LINKED_LIST::Initialize(newCatalogue);

				auto newTitleCatalogue = this->catalogueSection_.GetCatalogueData();
				this->titlePointer_->SetCatalogue(newTitleCatalogue);

				this->InitializeCatalogueCards();
				this->functionalitySet_.Reset();
			}

			break;
		}
		case (3): {
			this->creatingNewBooksSection_.Deactivate();
			this->updatingBookSection_.Deactivate();

			break;
		}
	}

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
	this->detailCard_.SetPackage(this->package_);
	this->detailCard_.Activate();

	this->functionalitySet_.SetTitlePointer(this->titlePointer_);
	this->functionalitySet_.SetCurrentBook(nullptr);
	this->functionalitySet_.Activate();

	this->goBackButton_.SetTopLeft({ 1685, 940 });
	this->goBackButton_.UpdateWithNewTopLeft();
	this->goBackButton_.SetPlaceholder("Back");
}

void TitleDetail::InitializeCatalogueCards()
{
	if (this->titlePointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Title's pointer is NULL! (TitleDetail::InitializeCatalogueCards)");
	}

	if (this->package_ == nullptr)
	{
		throw std::logic_error("[ERROR] Package's pointer is NULL! (TitleDetail::InitializeCatalogueCards)");
	}

	auto titleCatalogue = this->titlePointer_->GetCatalogue();
	int catalogueSize = LINKED_LIST::Size(titleCatalogue);
	this->catalogueSection_ = TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController(catalogueSize);
	this->catalogueSection_.SetPackage(this->package_);
	this->catalogueSection_.SetTitlePointer(this->titlePointer_);
	this->catalogueSection_.CreateCatalogueCards(titleCatalogue);
	this->catalogueSection_.Activate();
}

void TitleDetail::CleanUp()
{
	this->functionalitySet_.Reset();
}

void TitleDetail::Display()
{
	if (!this->status_) { return; }

	this->goBackButton_.Display();
}

TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::FunctionalitySet()
{
	this->Initialize();
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Run()
{
	if (!this->status_) { return 0; }

	if (this->titlePointer_ == nullptr) { return 0; }

	//* Indicating working functionality
	std::cerr << "Working function: " << this->workingFunction_ << "\n";

	if (this->workingFunction_ != -1)
	{
		this->functionalButtons_[this->workingFunction_ - 1].SetTextColor(WHITE);
		this->functionalButtons_[this->workingFunction_ - 1].SetFillColor(rgb(155, 164, 181));
		this->functionalButtons_[this->workingFunction_ - 1].SetPlaceholder("Cancel");
	}

	this->Display();

	// TODO: rewrite this section logic
	int functionalityReturnSignal = this->FunctionalityButtonsOnAction();
	switch (functionalityReturnSignal)
	{
		case (11): {
			return 11; //TODO: return a signal to create new books
			break;
		}
		case (12): {
			return 12; //TODO: return a signal to update current book
			break;
		}
		case (13): {
			return 13; //TODO: return a signal to delete current book
			break;
		}
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
		this->functionalButtons_[i].SetBorderColor(rgb(236, 242, 255));
		this->functionalButtons_[i].SetPlaceholder(placeholders[i]);
	}

	//this->infomaticButtons_[1].content_ = Button({576, 438}, {150, 47}, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	//this->infomaticButtons_[1].content_.SetPlaceholder("Editing this book!");

	//this->infomaticButtons_[2].content_ = Button({ 576, 493 }, { 150, 47 }, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	//this->infomaticButtons_[2].content_.SetPlaceholder("Delete this book?");

	//this->confirmButtons_[2] = Button({ 736, 493 }, { 70, 47 }, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	//this->confirmButtons_[2].SetPlaceholder("YES");
}


void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Reset()
{
	this->workingFunction_ = -1;

	this->Initialize();
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetCurrentBook(BOOK::Book* bookPointer)
{
	this->bookPointer_ = bookPointer;
}

BOOK::Book* TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::GetCurrentBook()
{
	return this->bookPointer_;
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;
}

BOOK_TITLE::BookTitle* TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::GetCurrentTitle()
{
	return this->titlePointer_;
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::SetPackage(Package* package)
{
	this->package_ = package;
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::WorkingFunctionality()
{
	return this->workingFunction_;
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Display()
{
	if (!this->status_) { return 0; }

	for (int i = 0; i < 3; ++i)
	{
		this->functionalButtons_[i].Display();
	}

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::FunctionalityButtonsOnAction()
{
	if (!this->status_) { return 0; }

	std::cerr << "bug: " << (this->bookPointer_ == nullptr) << "\n";

	if (this->bookPointer_ == nullptr)
	{
		int resultValue = this->FunctionButtonOnAction(1);
		if (resultValue) { return resultValue; }
	}
	else
	{
		if (this->workingFunction_ != -1)
		{
			int resultValue = this->FunctionButtonOnAction(this->workingFunction_);
			if (resultValue) { return resultValue; }
		}
		else
		{
			int reusltValue = 0;
			for (int i = 1; i <= 3; ++i)
			{
				reusltValue = this->FunctionButtonOnAction(i);
				if (reusltValue) { return reusltValue; }
			}
		}
	}

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::FunctionButtonOnAction(int indicator)
{
	if (!this->status_) { return 0; }

	//* If this function is working then skip handling mouse action
	if (this->workingFunction_ == indicator)
	{
		if (this->functionalButtons_[indicator - 1].IsHover())
		{
			this->functionalButtons_[indicator - 1].SetTextColor(BLACK);
			this->functionalButtons_[indicator - 1].SetFillColor(rgb(236, 242, 255));
		}
		else if (this->functionalButtons_[indicator - 1].LeftMouseClicked())
		{
			delay(130);

			if (indicator - 1 == 0)
				this->functionalButtons_[indicator - 1].SetPlaceholder("NEW BOOK");
			else if (indicator - 1 == 1)
				this->functionalButtons_[indicator - 1].SetPlaceholder("EDIT BOOK");
			else
				this->functionalButtons_[indicator - 1].SetPlaceholder("DELETE BOOK");

			this->workingFunction_ = -1;
		}
		else
		{
			this->functionalButtons_[indicator - 1].SetTextColor(WHITE);
			this->functionalButtons_[indicator - 1].SetFillColor(rgb(130, 170, 227));
		}

		return 0;
	}

	if (this->functionalButtons_[indicator - 1].IsHover())
	{
		this->workingFunction_ = -1;
		this->functionalButtons_[indicator - 1].SetTextColor(WHITE);
		this->functionalButtons_[indicator - 1].SetFillColor(rgb(130, 170, 227));
	}
	else if (this->functionalButtons_[indicator - 1].LeftMouseClicked())
	{
		delay(130);

		this->workingFunction_ = indicator;

		//* I dunno why the return signal has this formula (LOL). It just came up in my mind when i was thinking
		return 10 + indicator; // return a signal to create new books
	}
	else
	{
		this->functionalButtons_[indicator - 1].SetTextColor(BLACK);
		this->functionalButtons_[indicator - 1].SetFillColor(rgb(236, 242, 255));
	}

	this->workingFunction_ = -1;

	return 0;
}

TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::CreatingNewBooksSection()
{
	this->Initialize();
}

int TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	this->InfomaticButtonOnAction();

	int createNewBooks = this->ConfirmButtonOnAction();
	if (createNewBooks)
	{
		int numberOfNewBooks = std::stoi(this->infomaticButtons_.content_.GetPlaceholder());
		this->newBooksCardsController_ = TITLE_DETAIL_CARD_COMPONENTS::BookDetailCardsController(numberOfNewBooks);
		this->newBooksCardsController_.SetPackage(this->package_);
		this->CreateCatalogue(numberOfNewBooks);
		this->newBooksCardsController_.CreateCatalogueCards(this->newBooks_);
		this->InitializeNewBookCards();
		this->newBooksCardsController_.Activate();
		this->allowCreatingNewBooks_ = true;
	}

	if (this->allowCreatingNewBooks_ && this->newBooksCardsController_.InActive())
	{
		this->newBooksCardsController_.Run();

		this->NewBooksCardsOnAction();

		this->saveButton_.Display();

		int saveButtonOnActionReturnSignal = this->SaveButtonOnAction();
		if (saveButtonOnActionReturnSignal == 1)
		{
			return 1;
		}
	}

	return 0;
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::Reset()
{
	this->allowCreatingNewBooks_ = false;
	this->infomaticButtons_.content_.SetPlaceholder("1");
	this->newBooksCardsController_.Clear();
	this->newBooksCardsController_.Deactivate();
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;
}

BOOK_TITLE::BookTitle* TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::GetCurrentTitle()
{
	return this->titlePointer_;
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::SetPackage(Package* package)
{
	this->package_ = package;
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::Initialize()
{
	this->InitializeElements();
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::InitializeElements()
{
	this->infomaticButtons_.status_ = true;

	this->infomaticButtons_.description_ = Button({576, 360}, {150, 20}, BLACK, WHITE, WHITE);
	this->infomaticButtons_.description_.SetPlaceholder("Number of new books:");

	this->infomaticButtons_.content_ = Button({576, 380}, {150, 47}, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	this->infomaticButtons_.content_.SetPlaceholder("1");

	this->confirmButton_ = Button({736, 380}, {70, 47}, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	this->confirmButton_.SetPlaceholder("CREATE");

	this->saveButton_ = Button({ 176, 900 }, { 100, 40 }, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	this->saveButton_.SetPlaceholder("SAVE");
}

int TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::Display()
{
	if (!this->status_) { return 0; }

	this->infomaticButtons_.Display();

	this->confirmButton_.Display();

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::InfomaticButtonOnAction()
{
	if (!this->status_) { return 0; }

	if (this->package_ == nullptr)
	{
		throw std::logic_error("[ERROR] Package's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::InfomaticButtonOnAction)");
	}

	if (this->infomaticButtons_.content_.IsHover())
	{
		this->infomaticButtons_.content_.SetFillColor(rgb(241, 246, 249));
	}
	else if (this->infomaticButtons_.content_.LeftMouseClicked())
	{
		delay(130);
		this->package_->inputController->Activate(
			&this->infomaticButtons_.content_,
			&this->infomaticButtons_.content_,
			3,
			false,
			true,
			false
		);
	}
	else
	{
		this->infomaticButtons_.content_.SetFillColor(rgb(238, 238, 238));
	}

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::ConfirmButtonOnAction()
{
	if (!this->status_) { return 0; }

	if (this->confirmButton_.IsHover())
	{
		this->confirmButton_.SetFillColor(rgb(145, 216, 228));
	}
	else if (this->confirmButton_.LeftMouseClicked())
	{
		delay(130);

		return 1;
	}
	else
	{
		this->confirmButton_.SetFillColor(rgb(130, 170, 227));
	}

	return 0;
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::CreateCatalogue(int catalogueSize)
{
	if (this->titlePointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Title's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::CreateCatalogue)");
	}

	int newIndex = 1;
	LINKED_LIST::Pointer lastNode = this->titlePointer_->GetCatalogue();
	if (lastNode != nullptr)
	{
		for (; lastNode->next != nullptr; lastNode = lastNode->next);
		std::string lastID = lastNode->info.GetID();
		newIndex = std::stoi(lastID.substr(lastID.find("-") + 1)) + 1;
	}
	std::string titleISBN = this->titlePointer_->GetISBN();

	LINKED_LIST::Initialize(this->newBooks_);

	for (int i = 0; i < catalogueSize; ++i)
	{
		LINKED_LIST::PushBack(
			this->newBooks_, 
			BOOK::Book(
				std::format("{}-{}", titleISBN, newIndex),
				BOOK::Status::AVAILABLE,
				std::format("ROW 0 COLUMN 0 SECTION 0")
			)
		);
		++newIndex;

		this->newBooksCardsController_[i].SetRemovability(true);
	}
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::InitializeNewBookCards()
{
	int cardCount = this->newBooksCardsController_.Size();
	for (int i = 0; i < cardCount; ++i)
	{
		TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard& card = this->newBooksCardsController_[i];

		HELPER::Fill& background = card.DA_Background();
		Button& heading = card.DA_Heading();
		LinkedButton& bookID = card.DA_BookID();
		LinkedButton& bookStatus = card.DA_BookStatus();
		LinkedButton& row = card.DA_Row();
		LinkedButton& column = card.DA_Column();
		LinkedButton& section = card.DA_Section();

		Button& leftCardChangeButton = this->newBooksCardsController_.DA_CardChangeButton(0);
		Button& rightCardChangeButton = this->newBooksCardsController_.DA_CardChangeButton(1);
		Button& cardCountIndicator = this->newBooksCardsController_.DA_CardCountIndicator();

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

		leftCardChangeButton.SetTopLeft({ 36, 845 });
		rightCardChangeButton.SetTopLeft({ 146, 845 });
		cardCountIndicator.SetTopLeft({ 86, 845 });
	}
}

void TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::NewBooksCardsOnAction()
{
	if (!this->status_) { return; }

	if (this->allowCreatingNewBooks_ == false) { return; }

	if (this->newBooks_ == nullptr) { return; }

	if (this->package_ == nullptr)
	{
		throw std::logic_error("[ERROR] Package's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::NewBooksCardsOnAction)");
	}

	int currentCardIndex = this->newBooksCardsController_.CurrentCardIndex();
	Button* cells[3] = {
		&this->newBooksCardsController_[currentCardIndex].DA_Row().content_,
		&this->newBooksCardsController_[currentCardIndex].DA_Column().content_,
		&this->newBooksCardsController_[currentCardIndex].DA_Section().content_
	};
	for (int i = 0; i < 3; ++i)
	{
		if (cells[i]->IsHover())
		{
			cells[i]->SetFillColor(rgb(241, 246, 249));
		}
		else if (cells[i]->LeftMouseClicked())
		{
			delay(130);
			this->package_->inputController->Activate(
				cells[i], 
				cells[i], 
				3, 
				false, 
				true, 
				false
			);
		}
		else
		{
			cells[i]->SetFillColor(WHITE);
		}
	}
}

int TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::SaveButtonOnAction()
{
	if (!this->status_) { return 0; }

	if (this->allowCreatingNewBooks_ == false) { return 0; }

	if (this->newBooks_ == nullptr) { return 0; }

	if (this->titlePointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Title's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::CreatingNewBooksSection::SaveButtonOnAction)");
	}

	if (this->saveButton_.IsHover())
	{
		this->saveButton_.SetFillColor(rgb(145, 216, 228));
	}
	else if (this->saveButton_.LeftMouseClicked())
	{
		delay(130);

		LINKED_LIST::Pointer titleCatalogue = this->titlePointer_->GetCatalogue();

		int index = 0;
		for (auto p = this->newBooks_; p != nullptr; p = p->next)
		{
			p->info.SetDescription(
				std::format(
					"ROW {} COLUMN {} SECTION {}",
					this->newBooksCardsController_[index].DA_Row().content_.GetPlaceholder(),
					this->newBooksCardsController_[index].DA_Column().content_.GetPlaceholder(),
					this->newBooksCardsController_[index].DA_Section().content_.GetPlaceholder()
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
		this->saveButton_.SetFillColor(rgb(130, 170, 227));
	}

	return 0;
}

TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::UpdateBookSection()
{
}

int TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	this->CatalogueCardOnAction();

	if (this->ConfirmButtonOnAction()) //! External saving
	{
		return 1;
	}

	return 0;
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::Reset()
{
	this->Initialize();
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;
}

BOOK_TITLE::BookTitle* TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::GetCurrentTitle()
{
	return this->titlePointer_;
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::SetBookPointer(BOOK::Book* bookPointer)
{
	this->bookPointer_ = bookPointer;
}

BOOK::Book* TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::GetBookPointer()
{
	return this->bookPointer_;
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::SetCurrentCatalogueCardPointer(TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* currentCatalogueCard)
{
	this->currentCatalogueCard_ = currentCatalogueCard;
}

TITLE_DETAIL_CARD_COMPONENTS::BookDetailCard* TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::GetCurrentCatalogueCardPointer()
{
	return this->currentCatalogueCard_;
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::SetPackage(Package* package)
{
	this->package_ = package;
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::Initialize()
{
	this->InitializeElements();
}

void TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::InitializeElements()
{
	this->infomaticButtons_.content_ = Button({576, 438}, {150, 47}, BLACK, rgb(238, 238, 238), rgb(238, 238, 238));
	this->infomaticButtons_.content_.SetPlaceholder("Editing this book!");

	this->confirmButton_ = Button({ 736, 438 }, { 70, 47 }, WHITE, rgb(130, 170, 227), rgb(130, 170, 227));
	this->confirmButton_.SetPlaceholder("SAVE");
}

int TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::Display()
{
	if (!this->status_) { return 0; }

	this->infomaticButtons_.Display();

	this->confirmButton_.Display();

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::ConfirmButtonOnAction()
{
	if (!this->status_) { return 0; }

	if (this->confirmButton_.IsHover())
	{
		this->confirmButton_.SetFillColor(rgb(145, 216, 228));
	}
	else if (this->confirmButton_.LeftMouseClicked())
	{
		delay(130);

		return 1;
	}
	else
	{
		this->confirmButton_.SetFillColor(rgb(130, 170, 227));
	}

	return 0;
}

int TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::CatalogueCardOnAction()
{
	if (!this->status_) { return 0; }

	if (this->titlePointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Title's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::CatalogueCardOnAction)");
	}

	if (this->package_ == nullptr)
	{
		throw std::logic_error("[ERROR] Package's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::CatalogueCardOnAction)");
	}

	if (this->bookPointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Book's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::CatalogueCardOnAction)");
	}

	if (this->currentCatalogueCard_ == nullptr)
	{
		throw std::logic_error("[ERROR] Current catalogue card's pointer is NULL! (TITLE_DETAIL_VIEW_COMPONENTS::UpdateBookSection::CatalogueCardOnAction)");
	}

	Button* cells[3] = {
		&(this->currentCatalogueCard_->DA_Row().content_),
		&(this->currentCatalogueCard_->DA_Column().content_),
		&(this->currentCatalogueCard_->DA_Section().content_)
	};

	for (int i = 0; i < 3; ++i)
	{
		if (cells[i]->IsHover())
		{
			cells[i]->SetFillColor(rgb(241, 246, 249));
		}
		else if (cells[i]->LeftMouseClicked())
		{
			delay(130);
			this->package_->inputController->Activate(
				cells[i],
				cells[i],
				3,
				false,
				true,
				false
			);
		}
		else
		{
			cells[i]->SetFillColor(WHITE);
		}
	}

	return 0;
}
