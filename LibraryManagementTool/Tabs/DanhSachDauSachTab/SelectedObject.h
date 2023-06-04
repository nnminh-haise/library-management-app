#pragma once

#include "../UI/Button.h"

template<typename T>
class SelectedObject
{
public:
	SelectedObject() : active_(false), objectPointer_(nullptr), indicator_(Button({1042, 950}, {500, 30}, BLACK, rgb(236, 242, 255), BLACK)) {}

	SelectedObject(const SelectedObject& other)
	{
		if (this != &other)
		{
			~SelectedObject();

			this->active_ = other.active_;

			this->objectPointer_ = other.objectPointer_;

			this->indicator_ = other.indicator_;
		}
	}

	inline SelectedObject& operator=(const SelectedObject& other)
	{
		if (this == &other) { return this; }

		~SelectedObject();

		this->active_ = other.active_;

		this->objectPointer_ = other.objectPointer_;

		this->indicator_ = other.indicator_;
	}

	inline void Activate() { this->active_ = true; }

	inline void Deactivate() { this->active_ = false; }

	inline bool InActive() { return this->active_; }

	inline void SetObjectPointer(T objectPointer)
	{
		this->objectPointer_ = objectPointer;

		this->indicator_.SetPlaceholder(this->objectPointer_->GetTitle());
	}

	inline T GetObjectPointer() { return this->objectPointer_; }

	inline int Run()
	{
		if (!this->active_) { return 0; }

		this->Display();
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
