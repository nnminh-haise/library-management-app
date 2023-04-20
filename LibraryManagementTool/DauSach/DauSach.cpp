#include "DauSach.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>

SACH::Sach::Sach() {
	this->MaSach = std::string();
	this->TrangThai = SACH::TrangThaiSach::CHO_MUON_DUOC;
	this->ViTri = std::string();
}

SACH::Sach::Sach(std::string MaSach, SACH::TrangThaiSach TrangThai, std::string ViTri) {
	this->MaSach = MaSach;
	this->TrangThai = TrangThai;
	this->ViTri = ViTri;
}

void SACH::Sach::SetMaSach(std::string MaSach) {
	this->MaSach = MaSach;
}

std::string SACH::Sach::GetMaSach() {
	return this->MaSach;
}

void SACH::Sach::SetTrangThai(TrangThaiSach TrangThai) {
	this->TrangThai = TrangThai;
}

SACH::TrangThaiSach SACH::Sach::GetTrangThai() {
	return this->TrangThai;
}

std::string SACH::Sach::GetStringfyTrangThai() {
	switch (this->TrangThai) {
		case(SACH::TrangThaiSach::CHO_MUON_DUOC):
			return "CHO MUON DUOC";
		case(SACH::TrangThaiSach::DA_CO_DOC_GIA_MUON):
			return "DA CO DOC GIA MUON";
		case(SACH::TrangThaiSach::DA_THANH_LY):
			return "DA THANH LY";
	}
	return std::string();
}

void SACH::Sach::SetViTri(std::string ViTri) {
	this->ViTri = ViTri;
}

std::string SACH::Sach::GetViTri() {
	return this->ViTri;
}

LINKED_LIST::Node::Node() : info(SACH::Sach()), next(nullptr) {
}

LINKED_LIST::Node::Node(SACH::Sach info, LINKED_LIST::Node* next) : info(info), next(next) {
}

void LINKED_LIST::Initialize(LINKED_LIST::Controller& controller) {
	controller.first = nullptr;
}

bool LINKED_LIST::IsEmpty(const LINKED_LIST::Controller& controller) {
	return controller.first == nullptr;
}

int LINKED_LIST::Size(const Controller& controller) {
	int counter = 0;
	for (LINKED_LIST::Pointer p = controller.first; p != nullptr; p = p->next) {
		++counter;
	}

	return counter;
}

void LINKED_LIST::InsertItemLast(LINKED_LIST::Controller& controller, SACH::Sach item) {
	LINKED_LIST::Pointer newNode = new Node(item, nullptr);

	++controller.total;
	if (item.GetTrangThai() == SACH::TrangThaiSach::DA_CO_DOC_GIA_MUON) {
		++controller.borrowed;
	}
	else if (item.GetTrangThai() == SACH::TrangThaiSach::DA_THANH_LY) {
		++controller.sold;
	}

	if (LINKED_LIST::IsEmpty(controller)) {
		controller.first = newNode;
	}
	else {
		LINKED_LIST::Pointer Last = controller.first;
		for (; Last->next != nullptr; Last = Last->next);
		Last->next = newNode;
	}
}


DAU_SACH::DauSach::DauSach() {
	this->ISBN = std::string();
	this->TenSach = std::string();
	this->SoTrang = 0;
	this->TacGia = std::string();
	this->NamXuatBan = 0;
	this->TheLoai = std::string();
	this->DanhMucSach.first = nullptr;
}

DAU_SACH::DauSach::DauSach(std::string ISBN, std::string TenSach, int SoTrang, std::string TacGia, int NamXuatBan, std::string TheLoai, LINKED_LIST::Controller DanhMucSach) {
	this->ISBN = ISBN;
	this->TenSach = TenSach;
	this->SoTrang = SoTrang;
	this->TacGia = TacGia;
	this->NamXuatBan = NamXuatBan;
	this->TheLoai = TheLoai;
	this->DanhMucSach = DanhMucSach;
}

void DAU_SACH::DauSach::SetISBN(std::string ISBN) {
	this->ISBN = ISBN;
}

std::string DAU_SACH::DauSach::GetISBN() {
	return this->ISBN;
}

