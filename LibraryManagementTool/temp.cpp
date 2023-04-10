/*

//* Sample Interface (can be copy)
class nameInputController : public ELEMENTS::InputModeController {
public:

	//* Modify this function to validate the input key
	bool KeyValidation(const char& chr) override {
		return (chr == ' ' || 'A' <= chr && chr <= 'Z');
	}

	//* modify this function to decide action on each key press
	void ActionOnKey(const char& chr) override {

		//* press ENTER key or ESCAPE key to stop the input process
		if (chr == ELEMENTS::SpecialKey::ENTER || chr == ELEMENTS::SpecialKey::ESCAPE) {
			if (this->outputTextBox != nullptr) {
				this->outputTextBox->SetPlaceholder(this->inputString);
			}
			this->Deactivate();
		}

		//* Do not accept the first key is a SPACE
		else if (this->inputString.length() == 0 && chr == ' ') {
			return;
		}

		//* Do not accept multiple SPACE
		else if (this->inputString.length() != 0 && this->inputString[this->inputString.length() - 1] == ' ' && chr == ' ') {
			return;
		}

		//* Do not accept the BACKSPACE key if the string is empty
		else if (this->inputString.length() == 0 && chr == ELEMENTS::SpecialKey::BACKSPACE) {
			return;
		}

		//* Remove the latest key before pressing BACKSPACE key
		else if (chr == ELEMENTS::SpecialKey::BACKSPACE) {
			this->inputString.pop_back();
			this->characterCount--;
			this->currentTextBox->SetPlaceholder(this->inputString);
		}

		//* Validate the key using the previous validation function and accept the key
		else if (this->characterCount + 1 < this->characterLimit && this->KeyValidation(chr)) {
			this->inputString.push_back(chr);
			++this->characterCount;
			this->currentTextBox->SetPlaceholder(this->inputString);
		}
	}
};


void testFunc() { // main loop

	//* Graphic window and element initialization start below
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
	//--- Graphic window and element initialization end above

	//* Create a input mode controller for the view (this can be setup at the view's global loop)
	nameInputController inpController;

	//* View Main loop
	while (true) {

		//* Loop for drawing frame
		while (!kbhit()) {

			//* Draw view's elements below this code
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
				inpController.Activate(&btn1, &outputtext, 20);
			}
			else if (btn2.LeftMouseClicked()) {
				inpController.Activate(&btn2, &outputtext, 20);
			}
			else if (btn3.LeftMouseClicked()) {
				inpController.Activate(&btn3, &outputtext, 20);
			}
			else {
				ButtonDefaultProperties(btn1);
				ButtonDefaultProperties(btn2);
				ButtonDefaultProperties(btn3);
			}


			//* Frame drawing end above
			setvisualpage(getactivepage());

			clearmouseclick(VK_LBUTTON);
			clearmouseclick(VK_RBUTTON);
		}

		//* Input processing start in this if statement
		if (inpController.InInputMode()) {
			char tmp = std::toupper(getch());
			inpController.ActionOnKey(tmp);
		}

		//* This currently filter out the case where input mode is not on but user still press some key.
		else {
			char emptychr = getch();//take an empty char then do notthing
		}
	}

	win.Deactivate();
}


*/