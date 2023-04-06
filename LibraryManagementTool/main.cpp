
#include <iostream>
#include <string>
#include <format>

#include "Views/LandingView.h"
#include "Views/Elements.h"
#include "Helper/Helper.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#include "Helper/ConstantsAndGlobalVariables.h"
#include "Graphics/graphics.h"


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
	LANDING_VIEW::Run(danhSachTheDocgia, danhSachDauSach);

	

	return 0;
}