void DAU_SACH::DauSach::SetTenSach(std::string TenSach) {
	this->TenSach = TenSach;
}

std::string DAU_SACH::DauSach::GetTenSach() {
	return this->TenSach;
}

void DAU_SACH::DauSach::SetSoTrang(int soTrang) {
	this->SoTrang = soTrang;
}

int DAU_SACH::DauSach::GetSoTrang() {
	return this->SoTrang;
}

void DAU_SACH::DauSach::SetTacGia(std::string TacGia) {
	this->TacGia = TacGia;
}

std::string DAU_SACH::DauSach::GetTacGia() {
	return this->TacGia;
}

void DAU_SACH::DauSach::SetNamXuatBan(int NamXuatBan) {
	this->NamXuatBan = NamXuatBan;
}

int DAU_SACH::DauSach::GetNamXuatBan() {
	return this->NamXuatBan;
}

void DAU_SACH::DauSach::SetTheLoai(std::string TheLoai) {
	this->TheLoai = TheLoai;
}

std::string DAU_SACH::DauSach::GetTheLoai() {
	return this->TheLoai;
}

void DAU_SACH::DauSach::SetDanhMucSach(LINKED_LIST::Controller DanhMucSach) {
	this->DanhMucSach = DanhMucSach;
}

LINKED_LIST::Controller DAU_SACH::DauSach::GetDanhMucSach() {
	return this->DanhMucSach;
}

void DAU_SACH::DauSach::Log() {
	std::cerr << std::format("___ Dau Sach ___\n");
	std::cerr << std::format("ISBN    : {}\n", this->ISBN);
	std::cerr << std::format("Ten sach: {}\n", this->TenSach);
	std::cerr << std::format("So trang: {}\n", this->SoTrang);
	std::cerr << std::format("Tac gia : {}\n", this->TacGia);
	std::cerr << std::format("NXB     : {}\n", this->NamXuatBan);
	std::cerr << std::format("The loai: {}\n", this->TheLoai);
	std::cerr << std::format("----------------\n");
}

LINEAR_LIST::LinearList::LinearList() {
	this->numberOfNode = 0;
	for (int i = 0; i < LINEAR_LIST::MAX_SIZE; ++i) {
		this->nodes[i] = nullptr;
	}
}

void LINEAR_LIST::Initialize(LINEAR_LIST::LinearList& list) {
	list.numberOfNode = 0;
	for (int i = 0; i < LINEAR_LIST::MAX_SIZE; ++i) {
		list.nodes[i] = nullptr;
	}
}

bool LINEAR_LIST::IsEmpty(const LinearList& list) {
	return list.numberOfNode == 0;
}

bool LINEAR_LIST::IsFull(const LinearList& list) {
	return list.numberOfNode == MAX_SIZE;
}

bool LINEAR_LIST::InsertItem(LINEAR_LIST::LinearList& list, DAU_SACH::DauSach* item, int position) {
	if (LINEAR_LIST::IsFull(list)) {
		std::cerr << std::format("[ERROR] LIST IS FULL CANNOT INSERT NEW ELEMENT!\nSUGGEST CREATE A NEW LIST WITH BIGGER SIZE!\n");
		return false;
	}

	if (position < 0 || position >= list.numberOfNode) {
		std::cerr << std::format("[ERROR] POSITION OUT OF RANGE! INSERT POSITION MUST IN RANGE 0 TO {}\n", LINEAR_LIST::MAX_SIZE - 1);
		return false;
	}

	//* Shift all item from position + 1 to the right by 1.
	for (int i = list.numberOfNode; i > position; --i) {
		list.nodes[i] = list.nodes[i - 1];
	}
	
	//* Insert new item into the list.
	list.nodes[position] = item;

	//* Increase the size of the list by one.
	++list.numberOfNode;

	return true;
}

bool LINEAR_LIST::InsertLast(LinearList& list, DAU_SACH::DauSach* item) {
	if (LINEAR_LIST::IsFull(list)) {
		std::cerr << std::format("[ERROR] DANH SACH DAU SACH IS FULL!\n");
		return false;
	}

	list.nodes[list.numberOfNode] = item;
	++list.numberOfNode;

	return false;
}

