
#include <iostream>
#include <string>
#include <format>

#include "Views/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#include "Views/Elements.h"

#define ff std::format

bool validation(const char& chr) {
	return ('A' <= chr && chr <= 'Z' || chr == ' ');
}

void testFunc(){ // main loop
	ELEMENTS::Window win(HELPER::Dimension(1000, 700), "TEST");
	win.Activate();

	ELEMENTS::Fill fill(HELPER::Coordinate(0, 0), 1000, 700);
	fill.fillColor = WHITE;

	ELEMENTS::InputBox bx(HELPER::Coordinate(100, 50), 300, 100);
	bx.SetFillColor(WHITE);
	bx.SetBorderColor(BLACK);
	bx.SetTextColor(BLACK);

	char escKey{};
	while (escKey != ELEMENTS::SpecialKey::ESCAPE) {
		int frCnt = 0;
		while (!kbhit()) {

			setactivepage(1 - getactivepage());

			fill.Draw();
			if (bx.IsPointed() && bx.LeftMouseClicked() == false) {
				bx.SetFillColor(rgb(191, 234, 245));
			}
			else if (bx.LeftMouseClicked()) {
				bx.ActivateInputMode();
				bx.SetTextColor(BLACK);
				bx.SetFillColor(rgb(246, 241, 241));
			}
			else {
				bx.SetFillColor(WHITE);
				bx.SetTextColor(BLACK);
			}

			std::string res = bx.InputMode(30, validation);
			if (bx.InInputMode()) {
				bx.SetPlaceholder(res);
				bx.DeactivateInputMode();
			}

			outtextxy(100, 600, (char*)bx.GetPlaceholder().c_str());

			setvisualpage(getactivepage());

			clearmouseclick(VK_LBUTTON);
			clearmouseclick(VK_RBUTTON);
		}

		escKey = getch();
	}

	win.Deactivate();
}

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
	//LandingView mainView(danhSachTheDocgia, danhSachDauSach);
	//mainView.Run();
	
	testFunc();
	//testFunc2();

	return 0;
}

