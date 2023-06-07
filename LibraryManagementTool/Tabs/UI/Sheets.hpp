#pragma once

#ifndef SHEETS
#define SHEETS

#include <iostream>
#include <string>
#include <format>
#include "Button.h"
#include "Component.hpp"
#include "../../Helper/ConstantsAndGlobalVariables.h"

namespace DATASHEETS
{
	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	class Record : public View 
	{
	public:
		inline Button& operator[](int index);

		inline Button& AccessIndexCell();

		inline int Size();

		inline void Display();

	public:

		virtual bool Create(int recordIndex, OBJECT_TYPE* objectPointer) = 0;

	public:
		const int rowHeight_ = DATASHEET_DEFAULT_PROPERTIES::ROW_HEIGHT;

		int rowWidth_ = -1;

	public:
		using View::status_;

		OBJECT_TYPE* objectPointer_ = nullptr;

		Button attributes_[ATTRIBUTE_COUNT];

		int recordIndex_ = -1;

		Button indexIndicator_;
	};

	//*---------------------------------------------------------------------

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Button& Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::operator[](int index)
	{
		if (index < 0 || index >= ATTRIBUTE_COUNT) { throw std::logic_error("[ERROR] Index out of range! (DATASHEETS::Record::operator[])"); }

		return this->attributes_[index];
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline Button& Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::AccessIndexCell()
	{
		return this->indexIndicator_;
	}

	template<typename OBJECT_TYPE, unsigned int ATTRIBUTE_COUNT>
	inline int Record<OBJECT_TYPE, ATTRIBUTE_COUNT>::Size()
	{
		return ATTRIBUTE_COUNT;
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
