
#include "Tabs/LandingView/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#pragma comment(lib, "Graphics/graphics.lib")

//* Program's entrance
int main() {
	AVL_TREE::Pointer readerList;
	AVL_TREE::Initialize(readerList);

	LINEAR_LIST::LinearList titleList;
	LINEAR_LIST::Initialize(titleList);

	LandingView mainView(&readerList, &titleList);
	mainView.Run();

	//* Update databse before closing the program
	try {
		READER_MODULES::UpdateListToDatabase(CONSTANTS::READER_DATABASE, readerList);
		DAU_SACH_MODULES::UpdateListToDatabase(CONSTANTS::TITLES_DATABASE, titleList);
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << "\n";
		return 1;
	}

	return 0;
}


