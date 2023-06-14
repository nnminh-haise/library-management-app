#pragma once

#ifndef UPDATE_READER_PROCESS_H
#define UPDATE_READER_PROCESS_H

#include "ReaderDetail.hpp"
#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../../Helper/Package.h"
#include "../../DauSach/DauSach.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/LinearList.h"

class UpdateReaderProcess : public View
{
public:
	UpdateReaderProcess();

	using View::Activate;

	using View::Deactivate;

	using View::InActive;

	int Run() override;

	void Reset();

	void SetReader(AVL_TREE::Pointer reader);

	void SetDetailCard(ReaderDetails* detailCardPointer);

	void Prepare();

private:
	void Initialize();

	void InitializeElements();

private:
	using View::status_;

	AVL_TREE::Pointer reader_ = nullptr;

	ReaderDetails* detailCardPointer_ = nullptr;

};

#endif // !UPDATE_READER_PROCESS_H
