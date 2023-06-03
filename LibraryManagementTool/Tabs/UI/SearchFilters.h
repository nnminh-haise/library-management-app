#pragma once

#include <iostream>
#include "Button.h"

class Filter
{
    public:
    Filter() : value_(false), label_(Button({0, 0}, {100, 40}, BLACK, WHITE, WHITE)), indicator_(Button({0, 0}, {100, 30}, BLACK, WHITE, BLACK)) {}

    Filter(const Filter& other)
    {
        if (this != &other)
        {
            this->value_ = other.value_;
            this->label_ = other.label_;
            this->indicator_ = other.indicator_;
        }
    }

    inline Filter& operator=(const Filter& other)
    {
        if (this == &other) { return *this; }

        this->value_ = other.value_;
        this->label_ = other.label_;
        this->indicator_ = other.indicator_;
    }

    inline void SetTopLeft(HELPER::Coordinate topLeft)
    {
        this->label_.SetTopLeft(topLeft);
        this->label_.UpdateWithNewTopLeft();
        this->indicator_.SetTopLeft({ topLeft.x, topLeft.y + 40 });
        this->indicator_.UpdateWithNewTopLeft();
    }

    inline void SetPlaceholder(std::string placeholder)
    {
        this->label_.SetPlaceholder(placeholder);
    }

    inline void SetValue(bool value)
    {
        this->value_ = value;
        this->indicator_.SetPlaceholder(value ? "On" : "Off");
        this->indicator_.SetTextColor(value ? WHITE : BLACK);
    }

    inline bool GetValue() { return this->value_; }

    inline void Display()
    {
        this->label_.Display();
        this->indicator_.Display();
    }

    inline void IndicatorOnAction()
    {
        if (this->indicator_.IsHover())
        {
            this->indicator_.SetFillColor(this->HOVER_FILL_COLOR);
        }
        else if (this->indicator_.LeftMouseClicked())
        {
            delay(100);

            this->indicator_.SetFillColor(this->HOVER_FILL_COLOR);
            this->SetValue(!this->value_);
        }
        else
        {
            this->indicator_.SetFillColor(this->value_ ? this->ON_BACKGROUND_FILL_COLOR : this->OFF_BACKGROUND_FILL_COLOR);
        }
    }

    inline void Run()
    {
        this->Display();
        this->IndicatorOnAction();
    }

    private:
    const int OFF_BACKGROUND_FILL_COLOR = rgb(241, 246, 249);
    const int ON_BACKGROUND_FILL_COLOR = rgb(130, 170, 227);
    const int HOVER_FILL_COLOR = rgb(157, 178, 191);

    private:
    bool value_ = false;

    Button label_;

    Button indicator_;
};

class SearchFilters
{
    public:
    SearchFilters() : active_(false), filters_(nullptr) {}

    SearchFilters(int filterCount) : active_(false), filterCount_(filterCount)
    {
        this->filters_ = new Filter[filterCount];
    }

    SearchFilters(const SearchFilters& other)
    {
        if (this != &other)
        {
            this->active_ = other.active_;
            this->filterCount_ = other.filterCount_;
            this->filters_ = new Filter[this->filterCount_];
            for (int i = 0; i < this->filterCount_; ++i)
            {
                this->filters_[i] = other.filters_[i];
            }
        }
    }

    ~SearchFilters()
    {
        delete[] this->filters_;
    }

    inline void Activate() { this->active_ = true; }

    inline void Deactivate() { this->active_ = false; }

    inline bool InActive() { return this->active_; }

    inline SearchFilters& operator= (const SearchFilters& other)
    {
        if (this == &other) { return *this; }

        // this->~SearchFilters();

        this->active_ = other.active_;
        this->filterCount_ = other.filterCount_;
        this->filters_ = new Filter[this->filterCount_];
        for (int i = 0; i < this->filterCount_; ++i) { this->filters_[i] = other.filters_[i]; }

        return *this;
    }

    inline Filter& operator[] (const int& index)
    {
        if (index < 0 || index >= this->filterCount_) { throw std::logic_error("[ERROR] Filters: Index out of range! (method `operator[]`)"); }

        return this->filters_[index];
    }

    inline Filter At(const int& index)
    {
        if (index < 0 || index >= this->filterCount_) { throw std::logic_error("[ERROR] Filters: Index out of range! (method `At`)"); }

        return this->filters_[index];
    }

    inline bool FilterValue(const int& index)
    {
        if (index < 0 || index >= this->filterCount_) { throw std::logic_error("[ERROR] Filters: Index out of range! (method `FilterValue`)"); }

        return this->filters_[index].GetValue();
    }

    inline int Size() { return this->filterCount_; }

    //! This method is under development
    // inline int GetFilters()
    // {
    //     int decimal = 0;
    //     int power = 0;

    //     for (int i = this->filterCount_ - 1; i >= 0; --i)
    //     {
    //         if (this->filters_[i]) { decimal += pow(2, power); }
    //         power++;
    //     }

    //     return decimal;
    // }

    inline void Display()
    {
        if (!this->active_) { return; }

        for (int i = 0; i < this->filterCount_; ++i) { this->filters_[i].Run(); }
    }

    private:
    bool active_;
    int filterCount_ = 0;
    Filter* filters_ = nullptr;
};
