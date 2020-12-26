#pragma once

#include "Color.h"

class IDrawable {
public:
    virtual Color get(unsigned int x, unsigned int y) const = 0;
    virtual void put(unsigned int x, unsigned int y, const Color &color) = 0;
    virtual unsigned int getWidth(void) const = 0;
    virtual unsigned int getHeight(void) const = 0;
};

