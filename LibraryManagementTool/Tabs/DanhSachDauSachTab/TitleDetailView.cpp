#include "TitleDetailView.h"

TitleDetail::TitleDetail() : titlePointer_(nullptr)
{
	this->Initialize();
}

void TitleDetail::SetTitlePointer(BOOK_TITLE::BookTitle* titlePointer)
{
	this->titlePointer_ = titlePointer;

	this->detailCard_.UpdateCard(this->titlePointer_);
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

	this->functionalitySet_.Run();

	this->goBackButton_.Display();
}

TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::FunctionalitySet()
{
	this->Initialize();
}

int TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

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

	for (int i = 0; i < 3; ++i) { this->confirmCovers_[i] = HELPER::Fill({ 576, 360 }, 230, 67, WHITE, WHITE); }
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Reset()
{
	for (int i = 0; i < 3; ++i) { this->infomaticButtons_[i].status_ = false; }
	this->selectingFunction_ = -1;
}

void TITLE_DETAIL_VIEW_COMPONENTS::FunctionalitySet::Display()
{
	if (!this->status_) { return; }

	for (int i = 0; i < 3; ++i)
	{
		if (i == 2 && this->selectingFunction_ == i)
		{
			this->functionalButtons_[i].SetPlaceholder("NO");
		}
		else if (i == 2 && this->selectingFunction_ != 2)
		{
			this->functionalButtons_[i].SetPlaceholder("DELETE BOOK");
		}

		this->functionalButtons_[i].Display();
	}

	if (this->selectingFunction_ == -1)
	{
		for (int i = 0; i < 3; ++i) { this->confirmCovers_[i].Draw(); }
	}
	else
	{
		int displayOptions[] = {-1, 2, 2};

		if (this->infomaticButtons_[this->selectingFunction_].status_)
		{
			this->infomaticButtons_[this->selectingFunction_].Display(displayOptions[this->selectingFunction_]);
			if (this->selectingFunction_ == 0 || this->selectingFunction_ == 2) { this->confirmButtons_[this->selectingFunction_].Display(); }
		}
	}
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

				return i + 1;
			}
			else if (this->functionalButtons_[i].LeftMouseClicked())
			{
				delay(130);
				this->selectingFunction_ = i;
				this->infomaticButtons_[i].status_ = true;

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
