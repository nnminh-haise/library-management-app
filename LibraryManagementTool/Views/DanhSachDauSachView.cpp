#include "DanhSachDauSachView.h"
#include "Elements.h"
#include "../Graphics/graphics.h"
#include "../Helper/Helper.h"
#include "../Helper/ConstantsAndGlobalVariables.h"
#include "../DataStructures/Stack.h"

#include <iostream>
#include <format>
#include <string>



void DanhSachDauSachView::CreateDatasheetsFromDatabase(LINEAR_LIST::LinearList& danhSachDauSach, DATASHEET::Controler& controler) {
	DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(CONSTANTS::DAU_SACH_DB, danhSachDauSach);

	int recordCount = danhSachDauSach.numberOfNode;
	controler.datasheetCount = recordCount / (CONSTANTS::MAX_ROW_COUNT - 1) + (recordCount % (CONSTANTS::MAX_ROW_COUNT - 1) == 0 ? 0 : 1);
	controler.sheets = new DATASHEET::Datasheet[controler.datasheetCount];
	controler.activeSheet = 0;

	for (int i = 0; i < controler.datasheetCount; ++i) {
		controler.sheets[i] = DATASHEET::Datasheet(
			controler.rowCount, controler.columnCount, controler.rowHeight, controler.topLeft,
			(std::string*)DAU_SACH_PROPERTIES::LABEL_PLACEHOLDERS, (int*)DAU_SACH_PROPERTIES::CHARACTER_LIMITS
		);
	}

	int rowIndicator = 0;
	int sheetIndicator = -1;

	for (int i = 0; i < danhSachDauSach.numberOfNode; ++i) {
		++rowIndicator;
		if (rowIndicator % CONSTANTS::MAX_ROW_COUNT == 1) {
			++sheetIndicator;
		}

		std::string* data = new std::string[controler.columnCount];
		data[0] = std::to_string(rowIndicator);
		data[1] = danhSachDauSach.nodes[i]->GetISBN();
		data[2] = danhSachDauSach.nodes[i]->GetTenSach();
		data[3] = std::to_string(danhSachDauSach.nodes[i]->GetSoTrang());
		data[4] = danhSachDauSach.nodes[i]->GetTacGia();
		data[5] = std::to_string(danhSachDauSach.nodes[i]->GetNamXuatBan());
		data[6] = danhSachDauSach.nodes[i]->GetTheLoai();
		data[7] = "DANH MUC SACH";

		controler.sheets[sheetIndicator].UpdateNewPlaceholder(data, rowIndicator % CONSTANTS::MAX_ROW_COUNT);
	}
	
}

void DanhSachDauSachView::DatasheetChangeBTNHover(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(130, 170, 227));
}

void DanhSachDauSachView::DatasheetChangeBTNProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(236, 242, 255));
	btn.SetBorderColor(rgb(25, 24, 37));
	btn.SetTextColor(rgb(25, 24, 37));
}

DanhSachDauSachView::DanhSachDauSachView(LINEAR_LIST::LinearList& danhSachDauSach) {
	this->active = false;
	HELPER::Coordinate datasheetTopLeft(36, 120);
	HELPER::Coordinate toLeftBtnTopLeft(36, 940);
	HELPER::Coordinate toRightBtnTopLeft(86, 940);

	this->controler = DATASHEET::Controler(
		CONSTANTS::MAX_ROW_COUNT, DAU_SACH_PROPERTIES::PROPERTIES_COUNT, DAU_SACH_PROPERTIES::ROW_HEIGHT, datasheetTopLeft
	);
	this->CreateDatasheetsFromDatabase(danhSachDauSach, controler);

	this->sheetChange[0] = ELEMENTS::Button(toLeftBtnTopLeft, 50, 30);
	this->sheetChange[1] = ELEMENTS::Button(toRightBtnTopLeft, 50, 30);
	this->sheetChange[0].SetPlaceholder("<");
	this->sheetChange[1].SetPlaceholder(">");
	for (int i = 0; i < 2; ++i) {
		this->DatasheetChangeBTNProperties(this->sheetChange[i]);
	}
}

void DanhSachDauSachView::Run() {
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
			delay(100);
		}
		else {
			this->DatasheetChangeBTNProperties(this->sheetChange[i]);
		}
	}
}
