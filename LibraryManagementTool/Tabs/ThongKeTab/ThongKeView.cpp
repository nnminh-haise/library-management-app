#include "ThongKeView.h"

#include <iostream>
#include <string>
#include <format>

void StatisticTab::TitleBorrowedCountProcess()
{
	this->titleListMap = HashMap < BOOK_TITLE::BookTitle* > (456976, nullptr);
	this->titleBorrowedCountMap = HashMap < int > (456976, 0);

	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		this->titleListMap.Insert(this->titleList->nodes[i]->GetISBN(), this->titleList->nodes[i]);
		this->titleBorrowedCountMap.Insert(this->titleList->nodes[i]->GetISBN(), 0);
	}

	STACK::Stack stk;
	STACK::Initialize(stk);

	AVL_TREE::Pointer reader = *this->readerList;

	do 
	{
		while (reader != nullptr) 
		{
			STACK::Push(stk, reader);
			reader = reader->left;
		}

		if (STACK::IsEmpty(stk) == false) 
		{
			reader = STACK::Pop(stk);
			
			DOUBLE_LINKED_LIST::Controller readerBooksCirculation = reader->info.GetBorrowedBooks();

			std::string bookTitle = {};
			for (DOUBLE_LINKED_LIST::Pointer bookCirculation = readerBooksCirculation.First; bookCirculation != nullptr; bookCirculation = bookCirculation->right)
			{
				if (bookCirculation->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING || bookCirculation->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::RETURNED)
				{
					bookTitle = bookCirculation->info.GetID().substr(0, 4);
					this->titleBorrowedCountMap[bookTitle] = this->titleBorrowedCountMap[bookTitle] + 1;
				}
			}

			reader = reader->right;
		}
		else 
		{
			break;
		}
	} while (true);
}

void StatisticTab::OverdueReaderCountProcess()
{
	STACK::Stack stk;
	STACK::Initialize(stk);

	AVL_TREE::Pointer currentReader = *this->readerList;
	do {
		while (currentReader != nullptr) {
			STACK::Push(stk, currentReader);
			currentReader = currentReader->left;
		}

		if (STACK::IsEmpty(stk) == false) {
			currentReader = STACK::Pop(stk);
			//----------------------------------------

			DOUBLE_LINKED_LIST::Controller readerBookCirculationList = currentReader->info.GetBorrowedBooks();
			
			if (DOUBLE_LINKED_LIST::IsEmpty(readerBookCirculationList) == false)
			{
				for (DOUBLE_LINKED_LIST::Pointer currentBookCirculation = readerBookCirculationList.First; currentBookCirculation != nullptr; currentBookCirculation = currentBookCirculation->right)
				{
					if (currentBookCirculation->info.IsOverdue())
					{
						this->overdueReaders.PushBack(STATISTIC_TAB_MEMBER::OverdueReader(&currentReader->info, &currentBookCirculation->info));
						break;
					}
				}
			}

			//----------------------------------------
			currentReader = currentReader->right;
		}
		else {
			break;
		}
	} while (true);

	//* Sort by overdue day count
	int overdueReadersCount = this->overdueReaders.Size();
	for (int i = 0; i < overdueReadersCount - 1; ++i)
	{
		for (int j = i + 1; j < overdueReadersCount; ++j)
		{
			if (this->overdueReaders[i].book_->CountOverdueDate() > this->overdueReaders[j].book_->CountOverdueDate())
			{
				std::swap(this->overdueReaders[i], this->overdueReaders[j]);
			}
		}
	}
}

