
#include "Tabs/LandingView/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#pragma comment(lib, "Graphics/graphics.lib")

//* Program's entrance
int main() {
	/*AVL_TREE::Pointer readerList;
	AVL_TREE::Initialize(readerList);*/

	AVL_Tree<READER::Reader, int> readerList;

	LINEAR_LIST::LinearList titleList;
	LINEAR_LIST::Initialize(titleList);

	//* Run program main function
	LandingView mainView(&readerList, &titleList);
	mainView.Run();
	
	return 0;
}



