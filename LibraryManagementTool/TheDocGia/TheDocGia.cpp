#include "TheDocGia.h"
#include "../Helper/Helper.h"

#include <string>

MUON_TRA::MuonTra::MuonTra() {
	this->MaSach = std::string();
	this->NgayMuon = HELPER::Date();
	this->NgayTra = HELPER::Date();
	this->TrangThai = MUON_TRA::TrangThaiMuonTra::SACH_BI_MAT;
}

MUON_TRA::MuonTra::MuonTra(std::string MaSach, HELPER::Date NgayMuon, HELPER::Date NgayTra, MUON_TRA::TrangThaiMuonTra TrangThai) {
	this->MaSach = MaSach;
	this->NgayMuon = NgayMuon;
	this->NgayTra = NgayTra;
	this->TrangThai = TrangThai;
}

void MUON_TRA::MuonTra::SetMaSach(std::string MaSach) {
	this->MaSach = MaSach;
}

std::string MUON_TRA::MuonTra::GetMaSach() {
	return this->MaSach;
}

void MUON_TRA::MuonTra::SetNgayMuon(HELPER::Date NgayMuon) {
	this->NgayMuon = NgayMuon;
}

HELPER::Date MUON_TRA::MuonTra::GetNgayMuon() {
	return this->NgayMuon;
}

void MUON_TRA::MuonTra::SetNgayTra(HELPER::Date NgayTra) {
	this->NgayTra = NgayTra;
}

HELPER::Date MUON_TRA::MuonTra::GetNgayTra() {
	return this->NgayTra;
}

void MUON_TRA::MuonTra::SetTrangThai(MUON_TRA::TrangThaiMuonTra TrangThai) {
	this->TrangThai = TrangThai;
}

MUON_TRA::TrangThaiMuonTra MUON_TRA::MuonTra::GetTrangThai() {
	return this->TrangThai;
}

MUON_TRA::Node::Node() {
	this->info = MUON_TRA::MuonTra();
	this->left = this->right = nullptr;
}

MUON_TRA::DoubleLinkedList::DoubleLinkedList() {
	this->first = this->last = nullptr;
}

void MUON_TRA::Initialize(DoubleLinkedList& list) {
	list.first = list.last = nullptr;
}

THE_DOC_GIA::TheDocGia::TheDocGia() {
	this->MaThe = std::string();
	this->Ho = std::string();
	this->Ten = std::string();
	this->Phai = THE_DOC_GIA::GioiTinh::NAM;
	this->TrangThai = THE_DOC_GIA::TrangThaiThe::THE_BI_KHOA;
	this->DanhSachMuonTra = MUON_TRA::DoubleLinkedList();
}

THE_DOC_GIA::TheDocGia::TheDocGia(std::string MaThe, std::string Ho, std::string Ten, THE_DOC_GIA::GioiTinh Phai, THE_DOC_GIA::TrangThaiThe TrangThai, MUON_TRA::DoubleLinkedList DanhSachMuonTra) {
	this->MaThe = MaThe;
	this->Ho = Ho;
	this->Ten = Ten;
	this->Phai = Phai;
	this->TrangThai = TrangThai;
	this->DanhSachMuonTra = DanhSachMuonTra;
}

void THE_DOC_GIA::TheDocGia::SetMaThe(std::string MaThe) {
	this->MaThe = MaThe;
}

std::string THE_DOC_GIA::TheDocGia::GetMaThe() {
	return this->MaThe;
}

void THE_DOC_GIA::TheDocGia::SetHo(std::string Ho) {
	this->Ho = Ho;
}

std::string THE_DOC_GIA::TheDocGia::GetHo() {
	return this->Ho;
}

void THE_DOC_GIA::TheDocGia::SetTen(std::string Ten) {
	this->Ten = Ten;
}

std::string THE_DOC_GIA::TheDocGia::GetTen() {
	return this->Ten;
}

void THE_DOC_GIA::TheDocGia::SetPhai(THE_DOC_GIA::GioiTinh Phai) {
	this->Phai = Phai;
}

THE_DOC_GIA::GioiTinh THE_DOC_GIA::TheDocGia::GetPhai() {
	return this->Phai;
}

void THE_DOC_GIA::TheDocGia::SetTrangThai(THE_DOC_GIA::TrangThaiThe TrangThai) {
	this->TrangThai = TrangThai;
}

THE_DOC_GIA::TrangThaiThe THE_DOC_GIA::TheDocGia::GetTrangThai() {
	return this->TrangThai;
}

void THE_DOC_GIA::TheDocGia::SetDanhSachMuonTra(MUON_TRA::DoubleLinkedList DanhSachMuonTra) {
	this->DanhSachMuonTra = DanhSachMuonTra;
}

MUON_TRA::DoubleLinkedList THE_DOC_GIA::TheDocGia::GetDanhSachMuonTra() {
	return this->DanhSachMuonTra;
}

THE_DOC_GIA::Node::Node() {
	this->info = THE_DOC_GIA::TheDocGia();
	this->balanceFactor = 0;
	this->left = this->right = nullptr;
}
