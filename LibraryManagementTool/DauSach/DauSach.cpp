#include "DauSach.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>

SACH::Sach::Sach() {
	this->MaSach = std::string();
	this->TrangThai = SACH::TrangThaiSach::DA_THANH_LY;
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

void SACH::Sach::SetViTri(std::string ViTri) {
	this->ViTri = ViTri;
}

std::string SACH::Sach::GetViTri() {
	return this->ViTri;
}

SACH::Node::Node() : info(SACH::Sach()), next(nullptr) {
}

SACH::Node::Node(SACH::Sach info, SACH::Node* next) : info(info), next(next) {
}

//SACH::Sach* SACH::SplitDataFromString(const std::string& data, const std::string& seperator) {
//	std::string dataSet[3]{};
//	int indicator = 0;
//	std::size_t start = 0, end = 0;
//	while ((end = data.find(seperator, start)) != std::string::npos) {
//		dataSet[indicator++] = data.substr(start, end - start);
//		start = end + seperator.length();
//	}
//	dataSet[indicator] = data.substr(start);
//
//	SACH::Sach* newSach = new SACH::Sach(dataSet[0], dataSet[1], dataSet[2]);
//	return newSach;
//}

void SACH::Initialize(SACH::NodePointer& First) {
	First = nullptr;
}

bool SACH::IsEmpty(const SACH::NodePointer& First) {
	return First == nullptr;
}

void SACH::InsertItemLast(NodePointer& First, Sach item) {
	SACH::NodePointer newNode = new Node(item, nullptr);

	if (SACH::IsEmpty(First)) {
		First = newNode;
	}
	else {
		SACH::NodePointer Last = First;
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
	this->DanhMucSach = nullptr;
}

DAU_SACH::DauSach::DauSach(std::string ISBN, std::string TenSach, unsigned int SoTrang, std::string TacGia, unsigned int NamXuatBan, std::string TheLoai, SACH::NodePointer DanhMucSach) {
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

void DAU_SACH::DauSach::SetSoTrang(unsigned int Sotrang) {
	this->SoTrang = SoTrang;
}

unsigned int DAU_SACH::DauSach::GetSoTrang() {
	return this->SoTrang;
}

void DAU_SACH::DauSach::SetTacGia(std::string TacGia) {
	this->TacGia = TacGia;
}

std::string DAU_SACH::DauSach::GetTacGia() {
	return this->TacGia;
}

void DAU_SACH::DauSach::SetNamXuatBan(unsigned int NamXuatBan) {
	this->NamXuatBan = NamXuatBan;
}

unsigned int DAU_SACH::DauSach::GetNamXuatBan() {
	return this->NamXuatBan;
}

void DAU_SACH::DauSach::SetTheLoai(std::string TheLoai) {
	this->TheLoai = TheLoai;
}

std::string DAU_SACH::DauSach::GetTheLoai() {
	return this->TheLoai;
}

void DAU_SACH::DauSach::SetDanhMucSach(SACH::NodePointer DanhMucSach) {
	this->DanhMucSach = DanhMucSach;
}

SACH::NodePointer DAU_SACH::DauSach::GetDanhMucSach() {
	return this->DanhMucSach;
}

DAU_SACH::LinearList::LinearList() {
	this->numberOfNode = 0;
	for (int i = 0; i < DAU_SACH::MAX_SIZE; ++i) {
		this->nodes[i] = nullptr;
	}
}

//DAU_SACH::DauSach* DAU_SACH::SplitDataFromString(const std::string& data, const std::string& seperator) {
//	std::string dataSet[7]{};
//	int indicator = 0;
//	std::size_t start = 0, end = 0;
//	while ((end = data.find(seperator, start)) != std::string::npos) {
//		dataSet[indicator++] = data.substr(start, end - start);
//		start = end + seperator.length();
//	}
//	dataSet[indicator] = data.substr(start);
//
//	SACH::NodePointer newDanhMucSach_First;
//	SACH::Initialize(newDanhMucSach_First);
//	for (int i = 0; i < std::stoi(dataSet[6]); ++i) {
//		//std::getline()
//		//SACH::Sach newSach = SACH::SplitDataFromString()
//		//SACH::InsertItemLast(newDanhMucSach_First, );
//	}
//	
//
//	return nullptr;
//}

void DAU_SACH::Initialize(DAU_SACH::LinearList& list) {
	list.numberOfNode = 0;
	for (int i = 0; i < DAU_SACH::MAX_SIZE; ++i) {
		list.nodes[i] = nullptr;
	}
}

bool DAU_SACH::IsEmpty(const LinearList& list) {
	return list.numberOfNode == 0;
}

bool DAU_SACH::IsFull(const LinearList& list) {
	return list.numberOfNode == MAX_SIZE;
}

//bool DAU_SACH::InsertItem(LinearList& list, DauSach* item, int position) {
//	if (DAU_SACH::IsFull(list)) {
//		std::cerr << std::format("[ERROR] LIST IS FULL CANNOT INSERT NEW ELEMENT!\nSUGGEST CREATE A NEW LIST WITH BIGGER SIZE!\n");
//		return false;
//	}
//
//	if (position < 0 || position >= list.numberOfNode) {
//		std::cerr << std::format("[ERROR] POSITION OUT OF RANGE! INSERT POSITION MUST IN RANGE 0 TO {}\n", DAU_SACH::MAX_SIZE - 1);
//		return false;
//	}
//	//* Shift all item from position + 1 to the right by 1.
//	for (int i = list.numberOfNode; i > position; --i) {
//		list.nodes[i] = list.nodes[i - 1];
//	}
//	
//	//* Insert new item into the list.
//	list.nodes[position] = item;
//
//	//* Increase the size of the list by one.
//	++list.numberOfNode;
//
//	return true;
//}

