
#include "Tabs/LandingView/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#pragma comment(lib, "Graphics/graphics.lib")

//* Program's entrance
int main()
{
	AVL_Tree<READER::Reader, int> readerList;
	TitleLinearList titleList;

	//* Run program main function
	LandingView mainView(&readerList, &titleList);
	mainView.Run();
	
	return 0;
}



