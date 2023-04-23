#pragma once

#include <string>

namespace SACH {
	enum TrangThaiSach {
		CHO_MUON_DUOC, DA_CO_DOC_GIA_MUON, DA_THANH_LY
	};

	class Sach {
	private:
		std::string MaSach;
		TrangThaiSach TrangThai;
		std::string ViTri;

	public:
		Sach();

		Sach(std::string MaSach, TrangThaiSach TrangThai, std::string ViTri);

		void SetMaSach(std::string MaSach);

		std::string GetMaSach();

		void SetTrangThai(TrangThaiSach TrangThai);

		TrangThaiSach GetTrangThai();

		std::string GetStringfyTrangThai();

		void SetViTri(std::string ViTri);

		std::string GetViTri();
	};
}

namespace LINKED_LIST {
	struct Node {
		SACH::Sach info;
		Node* next;

		Node();

		Node(SACH::Sach info, Node* next);
	};

	typedef Node* Pointer;

	struct Controller {
		unsigned int total;
		unsigned int borrowed;
		unsigned int sold;
		Pointer first;
	};

	void Initialize(Controller& controller);

	bool IsEmpty(const Controller& controller);

	int Size(const Controller& controller);

	void InsertFirst(Controller& controller, SACH::Sach item);

	void InsertLast(Controller& controller, SACH::Sach item);
}

namespace DAU_SACH {
	class DauSach {
	private:
		std::string ISBN;
		std::string TenSach;
		int SoTrang;
		std::string TacGia;
		int NamXuatBan;
		std::string TheLoai;
		LINKED_LIST::Controller DanhMucSach;

	public:
		DauSach();

		DauSach(std::string ISBN, std::string TenSach, int SoTrang, std::string TacGia, int NamXuatBan, std::string TheLoai, LINKED_LIST::Controller DanhMucSach);

		void SetISBN(std::string ISBN);

		std::string GetISBN();

		void SetTenSach(std::string TenSach);

		std::string GetTenSach();

		void SetSoTrang(int sotrang);

		int GetSoTrang();
		
		void SetTacGia(std::string TacGia);

		std::string GetTacGia();

		void SetNamXuatBan(int NamXuatBan);

		int GetNamXuatBan();

		void SetTheLoai(std::string TheLoai);

		std::string GetTheLoai();

		void SetDanhMucSach(LINKED_LIST::Controller DanhMucSach);

		LINKED_LIST::Controller GetDanhMucSach();

		void Log();
	};
}

namespace LINEAR_LIST {
	const unsigned int MAX_SIZE = 10000;

	struct LinearList {
		unsigned int numberOfNode;
		DAU_SACH::DauSach* nodes[MAX_SIZE];

		LinearList();
	};

	void Initialize(LinearList& list);

	bool IsEmpty(const LinearList& list);

	bool IsFull(const LinearList& list);

	bool InsertFirst(LinearList& list, DAU_SACH::DauSach* item);

	bool InsertItem(LinearList& list, DAU_SACH::DauSach* item, int position);

	bool InsertLast(LinearList& list, DAU_SACH::DauSach* item);

	bool InsertOrder(LinearList& list, DAU_SACH::DauSach* item);

	void Traversal(const LinearList& list);
}

namespace DAU_SACH_MODULES {
	bool LoadDanhSachDauSachFromDB(std::string filename, LINEAR_LIST::LinearList& danhSachDauSach);

	bool UpdateListToDatabase(const std::string& filename, const LINEAR_LIST::LinearList& titleList);
}
