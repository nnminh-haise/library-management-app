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

	struct Controller {
		Pointer First;
		Pointer Last;

		Controller();
	};

	void Initialize(DOUBLE_LINKED_LIST::Controller& list);

	bool IsEmpty(const Controller& list);
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
		DOUBLE_LINKED_LIST::Controller DanhSachMuonTra;

	public:
		TheDocGia();

		TheDocGia(int MaThe, std::string Ho, std::string Ten, GioiTinh Phai, TrangThaiThe TrangThai, DOUBLE_LINKED_LIST::Controller DanhSachMuonTra);

		void SetMaThe(int MaThe);

		int GetMaThe();

		void SetHo(std::string Ho);

		std::string GetHo();

		void SetTen(std::string Ten);

		std::string GetTen();

		void SetPhai(GioiTinh Phai);

		GioiTinh GetPhai();

		void SetTrangThai(TrangThaiThe TrangThai);

		TrangThaiThe GetTrangThai();

		void SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controller DanhSachMuonTra);

		DOUBLE_LINKED_LIST::Controller GetDanhSachMuonTra();

		void Log();
	};
}

/*
* AVL TREE NAMESPACE.
* 
* Each node of the AVL tree is a @TheDocGia object. 
* The key of each node is the @TheDocGia.MaThe itself.
* The maximum size of the tree is 1000 nodes.
* 
* Due to the effect of the AVL Tree, @danhSachTheDocGia will be sorted to increasement order buy @maThe.
*/

namespace AVL_TREE {
	const int MAX_SIZE = 1000;

	struct Node {
		THE_DOC_GIA::TheDocGia info;
		int balanceFactor;
		Node* left;
		Node* right;

		Node();

		int GetKey();
	};

	typedef Node* Pointer;

	void Initialize(Pointer& root);

	bool IsEmpty(const Pointer& root);

	void PreOrderTraversal(const Pointer& root);

	void InOrderTraversal(const Pointer& root);

	void PostOrderTraversal(const Pointer& root);

	void NonrecursiveInOrderTraversal(const Pointer& root);

	Pointer RotateLeft(Pointer root);

	Pointer RotateRight(Pointer root);

	bool Insert(Pointer& root, THE_DOC_GIA::TheDocGia info);
}

bool TheDocGiaExtractor(std::string data, std::string seperator, THE_DOC_GIA::TheDocGia& returnData);

bool LoadDanhSachTheDocGiaFromDB(std::string filename, AVL_TREE::Pointer& tree);