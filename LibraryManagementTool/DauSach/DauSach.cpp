#include "DauSach.h"

#include <string>

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

void SACH::Initialize(SACH::NodePointer& First) {
	First = nullptr;
}

bool SACH::IsEmpty(const SACH::NodePointer& First) {
	return First == nullptr;
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

