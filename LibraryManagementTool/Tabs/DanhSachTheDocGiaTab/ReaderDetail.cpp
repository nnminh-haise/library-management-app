#include "ReaderDetail.hpp"

ReaderDetails::ReaderDetails()
{
	this->Initialize();
}

void ReaderDetails::Activate()
{
	this->status_ = true;
}

void ReaderDetails::Deactivate()
{
	this->status_ = false;

	this->Reset();
}

bool ReaderDetails::InActive()
{
	return status_ == true;
}

int ReaderDetails::Run()
{
	if (!this->status_) { return 0; }

	this->Display();

	if (this->mode_ == 1)
	{
		this->FieldsOnAction();
		this->GenderButtonOnAction();
	}

	return 0;
}

void ReaderDetails::Reset()
{
	this->mode_ = 0;
	this->status_ = false;
	this->reader_ = nullptr;
}

void ReaderDetails::SetReader(AVL_TREE::Pointer reader)
{
	this->reader_ = reader;

	this->UpdateInfo();
}

void ReaderDetails::SetPackage(Package* package)
{
	this->package_ = package;
}

void ReaderDetails::SetMode(int mode)
{
	this->mode_ = mode;
}

LinkedButton& ReaderDetails::AccessFields(int index)
{
	if (index < 0 || index >= 5)
	{
		throw std::out_of_range("[ERROR] Index out of range! (ReaderDetails::AccessFields)\n");
	}

	return this->details_[index];
}

void ReaderDetails::Initialize()
{
	this->InitializeElements();
}

void ReaderDetails::InitializeElements()
{
	this->background_ = HELPER::Fill({ 1022, 204 }, 650, 200);
	this->background_.fillColor = rgb(238, 238, 238);
	this->background_.borderColor = rgb(238, 238, 238);
	this->background_.Draw();

	this->title_ = Button({1022, 204}, {650, 40});
	this->title_.SetPlaceholder("Reader's Infomations");
	this->title_.SetTextColor(rgb(241, 246, 249));
	this->title_.SetFillColor(rgb(33, 42, 62));
	this->title_.SetBorderColor(rgb(33, 42, 62));

	HELPER::Coordinate descriptionTopLefts[] = {
		{1032, 254}, {1462, 254}, {1032, 329}, {1142, 329}, {1252, 329}
	};
	HELPER::Coordinate contentTopLefts[] = {
		{1032, 274}, {1462, 274}, {1032, 349}, {1142, 349}, {1252, 349}
	};
	HELPER::Dimension contentDimensions[] = {
		{420, 45}, {200, 45}, {100, 45}, {100, 45}, {100, 45}
	};
	std::string descriptionPlaceholders[] = {"First name:", "Last name:", "Reader ID:", "Status:", "Gender:"};
	std::string contentPlaceholders[] = { "Nguyen Van", "Vu", "Auto", "Auto", "FEMALE" };
	for (int i = 0; i < 5; ++i)
	{
		this->details_[i].description_ = Button(descriptionTopLefts[i], { 80, 20 });
		this->details_[i].description_.SetPlaceholder(descriptionPlaceholders[i]);
		this->details_[i].description_.SetTextColor(BLACK);
		this->details_[i].description_.SetFillColor(rgb(238, 238, 238));
		this->details_[i].description_.SetBorderColor(rgb(238, 238, 238));

		this->details_[i].content_ = Button(contentTopLefts[i], contentDimensions[i]);
		this->details_[i].content_.SetPlaceholder(contentPlaceholders[i]);
		this->details_[i].content_.SetTextColor(rgb(33, 42, 62));
		this->details_[i].content_.SetFillColor(WHITE);
		this->details_[i].content_.SetBorderColor(BLACK);
	}

	this->saveButton_ = Button({ 1542, 349 }, { 120, 45 });
	this->saveButton_.SetPlaceholder("SAVE");
	this->saveButton_.SetTextColor(BLACK);
	this->saveButton_.SetFillColor(rgb(130, 170, 227));
	this->saveButton_.SetBorderColor(rgb(130, 170, 227));
}

