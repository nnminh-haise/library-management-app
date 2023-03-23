#pragma once

#include <string>

namespace SACH{
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

		void SetViTri(std::string ViTri);

		std::string GetViTri();
	};

	struct Node {
		Sach info;
		Node* next;

		Node();

		Node(Sach info, Node* next);
	};

	typedef Node* NodePointer;

	void Initialize(NodePointer& First);

	bool IsEmpty(const NodePointer& First);
}

namespace DAU_SACH {
	class DauSach {
	private:
		std::string ISBN;
		std::string TenSach;
		unsigned int SoTrang;
		std::string TacGia;
		unsigned int NamXuatBan;
	    std::string TheLoai;
		SACH::NodePointer DanhMucSach;

	public:
		DauSach();

		DauSach(std::string ISBN, std::string TenSach, unsigned int SoTrang, std::string TacGia, unsigned int NamXuatBan, std::string TheLoai, SACH::NodePointer DanhMucSach);

		void SetISBN(std::string ISBN);

		std::string GetISBN();

		void SetTenSach(std::string TenSach);

		std::string GetTenSach();

		void SetSoTrang(unsigned int Sotrang);

		unsigned int GetSoTrang();
		
		void SetTacGia(std::string TacGia);

		std::string GetTacGia();

		void SetNamXuatBan(unsigned int NamXuatBan);

		unsigned int GetNamXuatBan();

		void SetTheLoai(std::string TheLoai);

		std::string GetTheLoai();

		void SetDanhMucSach(SACH::NodePointer DanhMucSach);

		SACH::NodePointer GetDanhMucSach();
	};

	const unsigned int MAX_SIZE = 10000;

	struct LinearList {
		unsigned int numberOfNode;
		DauSach* nodes[MAX_SIZE];

		LinearList();
	};
}
