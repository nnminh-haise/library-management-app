#pragma once

#include "../../Helper/Helper.h"

class Button {
public:
    Button();

    Button(HELPER::Coordinate topLeft, int with, int height, int textColor = BLACK, int fillcolor = WHITE, int borderColor = BLACK);

    Button(HELPER::Coordinate topLeft, HELPER::Dimension dimension, int textColor = BLACK, int fillcolor = WHITE, int borderColor = BLACK);

    void SetDefaultValue(const std::string& defaultValue = "button");

    std::string GetDefalutValue();

    void SetTopLeft(HELPER::Coordinate topLeft);

    HELPER::Coordinate GetTopLeft();

    void SetDimension(HELPER::Dimension newDimension);

    HELPER::Dimension GetDimension();

    bool UpdateWithNewTopLeft();

    HELPER::Coordinate GetBottomRight();

    void SetFillColor(int color);

    int GetFillColor();

    void SetTextColor(int color);

    int GetTextColor();

    void SetBorderColor(int color);

    int GetBorderColor();

    void SetPlaceholder(std::string placeholder);

    std::string GetPlaceholder();

    void Activate();

    void Deactivate();

    bool IsActive();

    void Display();

    bool IsPointed();

    bool IsHover();

    bool LeftMouseClicked();

    bool RightMouseClicked();

private:
    std::string defaultValue_;
    std::string placeholder;
    HELPER::Coordinate topLeft;
    HELPER::Coordinate bottomRight;
    HELPER::Dimension dimension;
    HELPER::Fill fill;
    int textColor;
    bool isPointed;
    bool active;
    bool inputMode;
    int clickedCount;
    bool leftClicked;
};
