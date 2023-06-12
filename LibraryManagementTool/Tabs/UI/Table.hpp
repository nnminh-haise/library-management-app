#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include <format>
#include "Button.h"
#include "Component.hpp"
#include "../../Helper/ConstantsAndGlobalVariables.h"
#include "../../Helper/Helper.h"

namespace TABLE
{
	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	class Record : public View 
	{
	public:
		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		inline Button& operator[](int index);

		inline int Run() override;

		virtual bool Create(int recordIndex, BOOK_TITLE::BookTitle* objectPointer, HELPER::Coordinate topLeft) = 0;

		HELPER::Dimension GetDimension();

	public:
		using View::status_;

		OBJECT_TYPE* objectPointer_ = nullptr;

		Button attributes_[ATTRIBUTE_COUNT];

		Button indexIndicator_{ 
			{0, 0}, 
			{DATASHEET_DEFAULT_PROPERTIES::LETTER_WIDTH * 5 + 20, DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT}
		};

		int recordIndex_ = -1;

		int attributeCount_ = ATTRIBUTE_COUNT;

		HELPER::Coordinate topLeft_;

		HELPER::Dimension dimension_;
	};

	//*---------------------------------------------------------------------

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Button& Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::operator[](int index)
	{
		if (index < 0 || index > ATTRIBUTE_COUNT)
		{
			throw std::logic_error("[ERROR] Index out of range! (DATASHEETS::Record::operator[])");
		}

		if (index == 0) { return this->indexIndicator_; }

		return this->attributes_[index];
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline int Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Run()
	{
		if (!this->status_) { return 0; }

		if (this->objectPointer_ == nullptr)
		{
			std::cerr << "[ERROR] Object's pointer is NULL! (Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Run)\n";
		}

		this->indexIndicator_.Display();

		for (int i = 0; i < this->attributeCount_; ++i) { this->attributes_[i].Display(); }

		return 1;
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline HELPER::Dimension Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::GetDimension()
	{
		return this->dimension_;
	}

	//*---------------------------------------------------------------------

	template<typename RECORD_TYPE, unsigned int RECORD_COUNT>
	class Table : public View
	{
	public:
		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		inline RECORD_TYPE& operator[](int index);

		inline int Run() override;

		HELPER::Coordinate& TopLeft();

		HELPER::Dimension& Dimension();

	public:
		using View::status_;

		RECORD_TYPE records_[RECORD_COUNT];

		int recordCount_ = RECORD_COUNT;

		HELPER::Coordinate topLeft_;

		HELPER::Dimension dimension_;
	};

	//*---------------------------------------------------------------------

	template<typename RECORD_TYPE, unsigned int RECORD_COUNT>
	inline RECORD_TYPE& Table<RECORD_TYPE, RECORD_COUNT>::operator[](int index)
	{
		if (index < 0 || index >= RECORD_COUNT)
		{
			throw std::out_of_range("[ERROR] Table's record access violation! (Table<RECORD_TYPE, RECORD_COUNT>::operator[])");
		}

		return this->records_[index];
	}

	template<typename RECORD_TYPE, unsigned int RECORD_COUNT>
	inline int Table<RECORD_TYPE, RECORD_COUNT>::Run()
	{
		if (!this->status_) { return 0; }

		for (int i = 0; i < this->recordCount_; ++i)
		{
			this->records_[i].Run();
		}

		return 0;
	}

	template<typename RECORD_TYPE, unsigned int RECORD_COUNT>
	inline HELPER::Coordinate& Table<RECORD_TYPE, RECORD_COUNT>::TopLeft()
	{
		return this->topLeft_;
	}

	template<typename RECORD_TYPE, unsigned int RECORD_COUNT>
	inline HELPER::Dimension& Table<RECORD_TYPE, RECORD_COUNT>::Dimension()
	{
		return this->dimension_;
	}

	//*---------------------------------------------------------------------

	template<typename TABLE_TYPE>
	class Controller : public View
	{
	public:
		Controller();

		Controller(const Controller<TABLE_TYPE>& other);

		~Controller();

		Controller<TABLE_TYPE>& operator= (const Controller<TABLE_TYPE>& other);

		TABLE_TYPE& operator[] (int index);

		using View::Activate;

		using View::Deactivate;

		using View::InActive;

		void Initialize(int tableCount);

		inline int Run() override;

		void SetTopLeft(HELPER::Coordinate topLeft);

	public:
		using View::status_;

		TABLE_TYPE* tables_ = nullptr;

		int tableCount_ = 0;

		int currentTableIndex_ = -1;

		HELPER::Coordinate topLeft_;
	};

	template<typename TABLE_TYPE>
	inline Controller<TABLE_TYPE>::Controller()
	{
	}

	template<typename TABLE_TYPE>
	inline Controller<TABLE_TYPE>::Controller(const Controller<TABLE_TYPE>& other)
	{
		if (this != &other)
		{
			this->~Controller();

			this->status_ = other.status_;
			
			this->tableCount_ = other.tableCount_;

			this->tables_ = new TABLE_TYPE[other.tableCount_];
			for (int i = 0; i < other.tableCount_; ++i)
			{
				this->tables_[i] = other.tables_[i];
			}

			this->currentTableIndex_ = other.currentTableIndex_;
		}
	}

	template<typename TABLE_TYPE>
	inline Controller<TABLE_TYPE>::~Controller()
	{
		delete[] this->tables_;
	}

	template<typename TABLE_TYPE>
	inline Controller<TABLE_TYPE>& Controller<TABLE_TYPE>::operator=(const Controller<TABLE_TYPE>& other)
	{
		if (this == &other) { return *this; }

		this->~Controller();

		this->status_ = other.status_;

		this->tableCount_ = other.tableCount_;

		this->tables_ = new TABLE_TYPE[other.tableCount_];
		for (int i = 0; i < other.tableCount_; ++i)
		{
			this->tables_[i] = other.tables_[i];
		}

		this->currentTableIndex_ = other.currentTableIndex_;
	}

	template<typename TABLE_TYPE>
	inline TABLE_TYPE& Controller<TABLE_TYPE>::operator[](int index)
	{
		if (this->tables_ == nullptr)
		{
			throw std::logic_error("[ERROR] Table access violation! Table list is empty! (Controller<TABLE_TYPE>::operator[])");
		}

		if (index < 0 || index >= this->tableCount_)
		{
			throw std::out_of_range("[ERROR] Table access violation! (Controller<TABLE_TYPE>::operator[])");
		}
	}

	template<typename TABLE_TYPE>
	inline void Controller<TABLE_TYPE>::Initialize(int tableCount)
	{
		this->tableCount_ = tableCount;

		this->tables_ = new TABLE_TYPE[tableCount];

		this->currentTableIndex_ = 0;
	}

	template<typename TABLE_TYPE>
	inline int Controller<TABLE_TYPE>::Run()
	{
		if (!this->status_) { return 0; }

		if (this->currentTableIndex_ == -1)
		{
			std::cerr << "[ERROR] Undefined table's index! (Controller<TABLE_TYPE>::Run)\n";
			throw std::logic_error("[ERROR] Undefined table's index! (Controller<TABLE_TYPE>::Run)\n");
		}
		this->tables_[this->currentTableIndex_].Run();

		return 0;
	}

	template<typename TABLE_TYPE>
	inline void Controller<TABLE_TYPE>::SetTopLeft(HELPER::Coordinate topLeft)
	{
		this->topLeft_ = topLeft;
	}
}

#endif // !TABLE_H
