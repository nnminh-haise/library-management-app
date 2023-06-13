#pragma once

#include "../UI/Button.h"

template<typename T>
class SelectedObject
{
public:
	SelectedObject() : active_(false), objectPointer_(nullptr), indicator_(Button({147, 940}, {600, 40}, BLACK, rgb(236, 242, 255), rgb(236, 242, 255))) {}

	SelectedObject(const SelectedObject& other)
	{
		if (this != &other)
		{
			this->~SelectedObject();

			this->active_ = other.active_;

			this->objectPointer_ = other.objectPointer_;

			this->indicator_ = other.indicator_;
		}
	}

	inline SelectedObject& operator=(const SelectedObject& other)
	{
		if (this == &other) { return *this; }

		this->~SelectedObject();

		this->active_ = other.active_;

		this->objectPointer_ = other.objectPointer_;

		this->indicator_ = other.indicator_;
	}

	inline void Activate() { this->active_ = true; }

	inline void Deactivate() { this->active_ = false; }

	inline bool InActive() { return this->active_; }

	inline Button& AccessIndicator()
	{
		return this->indicator_;
	}

	inline void SetObjectPointer(T objectPointer)
	{
		this->objectPointer_ = objectPointer;
	}

	inline T GetObjectPointer() { return this->objectPointer_; }

	inline bool IndicatorObAction()
	{
		if (!this->active_) { return false; }

		if (this->objectPointer_ == nullptr) { return false; }

		if (this->indicator_.IsHover())
		{
			this->indicator_.SetFillColor(rgb(130, 170, 227));
			this->indicator_.SetTextColor(WHITE);
		}
		else if (this->indicator_.LeftMouseClicked())
		{
			delay(100);
			return true;
		}
		else
		{
			this->indicator_.SetTextColor(BLACK);
			this->indicator_.SetFillColor(rgb(236, 242, 255));
			this->indicator_.SetBorderColor(BLACK);
		}

		return false;
	}

	inline int Run()
	{
		if (!this->active_) { return 0; }

		this->Display();
		if (this->IndicatorObAction()) { return 1; }

		return 0;
	}

private:
	inline void Display()
	{
		if (!this->active_) { return; }

		if (this->objectPointer_ == nullptr)
		{
			this->indicator_.SetPlaceholder("Unselected!");
		}

		this->indicator_.Display();
	}

private:
	bool active_;

	T objectPointer_;

	Button indicator_;
};
