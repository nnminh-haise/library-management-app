#pragma once

#include "DanhSachDauSachStyling.h"
#include "../../DauSach/DauSach.h"
#include "../../Helper/Package.h"
#include "../UI/Elements.h"
#include "../UI/Button.h"
#include "../UI/Datasheet.h"

namespace DAU_SACH_TAB
{
	/**
	* TODO: Rewrite this class into an template interface
	*/
	class DatasheetProcessor
	{
	public:
		DatasheetProcessor();

		DatasheetProcessor(LINEAR_LIST::LinearList* dataList, DataFilter* dataFilter);

		void AllowCreateDatasheet();

		void CreateDatasheet();

		void SetDataFilter(DataFilter* dataFilter);

		DataFilter* GetDataFilter();

		void SetDataList(LINEAR_LIST::LinearList* dataList);

		LINEAR_LIST::LinearList* GetDataList();

		DataFilter*& AccessDataFilter();

		DATASHEET::Datasheet& AccessCurrentDatasheet();

		void Display();

		void Activate();

		void Deactivate();

		bool InActive();

	public:
		bool active_;

		bool allowCreateDatasheet_;

		DATASHEET::Controller datasheetController_;
		
		DataFilter* dataFilter_;
		
		LINEAR_LIST::LinearList* dataList_;
	};

	/**
	 * TODO: Change this struct into a class
	 * 1. Create necessary member access methods
	 * 2. Re-design the UI
	 * 3. Optimize member's life cycle
	 * 4. Memory optimization
	*/
	struct BookCreatingSection
	{
		BookCreatingSection();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

		private:
		void InitializeElements();

		public:
		bool active_;
		HELPER::Fill background_;
		Button titleButton_;
		Button saveButton_;
		Button inputField_[5];
	};

	/**
	 * TODO: Change this struct into a class
	 * 1. Create necessary member access methods
	 * 2. Re-design the UI
	 * 3. Optimize member's life cycle
	 * 4. Memory optimization
	*/
	struct CatalogueCreatingSection
	{
		CatalogueCreatingSection();

		CatalogueCreatingSection(LINEAR_LIST::LinearList* titleList, ELEMENTS::InputModeController* inputController);

		~CatalogueCreatingSection();

		void InitializeCatalogue(int amount, std::string isbn);

		void InputFieldOnUpdate();

		void SaveButtonOnUpdate();

		void IndexChangeButtonOnAction();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

		private:
		void InitializeElements();

		public:
		LINEAR_LIST::LinearList* titleList_;
		ELEMENTS::InputModeController* inputController_;

		bool active;
		BookCreatingSection* items;
		int itemsCount;
		int activeField;
		Button indexChangeButtons[2];
	};

	/**
	 * TODO: Change this struct into a class
	 * 1. Create necessary member access methods
	 * 2. Re-design the UI
	 * 3. Optimize member's life cycle
	 * 4. Memory optimization
	*/
	struct TitleCreatingSection
	{
		public:
		TitleCreatingSection();

		TitleCreatingSection(Package* package);

		bool Run();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

		bool GoBackButtonOnAction();

		private:
		void InitializeElements();

		bool InputFieldOnUpdate();

		bool CreateCatalogueButtonOnUpdate();

		bool SubmitButtonOnUpdate();

		bool ISBNInputFieldCheckProcess();

		bool CatalogueSizeCheckProcess();

		bool CatalogueInputFieldCheckProcess();

		public:
		Package* package_;

		bool active;
		bool sachAddFieldDisplay;
		HELPER::Fill background;
		HELPER::Fill backdrop;
		Button title;
		Button createCatalogueButton_;
		Button inputField_[7];
		Button alertField_[2];
		Button goBackButton;
		Button submit;

		bool ISBNCheckProcessResult_ = false;
		bool catalogueSizeProcessResult_ = false;
		bool goodInputFieldCheckResult_ = false;
		bool allowCreatingNewTitle_ = false;

		CatalogueCreatingSection catalogueCreatingSection;
	};

	struct TitleDetailDisplayField
	{
		TitleDetailDisplayField();

		void Destructor();

		void Initialize(BOOK_TITLE::BookTitle* title);

		void CreateBookListDatasheet();

		void Activate();

		void Deactivate();

		bool GetStatus();

		void Display();

		void DeleteBookButtonOnAction();

		void ResetDeleteBookButton();

		bool GoBackButtonOnAction();

		bool active;
		BOOK_TITLE::BookTitle* targetedTitle;
		HELPER::Fill background;
		Button title;
		Button titleDetails[5];
		Button goBackBtn;
		DATASHEET::Controller bookListDatasheetController;
		Button deleteBookBtn;
		LINKED_LIST::Pointer deleteBook;
	};

	struct SearchField
	{
	public:
		SearchField();

		SearchField(Package* package, DAU_SACH_TAB::DatasheetProcessor* titleDatasheetPackage);

		void SetSearchData(LINEAR_LIST::LinearList* data);

		void Activate();

		void Deactivate();

		bool GetStatus();

		bool SearchOperation();

		void SearchBoxOnAction();

		void Display();

		bool Run();

	public:
		bool active_ = false;
		bool searching_ = false;
		bool searchFound = false;

		Button title;
		Button searchBox_;

	private:
		bool searchByTitle_ = true;
		bool searchByISBN_ = true;
		bool searchByCategory_ = false;
		bool searchByPublicationYear_ = false;

		LINEAR_LIST::LinearList* data_;
		Package* package_;
		DAU_SACH_TAB::DatasheetProcessor* titleDatasheetPackage_;
	};
}


namespace CATEGORY_LINKED_LIST
{
	struct Node
	{
		std::string info;
		Node* next;

		Node(std::string info, Node* next);
	};
	typedef Node* Pointer;

	void Initialzie(Pointer& First);

	bool Empty(const Pointer& First);

	void PushFront(Pointer& First, std::string info);

	void InsertOrder(Pointer& First, std::string info);

	void Traversal(const Pointer& First);
}


class DauSachTab
{
public:
	DauSachTab(Package* package);

	void Destructor();

	void Run();

private:
	void InitializeFilters();

	void CreateSortedByCategoryTitleList();

	void Initialize();

	void FunctionalButtonOnAction();

	void DatasheetSortingFunctionality();

private:
	bool datasheetDisplayFlag;
	Button functionalButtons[3];

private:
	DAU_SACH_TAB::SearchField titleSearchSection_;

	DAU_SACH_TAB::TitleCreatingSection titleCreatingSection;

	DAU_SACH_TAB::TitleDetailDisplayField titleDetailField;

private:
	bool defaultView_ = true;

	Package* package_;

	DataFilter defaultTitleListFilter_;

	LINEAR_LIST::LinearList sortedByCategoryTitleList_;

	DataFilter sortedByCategoryTitleListFilter_;

	DAU_SACH_TAB::DatasheetProcessor titleDatasheetPackage_;
};

