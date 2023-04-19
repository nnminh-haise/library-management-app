
#include "Tabs/LandingView/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#pragma comment(lib, "Graphics/graphics.lib")

//* Program's entrance
int main() {

	/**
	* Internal storage declaration.
	* @danhSachTheDocgia: AVL Tree
	*/
	AVL_TREE::Pointer danhSachTheDocgia;
	AVL_TREE::Initialize(danhSachTheDocgia);

	LINEAR_LIST::LinearList danhSachDauSach;
	LINEAR_LIST::Initialize(danhSachDauSach);

	//* Run program main function
	LandingView mainView(danhSachTheDocgia, danhSachDauSach);
	mainView.Run(danhSachTheDocgia, danhSachDauSach);

	//test();

	

	return 0;
}

