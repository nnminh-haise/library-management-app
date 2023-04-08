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

void LINKED_LIST::Initialize(LINKED_LIST::Controler& controller) {
	controller.first = nullptr;
}

bool LINKED_LIST::IsEmpty(const LINKED_LIST::Controler& controller) {
	return controller.first == nullptr;
}

void LINKED_LIST::InsertItemLast(LINKED_LIST::Controler& controller, SACH::Sach item) {
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

DAU_SACH::DauSach::DauSach(std::string ISBN, std::string TenSach, unsigned int SoTrang, std::string TacGia, unsigned int NamXuatBan, std::string TheLoai, LINKED_LIST::Controler DanhMucSach) {
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

void DAU_SACH::DauSach::SetDanhMucSach(LINKED_LIST::Controler DanhMucSach) {
	this->DanhMucSach = DanhMucSach;
}

LINKED_LIST::Controler DAU_SACH::DauSach::GetDanhMucSach() {
	return this->DanhMucSach;
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

void DAU_SACH::swap(DauSach*& ClassPtr1, DauSach*& ClassPtr2)
{
	DauSach* temp = ClassPtr1;
	ClassPtr1 = ClassPtr2;
	ClassPtr2 = temp;
}

void DAU_SACH::sortByCategory(LinearList& list)
{
	int j, k, min_index;
	for (j = 0; j < list.numberOfNode - 1; j++)
	{
		min_index = j;
		for (k = j + 1; k < list.numberOfNode; k++)
		{
			if (list.nodes[min_index]->GetTheLoai().compare(list.nodes[k]->GetTheLoai()) > 0)
				min_index = k;
			else if (list.nodes[min_index]->GetTheLoai().compare(list.nodes[k]->GetTheLoai()) == 0)
				if (list.nodes[min_index]->GetTenSach().compare(list.nodes[k]->GetTenSach()) > 0)
					swap(list.nodes[min_index], list.nodes[k]);
		}
		if (min_index != j)
			swap(list.nodes[min_index], list.nodes[j]);
	}
}

