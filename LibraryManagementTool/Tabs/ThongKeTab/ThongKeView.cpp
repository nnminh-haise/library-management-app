#include "ThongKeView.h"

#include <iostream>
#include <string>
#include <format>

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

void StatisticTab::TitleButtonOnAction()
{
	Button* buttons[2] = { &this->overdueReaderListButton, &this->top10TitleButton };

	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
		{
			if (this->overdueReadersDatasheet.GetStatus() == true)
			{
				buttons[i]->SetFillColor(rgb(73, 84, 100));
				buttons[i]->SetBorderColor(rgb(73, 84, 100));
				buttons[i]->SetTextColor(WHITE);
				continue;
			}
		}
		else
		{
			if (this->top10TitlesDatasheet.GetStatus() == true)
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
				this->overdueReadersDatasheet.Activate();
				this->overdueReadersDatasheet.CreateDatasheet();
				this->top10TitlesDatasheet.Deactivate();
			}
			else
			{
				this->overdueReadersDatasheet.Deactivate();
				this->top10TitlesDatasheet.Activate();
				this->top10TitlesDatasheet.CreateDatasheet();
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

StatisticTab::StatisticTab(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList) 
{
	this->readerList = readerList;
	this->titleList = titleList;

	this->InittializeTitleButton();

	this->overdueReadersDatasheet = STATISTIC_TAB_MEMBER::OverdueReadersDatasheet(readerList, titleList);
	this->overdueReadersDatasheet.CreateDatasheet();
	this->overdueReadersDatasheet.Activate();

	this->top10TitlesDatasheet = STATISTIC_TAB_MEMBER::Top10TitleDatasheet(readerList, titleList);
}

void StatisticTab::Run() 
{
	this->overdueReaderListButton.Display();
	this->top10TitleButton.Display();

	this->TitleButtonOnAction();
	
	if (this->overdueReadersDatasheet.GetStatus() == true)
	{
		this->overdueReadersDatasheet.Display();
	}

	if (this->top10TitlesDatasheet.GetStatus() == true)
	{
		this->top10TitlesDatasheet.Display();
	}
}

STATISTIC_TAB_MEMBER::Top10TitleDatasheet::Top10TitleDatasheet()
{
	this->readerList = nullptr;
	this->titleList = nullptr;
	this->status = false;
}

STATISTIC_TAB_MEMBER::Top10TitleDatasheet::Top10TitleDatasheet(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList)
{
	this->readerList = readerList;
	this->titleList = titleList;
	this->status = false;
}

void STATISTIC_TAB_MEMBER::Top10TitleDatasheet::CreateDatasheet()
{
	std::cerr << "[LOG] CREATING TOP 10 MOST BORROWED TITLES DATASHEET!\n";

	HashMap <int> titleBorrowedCountMap(456976, -1);
	HashMap <BOOK_TITLE::BookTitle*> titleListMap(456976, nullptr);

	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		titleBorrowedCountMap.Insert(this->titleList->nodes[i]->GetISBN(), 0);
		titleListMap.Insert(this->titleList->nodes[i]->GetISBN(), this->titleList->nodes[i]);
	}

	Stack<AVL_TREE::Pointer> stk;

	AVL_TREE::Pointer reader = *this->readerList;

	do
	{
		while (reader != nullptr)
		{
			stk.Push(reader);
			reader = reader->left;
		}

		if (stk.Empty() == false)
		{
			reader = stk.Pop();

			DOUBLE_LINKED_LIST::Controller readerBooksCirculation = reader->info.GetBooksCirculation();

			std::string bookTitle = {};
			for (DOUBLE_LINKED_LIST::Pointer bookCirculation = readerBooksCirculation.First; bookCirculation != nullptr; bookCirculation = bookCirculation->right)
			{
				if (bookCirculation->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWING || bookCirculation->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::RETURNED)
				{
					bookTitle = bookCirculation->info.GetID().substr(0, 4);
					titleBorrowedCountMap[bookTitle] = titleBorrowedCountMap[bookTitle] + 1;
				}
			}

			reader = reader->right;
		}
		else
		{
			break;
		}
	} while (true);

	BOOK_TITLE::BookTitle** newTitleList = new BOOK_TITLE::BookTitle * [this->titleList->numberOfNode];
	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		newTitleList[i] = this->titleList->nodes[i];
	}

	for (int i = 0; i < this->titleList->numberOfNode - 1; ++i)
	{
		for (int j = i + 1; j < this->titleList->numberOfNode; ++j)
		{
			if (titleBorrowedCountMap[newTitleList[i]->GetISBN()] < titleBorrowedCountMap[newTitleList[j]->GetISBN()])
			{
				std::swap(newTitleList[i], newTitleList[j]);
			}
		}
	}

	this->top10TitlesDatasheetController = DATASHEET::Controller(
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::MAX_ROW,
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::PROPERTIES_COUNT,
		DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::TOP_LEFT,
		STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::DATASHEET_CHANGE_BUTTON_TOP_LEFT
	);

	int listSize = 10;
	this->top10TitlesDatasheetController.SetDatasheetCount(1);
	this->top10TitlesDatasheetController.InitializeDatasheets();

	for (int i = 0; i < this->top10TitlesDatasheetController.GetDatasheetCount(); ++i)
	{
		this->top10TitlesDatasheetController[i] = DATASHEET::Datasheet(
			top10TitlesDatasheetController.GetRecordCount(),
			top10TitlesDatasheetController.GetAttributeCount(),
			top10TitlesDatasheetController.GetRowHeight(),
			top10TitlesDatasheetController.GetTopLeft(),
			(std::string*)STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
			(int*)STATISTIC_TAB_PROPERTIES::TOP_10_TITLES_DATASHEET_PROPERTIES::CHARACTER_LIMITS
		);
	}

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
		data[5] = std::to_string(titleBorrowedCountMap[newTitleList[i]->GetISBN()]);

		this->top10TitlesDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}

	delete[] newTitleList;
	this->top10TitlesDatasheetController.ActivateDatasheets();

	std::cerr << "[LOG] TOP 10 MOST BORROWED TITLES DATASHEET CREATED!\n";
	std::cerr << "----------------------------------------------------\n";
}

