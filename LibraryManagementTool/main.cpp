
#include <iostream>
#include <string>
#include <format>

#include "Views/LandingView.h"
#include "Views/Elements.h"
#include "Helper/Helper.h"
#include "TheDocGia/TheDocGia.h"
#include "Helper/ConstantsAndGlobalVariables.h"

void TestUIElement() {


}

//* Program's entrance
int main() {

	/**
	* Internal storage declaration.
	* @danhSachTheDocgia: AVL Tree
	*/
	AVL_TREE::Pointer danhSachTheDocgia;
	AVL_TREE::Initialize(danhSachTheDocgia);
	
	LoadDanhSachTheDocGiaFromDB(CONSTANTS::THE_DOC_GIA_DB, danhSachTheDocgia);

	AVL_TREE::NonrecursiveInOrderTraversal(danhSachTheDocgia);

	//LANDING_VIEW::Run(danhSachTheDocgia);


	return 0;
}

