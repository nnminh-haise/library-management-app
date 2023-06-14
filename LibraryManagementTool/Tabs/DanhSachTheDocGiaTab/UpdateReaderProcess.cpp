#include "UpdateReaderProcess.hpp"

UpdateReaderProcess::UpdateReaderProcess()
{
	this->Initialize();

	this->InitializeElements();
}

int UpdateReaderProcess::Run()
{
	if (!this->status_) { return 0; }

	if (this->reader_ == nullptr) {
		throw std::logic_error("[ERROR] Reader's pointer is NULL! (UpdateReaderProcess::Run())");
	}

	if (this->detailCardPointer_ == nullptr)
	{
		throw std::logic_error("[ERROR] Detail card's pointer is NULL! (UpdateReaderProcess::Run())");
	}

	return 0;
}

void UpdateReaderProcess::Reset()
{
}

void UpdateReaderProcess::SetReader(AVL_TREE::Pointer reader)
{
	this->reader_ = reader;
}

void UpdateReaderProcess::SetDetailCard(ReaderDetails* detailCardPointer)
{
	this->detailCardPointer_ = detailCardPointer;
}

void UpdateReaderProcess::Initialize()
{
}

void UpdateReaderProcess::InitializeElements()
{
}

void UpdateReaderProcess::Prepare()
{
	if (this->reader_ == nullptr) {
		std::cerr << "[ERROR] Reader's pointer is NULL! (UpdateReaderProcess::Run())\n";
		return;
	}

	if (this->detailCardPointer_ == nullptr)
	{
		std::cerr << "[ERROR] Detail card's pointer is NULL! (UpdateReaderProcess::Run())\n";
		return;
	}

	this->detailCardPointer_->Activate();
	this->detailCardPointer_->SetMode(1);
	this->detailCardPointer_->SetReader(this->reader_);
}
