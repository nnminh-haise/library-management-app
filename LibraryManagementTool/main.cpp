
#include <iostream>
#include <string>
#include <format>

#include "Views/LandingView.h"
#include "Views/Elements.h"
#include "Helper/Helper.h"
#include "TheDocGia/TheDocGia.h"
#include "Helper/ConstantsAndGlobalVariables.h"
#include "Graphics/graphics.h"



void TestUIElement() {
	
}

//* Program's entrance
int main() {

//#define CUSTOM_DEBUG_MODE 1


#ifdef CUSTOM_DEBUG_MODE

	TestUIElement();

#else

	/**
	* Internal storage declaration.
	* @danhSachTheDocgia: AVL Tree
	*/
	AVL_TREE::Pointer danhSachTheDocgia;
	AVL_TREE::Initialize(danhSachTheDocgia);

	//* Run program main function
	LANDING_VIEW::Run(danhSachTheDocgia);

#endif

	

	return 0;
}

