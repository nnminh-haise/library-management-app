#pragma once

#ifndef NEW_READER_H
#define NEW_READER_H

#include "../UI/Button.h"
#include "../UI/Elements.h"
#include "../UI/Datasheet.h"
#include "../UI/Component.hpp"
#include "../../Helper/Package.h"
#include "../../DauSach/DauSach.h"
#include "../../TheDocGia/TheDocGia.h"
#include "../../DataStructures/LinearList.h"

class ReaderDetails
{
public:
	ReaderDetails();

	void Activate();

	void Deactivate();

	bool InActive();

	int Run();

	void Reset();

	void SetReader(AVL_TREE::Pointer reader);

	void SetPackage(Package* package);

	void SetMode(int mode);

	int SaveButtonOnAction();

	LinkedButton& AccessFields(int index);

private:
	void Initialize();

	void InitializeElements();

	int Display();

	void UpdateInfo();

	void FieldsOnAction();

private:
	bool status_ = false;

	int mode_ = 0;

	Package* package_ = nullptr;

	AVL_TREE::Pointer reader_ = nullptr;

private:
	HELPER::Fill background_;

	Button title_;

	LinkedButton details_[5];

	Button saveButton_;

	Button cover_;
};

#endif // !NEW_READER_H