void STATISTIC_TAB_MEMBER::Top10TitleDatasheet::Display()
{
	if (this->top10TitlesDatasheetController.DisplayStatus() == false)
	{
		throw std::logic_error("[ERROR] CANNOT DISPLAY DEACTIVATED DATASHEET!\n");
	}

	this->top10TitlesDatasheetController.Display();
	this->top10TitlesDatasheetController.DatasheetChangeButtonUpdate();
}

void STATISTIC_TAB_MEMBER::Top10TitleDatasheet::Activate()
{
	this->status = true;
	this->top10TitlesDatasheetController.ActivateDatasheets();
}

void STATISTIC_TAB_MEMBER::Top10TitleDatasheet::Deactivate()
{
	this->status = false;
	this->top10TitlesDatasheetController.DeactivateDatasheets();
}

bool STATISTIC_TAB_MEMBER::Top10TitleDatasheet::GetStatus()
{
	return this->status;
}

STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::OverdueReadersDatasheet()
{
	this->readerList = nullptr;
	this->titleList = nullptr;
	this->status = false;
}

STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::OverdueReadersDatasheet(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList)
{
	this->readerList = readerList;
	this->titleList = titleList;
	this->status = false;
}

void STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::CreateDatasheet()
{
	std::cerr << "[LOG] CREATING OVERDUE READERS DATASHEET!\n";

	HashMap <BOOK_TITLE::BookTitle*> titleListMap(456976, nullptr);
	DynamicArray <STATISTIC_TAB_MEMBER::OverdueReader> overdueReaders;

	for (int i = 0; i < this->titleList->numberOfNode; ++i)
	{
		titleListMap.Insert(this->titleList->nodes[i]->GetISBN(), this->titleList->nodes[i]);
	}

	Stack<AVL_TREE::Pointer> stk;

	STATISTIC_TAB_MEMBER::OverdueReader overdueReader;

	AVL_TREE::Pointer currentReader = *this->readerList;
	do {
		while (currentReader != nullptr) {
			stk.Push(currentReader);
			currentReader = currentReader->left;
		}

		if (stk.Empty() == false) {
			currentReader = stk.Pop();
			//----------------------------------------

			DOUBLE_LINKED_LIST::Controller readerBookCirculationList = currentReader->info.GetBooksCirculation();

			if (!DOUBLE_LINKED_LIST::Empty(readerBookCirculationList))
			{
				for (DOUBLE_LINKED_LIST::Pointer currentBookCirculation = readerBookCirculationList.First; currentBookCirculation != nullptr; currentBookCirculation = currentBookCirculation->right)
				{
					if (currentBookCirculation->info.IsOverdue())
					{
						overdueReader.bookID = currentBookCirculation->info.GetID();
						overdueReader.bookTitle = titleListMap[currentBookCirculation->info.GetID().substr(0, 4)]->GetTitle();
						overdueReader.borrowDate = currentBookCirculation->info.GetBorrowDate();
						overdueReader.overdueDateCount = currentBookCirculation->info.CountOverdueDate();
						overdueReader.readerID = std::to_string(currentReader->info.GetID());
						overdueReader.readerFullname = currentReader->info.GetFullName();

						overdueReaders.PushBack(overdueReader);
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
	int overdueReadersCount = overdueReaders.Size();
	for (int i = 0; i < overdueReadersCount - 1; ++i)
	{
		for (int j = i + 1; j < overdueReadersCount; ++j)
		{
			if (overdueReaders[i].overdueDateCount > overdueReaders[j].overdueDateCount)
			{
				std::swap(overdueReaders[i], overdueReaders[j]);
			}
		}
	}

	this->overdueReaderDatasheetController = DATASHEET::Controller(
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::MAX_ROW,
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::PROPERTIES_COUNT,
		DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT,
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::TOP_LEFT,
		STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::DATASHEET_CHANGE_BUTTON_TOP_LEFT
	);

	int dataSize = overdueReaders.Size();
	this->overdueReaderDatasheetController.SetDatasheetCount(
		max(1, dataSize / (STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::MAX_ROW - 1) + (dataSize % (STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::MAX_ROW - 1) == 0 ? 0 : 1))
	);
	this->overdueReaderDatasheetController.SetDatasheetCount(1);
	this->overdueReaderDatasheetController.InitializeDatasheets();

	for (int i = 0; i < this->overdueReaderDatasheetController.GetDatasheetCount(); ++i)
	{
		this->overdueReaderDatasheetController[i] = DATASHEET::Datasheet(
			overdueReaderDatasheetController.GetRecordCount(),
			overdueReaderDatasheetController.GetAttributeCount(),
			overdueReaderDatasheetController.GetRowHeight(),
			overdueReaderDatasheetController.GetTopLeft(),
			(std::string*)STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
			(int*)STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::CHARACTER_LIMITS
		);
	}

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
		data[1] = overdueReaders[i].readerID;
		data[2] = overdueReaders[i].readerFullname;
		data[3] = overdueReaders[i].bookID;
		data[4] = overdueReaders[i].bookTitle;
		data[5] = overdueReaders[i].borrowDate.Stringify();
		data[6] = std::to_string(overdueReaders[i].overdueDateCount);

		this->overdueReaderDatasheetController[sheetIndex].UpdateNewPlaceholder(data, recordIndex);
	}

	this->overdueReaderDatasheetController.ActivateDatasheets();

	std::cerr << "[LOG] OVERDUE READERS DATASHEET CREATED!\n";
	std::cerr << "----------------------------------------------------\n";
}

void STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::Display()
{
	if (this->overdueReaderDatasheetController.DisplayStatus() == false)
	{
		throw std::logic_error("[ERROR] CANNOT DISPLAY DEACTIVATED DATASHEET!\n");
	}

	this->overdueReaderDatasheetController.Display();
	this->overdueReaderDatasheetController.DatasheetChangeButtonUpdate();
}

void STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::Activate()
{
	this->status = true;
	this->overdueReaderDatasheetController.ActivateDatasheets();
}

void STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::Deactivate()
{
	this->status = false;
	this->overdueReaderDatasheetController.DeactivateDatasheets();
}

bool STATISTIC_TAB_MEMBER::OverdueReadersDatasheet::GetStatus()
{
	return this->status;
}