void StatisticTab::TitleButtonOnAction()
{
	Button* buttons[2] = { &this->overdueReaderListButton, &this->top10TitleButton };

	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
		{
			if (this->overdueReaderDatasheetController.DisplayStatus() == true)
			{
				buttons[i]->SetFillColor(rgb(73, 84, 100));
				buttons[i]->SetBorderColor(rgb(73, 84, 100));
				buttons[i]->SetTextColor(WHITE);
				continue;
			}
		}
		else
		{
			if (this->top10TitlesDatasheetController.DisplayStatus() == true)
			{
				buttons[i]->SetFillColor(rgb(73, 84, 100));
				buttons[i]->SetBorderColor(rgb(73, 84, 100));
				buttons[i]->SetTextColor(WHITE);
				continue;
			}
		}

		if (buttons[i]->IsHover())
		{
			buttons[i]->SetFillColor(rgb(232, 232, 232));
			buttons[i]->SetBorderColor(rgb(73, 84, 100));
			buttons[i]->SetTextColor(BLACK);
		}
		else if (buttons[i]->LeftMouseClicked())
		{
			delay(50);

			if (i == 0)
			{
				this->overdueReaderDatasheetController.ActivateDatasheets();
				this->top10TitlesDatasheetController.DeactivateDatasheets();
			}
			else
			{
				this->overdueReaderDatasheetController.DeactivateDatasheets();
				this->top10TitlesDatasheetController.ActivateDatasheets();
			}
		}
		else
		{
			buttons[i]->SetFillColor(rgb(73, 84, 100));
			buttons[i]->SetBorderColor(rgb(73, 84, 100));
			buttons[i]->SetTextColor(WHITE);
		}
	}
}

void StatisticTab::CreateOverdueReaderDatasheet()
{
	this->OverdueReaderCountProcess();
	int dataSize = this->overdueReaders.Size();
	this->overdueReaderDatasheetController.SetDatasheetCount(
		dataSize / (STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::MAX_ROW - 1) + (dataSize % (STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::MAX_ROW - 1) == 0 ? 0 : 1)
	);
	this->overdueReaderDatasheetController.InitializeDatasheets();

	this->overdueReaderDatasheetController[0] = DATASHEET::Datasheet(
		overdueReaderDatasheetController.GetRecordCount(),
		overdueReaderDatasheetController.GetAttributeCount(),
		overdueReaderDatasheetController.GetRowHeight(),
		overdueReaderDatasheetController.GetTopLeft(),
		(std::string*)STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
		(int*)STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::CHARACTER_LIMITS
	);

	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;

	for (int i = 0; i < dataSize; ++i)
	{
		++recordIndex;
		if (recordIndex > this->overdueReaderDatasheetController.GetRecordCount() - 1) {
			recordIndex = 1;
		}
		if (recordIndex % (this->overdueReaderDatasheetController.GetRecordCount() - 1) == 1) {
			sheetIndex += 1;
		}

		std::string* data = new std::string[this->overdueReaderDatasheetController.GetAttributeCount()];
		
		data[0] = std::to_string(++order);
		data[1] = this->overdueReaders[i].reader_->GetID();
		data[2] = this->overdueReaders[i].reader_->GetFullName();
		data[3] = this->overdueReaders[i].book_->GetID();
		data[4] = this->titleListMap[this->overdueReaders[i].book_->GetID().substr(0, 4)]->GetTitle();
		data[5] = this->overdueReaders[i].book_->GetBorrowDate().Stringify();
		data[6] = std::to_string(this->overdueReaders[i].book_->CountOverdueDate());

		this->overdueReaderDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}
}

