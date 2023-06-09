#pragma once

#ifndef SHEETS
#define SHEETS

#include <iostream>
#include <string>
#include <format>
#include "Button.h"
#include "Component.hpp"
#include "../../Helper/ConstantsAndGlobalVariables.h"

namespace TABLE
{
	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	class Record : public View 
	{
	public:
		inline Record();

		inline Record(const TABLE::Record<OBJECT_TYPE, ATTRIBUTE_COUNT>& other);

		inline ~Record();

		inline TABLE::Record<OBJECT_TYPE, ATTRIBUTE_COUNT>& operator= (const TABLE::Record<OBJECT_TYPE, ATTRIBUTE_COUNT>& other);

		inline Button& operator[](int index);

		inline int Size();

		inline void Display();

	public:

		virtual bool Create(int recordIndex, OBJECT_TYPE* objectPointer) = 0;

	public:
		using View::status_;

		OBJECT_TYPE* objectPointer_ = nullptr;

		Button attributes_[ATTRIBUTE_COUNT];

		Button indexIndicator_;

		int recordIndex_ = -1;

		int recordSize_ = ATTRIBUTE_COUNT;
	};

	//*---------------------------------------------------------------------

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Record()
	{
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Record(const TABLE::Record<OBJECT_TYPE, ATTRIBUTE_COUNT>& other)
	{
		if (this != &other)
		{
			this->~Record();

			this->status_ = other.status_;
			this->objectPointer_ = other.objectPointer_;
			this->recordSize_ = other.recordSize_;
			for (int i = 0; i < this->recordSize_; ++i)
			{
				this->attributes_[i] = other.atrributes_[i];
			}
			this->recordIndex_ = other.recordIndex_;
		}
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::~Record()
	{
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline TABLE::Record<OBJECT_TYPE, ATTRIBUTE_COUNT>& Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::operator=(const TABLE::Record<OBJECT_TYPE, ATTRIBUTE_COUNT>& other)
	{
		if (this == &other) { return *this; }

		this->~Record();

		this->status_ = other.status_;
		this->objectPointer_ = other.objectPointer_;
		this->recordSize_ = other.recordSize_;
		for (int i = 0; i < this->recordSize_; ++i)
		{
			this->attributes_[i] = other.atrributes_[i];
		}
		this->recordIndex_ = other.recordIndex_;
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Button& Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::operator[](int index)
	{
		if (index < 0 || index > ATTRIBUTE_COUNT) { throw std::logic_error("[ERROR] Index out of range! (DATASHEETS::Record::operator[])"); }

		if (index == 0) { return this->indexIndicator_; }

		return this->attributes_[index];
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline int Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Size()
	{
		return this->recordSize_;
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline void Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Display()
	{
		if (!this->status_) { return; }

		this->indexIndicator_.Display();

		for (int i = 0; i < ATTRIBUTE_COUNT; ++i) { this->attributes_[i].Display(); }
	}
}

#endif // !SHEETS
