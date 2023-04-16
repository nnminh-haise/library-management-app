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
}

namespace DOUBLE_LINKED_LIST {
	struct Node {
		MUON_TRA::MuonTra info;
		Node* left;
		Node* right;

		Node();
	};

	typedef Node* Pointer;

	struct Controler {
		Pointer First;
		Pointer Last;

		Controler();
	};

	void Initialize(DOUBLE_LINKED_LIST::Controler& list);

	bool IsEmpty(const Controler& list);

	int Size(const Controler& list);

	void ClearList(Controler& list);
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
		int MaThe;
		std::string Ho;
		std::string Ten;
		GioiTinh Phai;
		TrangThaiThe TrangThai;
		DOUBLE_LINKED_LIST::Controler DanhSachMuonTra;

	public:
		TheDocGia();

		TheDocGia(int MaThe, std::string Ho, std::string Ten, GioiTinh Phai, TrangThaiThe TrangThai, DOUBLE_LINKED_LIST::Controler DanhSachMuonTra);

		void SetMaThe(int MaThe);

		int GetMaThe();

		void SetHo(std::string Ho);

		std::string GetHo();

		void SetTen(std::string Ten);

		std::string GetTen();

		void SetPhai(GioiTinh Phai);

		GioiTinh GetPhai();

		std::string GetFullName();

		std::string GetStringfyPhai();

		void SetTrangThai(TrangThaiThe TrangThai);

		TrangThaiThe GetTrangThai();

		std::string GetStringfyTrangThai();

		void SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controler DanhSachMuonTra);

		DOUBLE_LINKED_LIST::Controler GetDanhSachMuonTra();

		void Log();
	};
}

namespace MUON_TRA_MODULES {
	int CountBorrowedBooks(const DOUBLE_LINKED_LIST::Controler& list);
}

namespace AVL_TREE {
	struct Node {
		THE_DOC_GIA::TheDocGia info;
		int balanceFactor;
		int height;
		Node* left;
		Node* right;

		Node();

		int GetKey();

		void SetKey(const int key);
	};

	typedef Node* Pointer;

	void Initialize(Pointer& root);

	bool IsEmpty(const Pointer& root);

	void PreOrderTraversal(const Pointer& root);

	void InOrderTraversal(const Pointer& root);

	void PostOrderTraversal(const Pointer& root);

	void CountNode(const Pointer& root, int& counter);

	void NonrecursiveInOrderTraversal(const Pointer& root);

	Pointer RotateLeft(Pointer root);

	Pointer RotateRight(Pointer root);

	bool Insert(Pointer& root, THE_DOC_GIA::TheDocGia info);

	Pointer SearchByKey(const Pointer& root, const int& key);

	Pointer GetMinValueNode(Pointer const& node);

	Pointer RemoveNode(Pointer& node, const int& key);
}

namespace THE_DOC_GIA_MODULES {
	bool TheDocGiaExtractor(std::string data, std::string seperator, THE_DOC_GIA::TheDocGia& returnData);

	bool LoadDanhSachTheDocGiaFromDB(std::string filename, AVL_TREE::Pointer& tree);

	bool UpdateListToDatabase(const std::string& filename, AVL_TREE::Pointer& tree);

	int GetIndex(const std::string& filename, AVL_TREE::Pointer& tree);

	void SortByName(AVL_TREE::Pointer const& node, AVL_TREE::Pointer*& pointerArr, int& arrSize);
}