void StatisticTab::CreateTop10TitlesDatasheet()
{
	this->TitleBorrowedCountProcess();
	BOOK_TITLE::BookTitle** newTitleList = new BOOK_TITLE::BookTitle* [this->titleList->numberOfNode];
	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		newTitleList[i] = this->titleList->nodes[i];
	}

	for (int i = 0; i < this->titleList->numberOfNode - 1; ++i)
	{
		for (int j = i + 1; j < this->titleList->numberOfNode; ++j)
		{
			if (this->titleBorrowedCountMap[newTitleList[i]->GetISBN()] < this->titleBorrowedCountMap[newTitleList[j]->GetISBN()])
			{
				std::swap(newTitleList[i], newTitleList[j]);
			}
		}
	}

	int listSize = 10;
	this->top10TitlesDatasheetController.SetDatasheetCount(1);
	this->top10TitlesDatasheetController.InitializeDatasheets();

	this->top10TitlesDatasheetController[0] = DATASHEET::Datasheet(
		top10TitlesDatasheetController.GetRecordCount(),
		top10TitlesDatasheetController.GetAttributeCount(),
		top10TitlesDatasheetController.GetRowHeight(),
		top10TitlesDatasheetController.GetTopLeft(),
		(std::string*)STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
		(int*)STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::CHARACTER_LIMITS
	);

	int recordIndex = 0;
	int sheetIndex = -1;
	int order = 0;

	for (int i = 0; i < 10; ++i)
	{
		++recordIndex;
		if (recordIndex > this->top10TitlesDatasheetController.GetRecordCount() - 1)
		{
			recordIndex = 1;
		}
		if (recordIndex % (this->top10TitlesDatasheetController.GetRecordCount() - 1) == 1)
		{
			sheetIndex += 1;
		}

		std::string* data = new std::string[this->top10TitlesDatasheetController.GetAttributeCount()];
		data[0] = std::to_string(++order);
		data[1] = newTitleList[i]->GetISBN();
		data[2] = newTitleList[i]->GetTitle();
		data[3] = newTitleList[i]->GetAuthor();
		data[4] = newTitleList[i]->GetCategory();
		data[5] = std::to_string(this->titleBorrowedCountMap[newTitleList[i]->GetISBN()]);

		this->top10TitlesDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}

	delete[] newTitleList;
}

void StatisticTab::InittializeTitleButton()
{
	this->overdueReaderListButton = Button(HELPER::Coordinate(300, 115), HELPER::Dimension(500, 50));
	this->overdueReaderListButton.SetFillColor(rgb(73, 84, 100));
	this->overdueReaderListButton.SetBorderColor(rgb(73, 84, 100));
	this->overdueReaderListButton.SetTextColor(WHITE);
	this->overdueReaderListButton.SetPlaceholder("OVERDUE READER LIST");

	this->top10TitleButton = Button(HELPER::Coordinate(999, 115), HELPER::Dimension(500, 50));
	this->top10TitleButton.SetFillColor(rgb(73, 84, 100));
	this->top10TitleButton.SetBorderColor(rgb(73, 84, 100));
	this->top10TitleButton.SetTextColor(WHITE);
	this->top10TitleButton.SetPlaceholder("TOP 10 POPULAR TITLES");
}

StatisticTab::StatisticTab(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList) 
{
	this->readerList = readerList;
	this->titleList = titleList;

	this->displayingDatasheet = 1;

	this->overdueReaderDatasheetController = DATASHEET::Controller(
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::MAX_ROW,
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::PROPERTIES_COUNT,
		DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::TOP_LEFT,
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::DATASHEET_CHANGE_BUTTON_TOP_LEFT
	);

	this->top10TitlesDatasheetController = DATASHEET::Controller(
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::MAX_ROW,
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::PROPERTIES_COUNT,
		DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::TOP_LEFT,
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::DATASHEET_CHANGE_BUTTON_TOP_LEFT
	);

	this->InittializeTitleButton();

	this->overdueReaderDatasheetController.ActivateDatasheets();
	this->top10TitlesDatasheetController.DeactivateDatasheets();
}

void StatisticTab::Run() 
{
	this->overdueReaderListButton.Display();
	this->top10TitleButton.Display();

	this->TitleButtonOnAction();

	if (this->overdueReaderDatasheetController.DisplayStatus() == true)
	{
		this->CreateOverdueReaderDatasheet();
		this->overdueReaderDatasheetController.Display();
		this->overdueReaderDatasheetController.DatasheetChangeButtonUpdate();
	}

	if (this->top10TitlesDatasheetController.DisplayStatus() == true)
	{
		this->CreateTop10TitlesDatasheet();
		this->top10TitlesDatasheetController.Display(false);
	}
}

STATISTIC_TAB_MEMBER::OverdueReader::OverdueReader()
{
	this->reader_ = nullptr;
	this->book_ = nullptr;
}

STATISTIC_TAB_MEMBER::OverdueReader::OverdueReader(READER::Reader* reader, BOOK_CIRCULATION::BookCirculation* book)
{
	this->reader_ = reader;
	this->book_ = book;
}
