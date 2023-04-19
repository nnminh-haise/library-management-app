#pragma once

#include "../../Helper/Helper.h"

class Button {
private:
    HELPER::Coordinate topLeft;
    HELPER::Coordinate bottomRight;
    HELPER::Dimension dimension;
    HELPER::Fill fill;
    int textColor;
    std::string placeholder;
    bool isPointed;
    bool active;
    bool inputMode;
    int clickedCount;
    bool leftClicked;

public:
    Button();

    Button(HELPER::Coordinate topLeft, int with, int height, int textColor = BLACK, int fillcolor = WHITE, int borderColor = BLACK);

    Button(HELPER::Coordinate topLeft, HELPER::Dimension dimension, int textColor = BLACK, int fillcolor = WHITE, int borderColor = BLACK);

    Button(HELPER::Coordinate topLeft, HELPER::Coordinate bottomRight, int textColor = BLACK, int fillcolor = WHITE, int borderColor = BLACK);

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

    void SetStatus(bool status);

    bool GetStatus();

    void Display();

    bool IsPointed();

    bool IsHover();

    bool LeftMouseClicked();

    bool RightMouseClicked();

    void SetClickCount(int amount);

    int GetClickCount();

    void ResetClickCount();

    bool NotYetClicked();

    void IncreaseClickCount(int amount = 1);

    void DecreaseClickCount(int amount = 1);
};