int ReaderDetails::Display()
{
	if (!this->status_) { return 0; }

	this->background_.Draw();

	this->title_.Display();

	for (int i = 0; i < 5; ++i)
	{
		this->details_[i].Display();
	}

	if (this->mode_ == 1)
	{
		this->saveButton_.Display();
	}

	return 0;
}

void ReaderDetails::UpdateInfo()
{
	if (this->reader_ == nullptr)
	{
		return;
	}

	std::string firstname = this->reader_->info.GetFirstName();
	std::string lastname = this->reader_->info.GetLastName();
	std::string id = std::to_string(this->reader_->info.GetID());
	std::string readerStauus = this->reader_->info.StringfyStatus();
	std::string gender = this->reader_->info.StringifyGender();

	this->details_[0].content_.SetPlaceholder(firstname);
	this->details_[1].content_.SetPlaceholder(lastname);
	this->details_[2].content_.SetPlaceholder(id);
	this->details_[3].content_.SetPlaceholder(readerStauus);
	this->details_[4].content_.SetPlaceholder(gender);
}

void ReaderDetails::FieldsOnAction()
{
	if (!this->status_) { return; }

	if (this->mode_ != 1) { return; }

	int characterLimits[] = {30, 15};

	for (int i = 0; i < 5; ++i)
	{
		if (i != 0 && i != 1) { continue; }

		if (this->details_[i].content_.IsHover())
		{
			this->details_[i].content_.SetFillColor(rgb(234, 253, 252));
			this->details_[i].content_.SetBorderColor(rgb(130, 170, 227));
		}
		else if (this->details_[i].content_.LeftMouseClicked())
		{
			delay(130);
			this->package_->inputController->Activate(
				&this->details_[i].content_,
				&this->details_[i].content_,
				characterLimits[i],
				true,
				false,
				true
			);
		}
		else
		{
			this->details_[i].content_.SetTextColor(rgb(33, 42, 62));
			this->details_[i].content_.SetFillColor(WHITE);
			this->details_[i].content_.SetBorderColor(BLACK);
		}
	}
}

void ReaderDetails::GenderButtonOnAction()
{
	if (!this->status_) { return; }

	if (this->mode_ != 1) { return; }

	if (this->details_[4].content_.IsHover())
	{
		this->details_[4].content_.SetFillColor(rgb(234, 253, 252));
		this->details_[4].content_.SetBorderColor(rgb(130, 170, 227));
	}
	else if (this->details_[4].content_.LeftMouseClicked())
	{
		delay(130);

		std::string currentOption = this->details_[4].content_.GetPlaceholder();
		if (currentOption == "MALE")
		{
			this->details_[4].content_.SetPlaceholder("FEMALE");
		}
		else
		{
			this->details_[4].content_.SetPlaceholder("MALE");
		}
	}
	else
	{
		this->details_[4].content_.SetTextColor(rgb(33, 42, 62));
		this->details_[4].content_.SetFillColor(WHITE);
		this->details_[4].content_.SetBorderColor(BLACK);
	}
}

int ReaderDetails::SaveButtonOnAction()
{
	if (!this->status_) { return 0; }

	if (this->mode_ != 1) { return 0; }

	if (this->saveButton_.IsHover())
	{
		this->saveButton_.SetTextColor(rgb(234, 253, 252));
		this->saveButton_.SetFillColor(rgb(3, 201, 136));
		this->saveButton_.SetBorderColor(rgb(3, 201, 136));
	}
	else if (this->saveButton_.LeftMouseClicked())
	{
		delay(130);
		return 1;
	}
	else
	{
		this->saveButton_.SetTextColor(BLACK);
		this->saveButton_.SetFillColor(rgb(130, 170, 227));
		this->saveButton_.SetBorderColor(rgb(130, 170, 227));
	}

	return 0;
}
