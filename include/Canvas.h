#pragma once

#include <stack>

#include "Drawable.h"

class Canvas {
public:
    Canvas(void);
    ~Canvas(void);

    void setTarget(IDrawable &target);
    IDrawable &getTarget(void);

    void pushScale(float scale);
    float getScale(void) const;
    void popScale(void);

    void clear(const Color &color);
    void drawLine(int x0, int y0, int x1, int y1, const Color &color);
    void drawRect(int x0, int y0, int x1, int y1, const Color &color);
    void drawPoint(int x, int y, unsigned int size, const Color &color);

protected:
    void checkTarget(void) const;

private:
    void transform(int xIn, int yIn, int &xOut, int &yOut);
    void drawLineEx(int x0, int y0, int x1, int y1, const Color &color);
    void drawRectEx(int x0, int y0, int x1, int y1, const Color &color);

private:
    IDrawable *target;
    std::stack<float> scale;
};