void LINEAR_LIST::Traversal(const LinearList& list) {
	for (int i = 0; i < list.numberOfNode; ++i) {
		list.nodes[i]->Log();
	}
}

bool DAU_SACH_MODULES::DauSachExtractor(std::string data, std::string seperator, DAU_SACH::DauSach* returnData) {
	if (data.length() == 0) {
		return false;
	}

	int indicator = 0;
	size_t pos = 0;

	while ((pos = data.find(seperator)) != std::string::npos) {
		std::string extractedData = data.substr(0, pos);
		if (extractedData.length() == 0) {
			continue;
		}

		switch (indicator++) {
		case (0): {
			returnData->SetISBN(extractedData);
			break;
		}
		case (1): {
			returnData->SetTenSach(extractedData);
			break;
		}
		case (2): {
			returnData->SetSoTrang(std::stoi(extractedData));
			break;
		}
		case (3): {
			returnData->SetTacGia(extractedData);
			break;
		}
		case (4): {
			returnData->SetNamXuatBan(std::stoi(extractedData));
			break;
		}
		case (5): {
			returnData->SetTheLoai(extractedData);
		}
		}
		data.erase(0, pos + seperator.length());
	}

	if (data.length() == 0) {
		returnData->SetDanhMucSach(LINKED_LIST::Controller());
		return true;
	}

	int danhMucSachCount = std::stoi(data);
	if (danhMucSachCount == 0) {
		returnData->SetDanhMucSach(LINKED_LIST::Controller());
	}
	else {
		/**
		* Currently this session is for LOADING @DanhSachMuonTra from file based database.
		* todo: update database and write these code.
		*/
	}

	return true;
}

bool DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(std::string filename, LINEAR_LIST::LinearList& danhSachDauSach) {

	//time_t startPoint = time(0);

	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::in)) {
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		return false;
	}

	std::istream database(&databaseBuffer);
	bool processResult = true;
	int attributeCount = 0;
	while (database) {
		std::string line{};
		std::getline(database, line);
		DAU_SACH::DauSach* newDauSach = new DAU_SACH::DauSach;
		bool result = DAU_SACH_MODULES::DauSachExtractor(line, ", ", newDauSach);
		if (result) {
			++attributeCount;
			//newDauSach->Log();
			LINEAR_LIST::InsertLast(danhSachDauSach, newDauSach);
		}
	}
	databaseBuffer.close();

	//time_t endPoint = time(0);
	//std::cerr << std::format("Record count: {}\n", recordCount);
	//std::cerr << std::format("performance : {}s\n", ((double)(endPoint - startPoint)) / CLOCKS_PER_SEC);

	return processResult;
}

bool DAU_SACH_MODULES::UpdateListToDatabase(const std::string& filename, const LINEAR_LIST::LinearList& dsDauSach) {
	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::out)) {
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		return false;
	}

	std::ostream database(&databaseBuffer);

	for (int i = 0; i < dsDauSach.numberOfNode; ++i) {
		database << dsDauSach.nodes[i]->GetISBN() << ", ";
		database << dsDauSach.nodes[i]->GetTenSach() << ", ";
		database << dsDauSach.nodes[i]->GetSoTrang() << ", ";
		database << dsDauSach.nodes[i]->GetTacGia() << ", ";
		database << dsDauSach.nodes[i]->GetNamXuatBan() << ", ";
		database << dsDauSach.nodes[i]->GetTheLoai() << ", ";

		LINKED_LIST::Controller danhMucSach = dsDauSach.nodes[i]->GetDanhMucSach();
		
		if (LINKED_LIST::IsEmpty(danhMucSach)) {
			database << 0 << "\n";
		}
		else {
			int danhMucSachSize = LINKED_LIST::Size(danhMucSach);
			database << danhMucSachSize << "\n";
			for (LINKED_LIST::Pointer p = danhMucSach.first; p != nullptr; p = p->next) {
				database << p->info.GetMaSach() << ", ";
				database << p->info.GetStringfyTrangThai() << ", ";
				database << p->info.GetViTri() << "\n";
			}
		}
	}

	databaseBuffer.close();
	return true;
}
