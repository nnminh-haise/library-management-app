#pragma once

#include <string>
#include "../Helper/Helper.h"

namespace MUON_TRA {
	enum TrangThaiMuonTra {
		SACH_DANG_MUON, SACH_DA_TRA, SACH_BI_MAT
	};

	class MuonTra {
	private:
		std::string MaSach;
		HELPER::Date NgayMuon;
		HELPER::Date NgayTra;
		TrangThaiMuonTra TrangThai;

	public:
		MuonTra();

		MuonTra(std::string MaSach, HELPER::Date NgayMuon, HELPER::Date NgayTra, TrangThaiMuonTra TrangThai);

		void SetMaSach(std::string MaSach);

		std::string GetMaSach();

		void SetNgayMuon(HELPER::Date NgayMuon);

		HELPER::Date GetNgayMuon();

		void SetNgayTra(HELPER::Date NgayTra);

		HELPER::Date GetNgayTra();

		void SetTrangThai(TrangThaiMuonTra TrangThai);

		TrangThaiMuonTra GetTrangThai();
	};

	struct Node {
		MuonTra info;
		Node* left;
		Node* right;

		Node();
	};

	typedef Node* NodePointer;

	struct DoubleLinkedList {
		NodePointer first;
		NodePointer last;

		DoubleLinkedList();
	};

	void Initialize(MUON_TRA::DoubleLinkedList& list);
}

namespace THE_DOC_GIA {
	enum GioiTinh {
		NAM, NU
	};

	enum TrangThaiThe {
		THE_BI_KHOA, THE_HOAT_DONG
	};

	class TheDocGia {
	private:
		std::string MaThe;
		std::string Ho;
		std::string Ten;
		GioiTinh Phai;
		TrangThaiThe TrangThai;
		MUON_TRA::DoubleLinkedList DanhSachMuonTra;

	public:
		TheDocGia();

		TheDocGia(std::string MaThe, std::string Ho, std::string Ten, GioiTinh Phai, TrangThaiThe TrangThai, MUON_TRA::DoubleLinkedList DanhSachMuonTra);

		void SetMaThe(std::string MaThe);

		std::string GetMaThe();

		void SetHo(std::string Ho);

		std::string GetHo();

		void SetTen(std::string Ten);

		std::string GetTen();

		void SetPhai(GioiTinh Phai);

		GioiTinh GetPhai();

		void SetTrangThai(TrangThaiThe TrangThai);

		TrangThaiThe GetTrangThai();

		void SetDanhSachMuonTra(MUON_TRA::DoubleLinkedList DanhSachMuonTra);

		MUON_TRA::DoubleLinkedList GetDanhSachMuonTra();
	};
}