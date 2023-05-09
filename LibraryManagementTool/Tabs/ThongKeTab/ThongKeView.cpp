#include "ThongKeView.h"

#include <iostream>
#include <string>
#include <format>

void ThongKeView::TitleButtonOnAction()
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

void ThongKeView::CreateOverdueReaderDatasheet()
{
	this->overdueReaderDatasheetController.SetDatasheetCount(1);
	this->overdueReaderDatasheetController.InitializeDatasheets();

	this->overdueReaderDatasheetController[0] = DATASHEET::Datasheet(
		overdueReaderDatasheetController.GetRecordCount(),
		overdueReaderDatasheetController.GetAttributeCount(),
		overdueReaderDatasheetController.GetRowHeight(),
		overdueReaderDatasheetController.GetTopLeft(),
		(std::string*)STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::LABEL_PLACEHOLDERS,
		(int*)STATISTIC_TAB_PROPERTIES::OVERDUE_READER_DATASHEET_PROPERTIES::CHARACTER_LIMITS
	);
}

void ThongKeView::CreateTop10TitlesDatasheet()
{
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

	
}

void ThongKeView::InittializeTitleButton()
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

ThongKeView::ThongKeView(AVL_TREE::Pointer* readerList, LINEAR_LIST::LinearList* titleList) 
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

void ThongKeView::Run() 
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

int Map::HashFunction(std::string combination)
{
	int result = 0;
	int base = 1;

	for (int i = 3; i >= 0; i--)
	{
		int numericalValue = combination[i] - 'A';
		result += numericalValue * base;
		base *= 26;
	}

	return result;
}
