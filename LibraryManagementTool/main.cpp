
#include <iostream>
#include <string>
#include <format>

#include "Views/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#include "Views/Elements.h"

bool validation(const char& chr) {
	return ('A' <= chr && chr <= 'Z');
}

void testFunc(){
	ELEMENTS::Window win(HELPER::Dimension(1000, 700), "TEST");
	win.Activate();

	ELEMENTS::Fill fill(HELPER::Coordinate(0, 0), 1000, 700);
	fill.fillColor = WHITE;
	

	ELEMENTS::InputBox bx(HELPER::Coordinate(100, 50), 300, 50);
	bx.SetFillColor(WHITE);
	bx.SetBorderColor(BLACK);
	bx.SetTextColor(BLACK);


	char escKey{};
	while (escKey != ELEMENTS::SpecialKey::ESCAPE) {
		while (!kbhit()) {
			setactivepage(1 - getactivepage());

			fill.Draw();
			if (bx.IsPointed() && bx.LeftMouseClicked() == false) {
				bx.SetFillColor(rgb(191, 234, 245));
			}
			else if (bx.LeftMouseClicked()) {
				bx.ActivateInputMode();
			}
			else {
				bx.SetFillColor(WHITE);
			}

			std::string res = bx.InputMode(10, validation);
			if (bx.InInputMode() == true) {
				bx.DeactivateInputMode();
			}

			outtextxy(800, 50, (char*)res.c_str());

			setvisualpage(getactivepage());
			//* Draw elements end above

			//* Clear mouseclick
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
	LandingView mainView(danhSachTheDocgia, danhSachDauSach);
	mainView.Run();
	
	//testFunc();

	return 0;
}

