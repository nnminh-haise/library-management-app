#include "DauSach.h"
#include "../Helper/Helper.h"

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

void LINKED_LIST::InsertFirst(Controller& controller, SACH::Sach item) {
	LINKED_LIST::Pointer newNode = new LINKED_LIST::Node(item, nullptr);
	controller.first = newNode;

	controller.total++;
	if (item.GetTrangThai() == SACH::DA_CO_DOC_GIA_MUON) {
		controller.borrowed++;
	}
	else if (item.GetTrangThai() == SACH::DA_THANH_LY) {
		controller.sold++;
	}
}

void LINKED_LIST::InsertLast(LINKED_LIST::Controller& controller, SACH::Sach item) {
	if (LINKED_LIST::IsEmpty(controller)) {
		LINKED_LIST::InsertFirst(controller, item);
		return;
	}

	LINKED_LIST::Pointer newNode = new Node(item, nullptr);

	++controller.total;
	if (item.GetTrangThai() == SACH::TrangThaiSach::DA_CO_DOC_GIA_MUON) {
		++controller.borrowed;
	}
	else if (item.GetTrangThai() == SACH::TrangThaiSach::DA_THANH_LY) {
		++controller.sold;
	}

	LINKED_LIST::Pointer Last = controller.first;
	for (; Last->next != nullptr; Last = Last->next);
	Last->next = newNode;
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

bool LINEAR_LIST::InsertFirst(LinearList& list, DAU_SACH::DauSach* item) {
	if (LINEAR_LIST::IsFull(list)) {
		return false;
	}

	list.nodes[0] = item;
	list.numberOfNode = 1;
	return true;
}

bool LINEAR_LIST::InsertItem(LINEAR_LIST::LinearList& list, DAU_SACH::DauSach* item, int position) {
	if (LINEAR_LIST::IsFull(list)) {
		std::cerr << std::format("[ERROR] LIST IS FULL CANNOT INSERT NEW ELEMENT!\nSUGGEST CREATE A NEW LIST WITH BIGGER SIZE!\n");
		exit(1);
	}

	if (position < 0 || position >= list.numberOfNode) {
		std::cerr << std::format("[ERROR] POSITION OUT OF RANGE! INSERT POSITION MUST IN RANGE 0 TO {}\n", LINEAR_LIST::MAX_SIZE - 1);
		exit(1);
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
		exit(1);
	}

	list.nodes[list.numberOfNode] = item;
	++list.numberOfNode;

	return false;
}

bool LINEAR_LIST::InsertOrder(LinearList& list, DAU_SACH::DauSach* item) {
	if (LINEAR_LIST::IsFull(list)) {
		exit(1);
	}

	int index = 0;
	for (; index < list.numberOfNode && item->GetTenSach().compare(list.nodes[index]->GetTenSach()) >= 0; ++index);

	for (int i = list.numberOfNode; i > index; --i) {
		list.nodes[i] = list.nodes[i - 1];
	}

	list.numberOfNode++;
	list.nodes[index] = item;

	return true;
}

void LINEAR_LIST::Traversal(const LinearList& list) {
	for (int i = 0; i < list.numberOfNode; ++i) {
		list.nodes[i]->Log();
	}
}

bool DAU_SACH_MODULES::LoadDanhSachDauSachFromDB(std::string filename, LINEAR_LIST::LinearList& danhSachDauSach) {
	LINEAR_LIST::Initialize(danhSachDauSach);
	
	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::in)) {
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		exit(0);
	}

	std::istream database(&databaseBuffer);
	while (database) {
		std::string titleData{};
		std::getline(database, titleData);

		if (titleData.length() == 0) {
			continue;
		}

		std::string* data = nullptr;
		int dataCount = 0;
		STR::Extract(titleData, ", ", data, dataCount);

		DAU_SACH::DauSach* newTitle = new DAU_SACH::DauSach;

		for (int i = 0; i < dataCount; ++i) {
			switch (i) {
				case (0): {
					newTitle->SetISBN(data[i]);
					break;
				}
				case (1): {
					newTitle->SetTenSach(data[i]);
					break;
				}
				case (2): {
					newTitle->SetSoTrang(std::stoi(data[i]));
					break;
				}
				case (3): {
					newTitle->SetTacGia(data[i]);
					break;
				}
				case (4): {
					newTitle->SetNamXuatBan(std::stoi(data[i]));
					break;
				}
				case (5): {
					newTitle->SetTheLoai(data[i]);
					break;
				}
				case (6): {
					int bookListSize = std::stoi(data[i]);
					if (bookListSize == 0) {
						newTitle->SetDanhMucSach(LINKED_LIST::Controller());
					}
					else {
						LINKED_LIST::Controller newBookList;
						LINKED_LIST::Initialize(newBookList);

						while (database && bookListSize--) {
							SACH::Sach newBook{};

							std::string bookData{};
							std::getline(database, bookData);

							if (bookData.length() == 0) {
								std::cerr << std::format("[ERROR] Empty book list data in database!\n");
								exit(1);
							}

							std::string* bookItems = nullptr;
							int itemCount = 0;
							STR::Extract(bookData, ", ", bookItems, itemCount);

							newBook.SetMaSach(bookItems[0]);
							if (bookItems[1] == "CHO MUON DUOC") {
								newBook.SetTrangThai(SACH::CHO_MUON_DUOC);
							}
							else if (bookItems[1] == "DA CO DOC GIA MUON") {
								newBook.SetTrangThai(SACH::DA_CO_DOC_GIA_MUON);
							}
							else {
								newBook.SetTrangThai(SACH::DA_THANH_LY);
							}
							newBook.SetViTri(bookItems[2]);

							LINKED_LIST::InsertLast(newBookList, newBook);
						}

						newTitle->SetDanhMucSach(newBookList);
					}
					break;
				}
			}
		}

		if (LINEAR_LIST::IsEmpty(danhSachDauSach)) {
			LINEAR_LIST::InsertFirst(danhSachDauSach, newTitle);
		}
		else {
			LINEAR_LIST::InsertOrder(danhSachDauSach, newTitle);
		}
	}

	databaseBuffer.close();

	return true;
}

bool DAU_SACH_MODULES::UpdateListToDatabase(const std::string& filename, const LINEAR_LIST::LinearList& titleList) {
	std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::out)) {
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		return false;
	}

	std::ostream database(&databaseBuffer);

	for (int i = 0; i < titleList.numberOfNode; ++i) {
		database << titleList.nodes[i]->GetISBN() << ", ";
		database << titleList.nodes[i]->GetTenSach() << ", ";
		database << titleList.nodes[i]->GetSoTrang() << ", ";
		database << titleList.nodes[i]->GetTacGia() << ", ";
		database << titleList.nodes[i]->GetNamXuatBan() << ", ";
		database << titleList.nodes[i]->GetTheLoai() << ", ";

		LINKED_LIST::Controller danhMucSach = titleList.nodes[i]->GetDanhMucSach();
		
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
