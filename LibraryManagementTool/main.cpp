
#include <iostream>
#include <string>
#include <format>

#include "Views/LandingView.h"
#include "TheDocGia/TheDocGia.h"
#include "DauSach/DauSach.h"
#include "Views/Elements.h"

#define ff std::format

void ButtonInputModeProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(244, 238, 224));
	btn.SetBorderColor(rgb(57, 54, 70));
	btn.SetTextColor(rgb(57, 54, 70));
}

void ButtonDefaultProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(57, 54, 70));
	btn.SetBorderColor(rgb(244, 238, 224));
	btn.SetTextColor(rgb(244, 238, 224));
}

void ButtonHoverProperties(ELEMENTS::Button& btn) {
	btn.SetFillColor(rgb(109, 93, 110));
	btn.SetBorderColor(rgb(244, 238, 224));
	btn.SetTextColor(rgb(244, 238, 224));
}

void testFunc(){ // main loop
	ELEMENTS::Window win(HELPER::Dimension(1000, 700), "TEST");
	win.Activate();

	ELEMENTS::Fill fill(HELPER::Coordinate(0, 0), 1000, 700);
	fill.fillColor = WHITE;

	HELPER::Coordinate btn1Pos(100, 50);
	HELPER::Coordinate btn2Pos(100, 200);
	HELPER::Coordinate btn3Pos(100, 400);
	HELPER::Dimension btnDimension(300, 70);

	ELEMENTS::Button btn1(btn1Pos, btnDimension);
	ELEMENTS::Button btn2(btn2Pos, btnDimension);
	ELEMENTS::Button btn3(btn3Pos, btnDimension);

	btn1.SetPlaceholder("btn1");
	btn2.SetPlaceholder("btn2");
	btn3.SetPlaceholder("btn3");

	ButtonDefaultProperties(btn1);
	ButtonDefaultProperties(btn2);
	ButtonDefaultProperties(btn3);

	ELEMENTS::Button outputtext(HELPER::Coordinate(100, 500), 300, 70);
	ButtonDefaultProperties(outputtext);
	outputtext.SetPlaceholder("Output text");

	ELEMENTS::InputModeController inpController;

	while (true) {
		while (!kbhit()) {

			setactivepage(1 - getactivepage());

			//* Draw frame
			btn1.Display();
			btn2.Display();
			btn3.Display();
			outputtext.Display();


			///* Frame logic
			if (btn1.IsHover()) {
				ButtonHoverProperties(btn1);
			}
			else if (btn2.IsHover()) {
				ButtonHoverProperties(btn2);
			}
			else if (btn3.IsHover()) {
				ButtonHoverProperties(btn3);
			}
			else if (btn1.LeftMouseClicked()) {
				inpController.Activate(&btn1, &btn1, 20, true, true, true);
			}
			else if (btn2.LeftMouseClicked()) {
				//inpController.Activate(&btn2, &btn2, 20);
				inpController.Activate(&btn2, &btn2, 10, true, false, true);
			}
			else if (btn3.LeftMouseClicked()) {
				inpController.Activate(&btn3, &btn3, 20, false, true, false);
			}
			else {
				ButtonDefaultProperties(btn1);
				ButtonDefaultProperties(btn2);
				ButtonDefaultProperties(btn3);
			}

			setvisualpage(getactivepage());

			clearmouseclick(VK_LBUTTON);
			clearmouseclick(VK_RBUTTON);
		}

		

		if (inpController.InInputMode()) {
			char tmp = std::toupper(getch());
			inpController.ActionOnKey(tmp);
		}
		else {
			char emptychr = getch();//take an empty char then do notthing
		}
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

