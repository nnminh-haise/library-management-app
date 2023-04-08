#include "DanhSachTheDocGia.h"
#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../TheDocGia/TheDocGia.h"
#include "../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>



void DanhSachTheDocGiaView::CreateDatasheetsFromDatabase(AVL_TREE::Pointer& danhSachThedocGia, DATASHEET::Controler& controler) {
	THE_DOC_GIA_MODULES::LoadDanhSachTheDocGiaFromDB(CONSTANTS::THE_DOC_GIA_DB, danhSachThedocGia);

	int recordCount = 0;
	AVL_TREE::CountNode(danhSachThedocGia, recordCount);
	controler.datasheetCount = recordCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (recordCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1);
	controler.sheets = new DATASHEET::Datasheet[controler.datasheetCount];
	controler.activeSheet = 0;

	for (int i = 0; i < controler.datasheetCount; ++i) {
		controler.sheets[i] = DATASHEET::Datasheet(
			controler.rowCount, controler.columnCount, controler.rowHeight, controler.topLeft,
			(std::string*)THE_DOC_GIA_PROPERTIES::LABEL_PLACEHOLDERS, (int*)THE_DOC_GIA_PROPERTIES::CHARACTER_LIMITS
		);
	}

	STACK::Stack stk;
	STACK::Initialize(stk);
	AVL_TREE::Pointer currentNode = danhSachThedocGia;
	int rowIndicator = 0;
	int sheetIndicator = -1;

	do {
		while (currentNode != nullptr) {
			STACK::Push(stk, currentNode);
			currentNode = currentNode->left;
		}

		if (STACK::IsEmpty(stk) == false) {
			currentNode = STACK::Pop(stk);
			
			//* Logic stays here
			++rowIndicator;
			if (rowIndicator % CONSTANTS::MAX_ROW_COUNT == 1) {
				++sheetIndicator;
			}

			std::string* data = new std::string[controler.columnCount];
			data[0] = std::to_string(rowIndicator);
			data[1] = std::to_string(currentNode->info.GetMaThe());
			data[2] = currentNode->info.GetHo();
			data[3] = currentNode->info.GetTen();
			data[4] = currentNode->info.GetStringfyPhai();
			data[5] = currentNode->info.GetStringfyTrangThai();
			data[6] = "SACH DANG MUON";

			controler.sheets[sheetIndicator].UpdateNewPlaceholder(data, rowIndicator % CONSTANTS::MAX_ROW_COUNT);

			//---

			currentNode = currentNode->right;
		}
		else {
			break;
		}
	} while (true);
}

void DanhSachTheDocGiaView::DatasheetChangeBTNHover(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(130, 170, 227));
}

void DanhSachTheDocGiaView::DatasheetChangeBTNProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(236, 242, 255));
	btn.SetBorderColor(rgb(25, 24, 37));
	btn.SetTextColor(rgb(25, 24, 37));
}

DanhSachTheDocGiaView::DanhSachTheDocGiaView(AVL_TREE::Pointer& danhSachTheDocGia) {
	this->active = false;
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 940);
	HELPER::Coordinate toRightBtnTopLeft(86, 940);

	this->controler = DATASHEET::Controler(CONSTANTS::MAX_ROW_COUNT, THE_DOC_GIA_PROPERTIES::PROPERTIES_COUNT, THE_DOC_GIA_PROPERTIES::ROW_HEIGHT, datasheetTopLeft);
	this->CreateDatasheetsFromDatabase(danhSachTheDocGia, controler);

	this->sheetChange[0] = ELEMENTS::Button(toLeftBtnTopLeft, 50, 30);
	this->sheetChange[1] = ELEMENTS::Button(toRightBtnTopLeft, 50, 30);
	this->sheetChange[0].SetPlaceholder("<");
	this->sheetChange[1].SetPlaceholder(">");
	for (int i = 0; i < 2; ++i) {
		this->DatasheetChangeBTNProperties(this->sheetChange[i]);
	}
}

void DanhSachTheDocGiaView::Run() {
	this->controler.Display();

	for (int i = 0; i < 2; ++i) {
		this->sheetChange[i].Display();
	}


	//* Elements changes logic
	for (int i = 0; i < 2; ++i) {
		if (this->sheetChange[i].IsPointed() && this->sheetChange[i].LeftMouseClicked() == false) {
			this->DatasheetChangeBTNHover(this->sheetChange[i]);
		}
		else if (this->sheetChange[i].LeftMouseClicked()) {
			if (i == 0) {
				if (this->controler.activeSheet == 0) {
					this->controler.activeSheet = this->controler.datasheetCount - 1;
				}
				else {
					--this->controler.activeSheet;
				}
			}
			else {
				if (this->controler.activeSheet == this->controler.datasheetCount - 1) {
					this->controler.activeSheet = 0;
				}
				else {
					++this->controler.activeSheet;
				}
			}
		}
		else {
			this->DatasheetChangeBTNProperties(this->sheetChange[i]);
		}
	}
}
