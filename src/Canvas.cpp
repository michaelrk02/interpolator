#include <cmath>
#include <stdexcept>

#include <Canvas.h>
#include <debug.h>

Canvas::Canvas(void) {
    this->target = NULL;
}

Canvas::~Canvas(void) {
    TRACE("Canvas::destroy");
}

void Canvas::setTarget(IDrawable &target) {
    this->target = &target;
}

IDrawable &Canvas::getTarget(void) {
    this->checkTarget();
    return *this->target;
}

void Canvas::pushScale(float scale) {
    this->scale.push(scale);
}

float Canvas::getScale(void) const {
    if (this->scale.empty()) {
        return 1.0f;
    }
    return this->scale.top();
}

void Canvas::popScale(void) {
    if (!this->scale.empty()) {
        this->scale.pop();
    }
}

void Canvas::clear(const Color &color) {
    this->checkTarget();
    for (unsigned int x = 0; x < this->target->getWidth(); x++) {
        for (unsigned int y = 0; y < this->target->getHeight(); y++) {
            DUMP(x);
            DUMP(y);
            this->target->put(x, y, color);
        }
    }
}

#define MIN(_A, _B) (((_A) < (_B)) ? (_A) : (_B))
#define MAX(_A, _B) (((_A) > (_B)) ? (_A) : (_B))

void Canvas::drawLine(int x0, int y0, int x1, int y1, const Color &color) {
    this->checkTarget();

    int _x0, _y0, _x1, _y1;
    this->transform(x0, y0, _x0, _y0);
    this->transform(x1, y1, _x1, _y1);
    this->drawLineEx(_x0, _y0, _x1, _y1, color);
}

void Canvas::drawRect(int x0, int y0, int x1, int y1, const Color &color) {
    this->checkTarget();

    int _x0, _y0, _x1, _y1;
    this->transform(x0, y0, _x0, _y0);
    this->transform(x1, y1, _x1, _y1);
    this->drawRectEx(MIN(_x0, _x1), MIN(_y0, _y1), MAX(_x0, _x1), MAX(_y0, _y1), color);
}

void Canvas::drawPoint(int x, int y, unsigned int size, const Color &color) {
    this->checkTarget();

    int x0 = x - (int)size;
    int y0 = y + (int)size;
    int x1 = x + (int)size;
    int y1 = y - (int)size;

    int _x0, _y0, _x1, _y1;
    this->transform(x0, y0, _x0, _y0);
    this->transform(x1, y1, _x1, _y1);
    this->drawRectEx(_x0, _y0, _x1, _y1, color);
}

void Canvas::checkTarget(void) const {
    if (this->target == NULL) {
        throw std::logic_error("target was not set");
    }
}

void Canvas::transform(int xIn, int yIn, int &xOut, int &yOut) {
    this->checkTarget();

    float scale = this->getScale();
    xIn = (int)(scale * (float)xIn);
    yIn = (int)(scale * (float)yIn);

    int width = (int)this->target->getWidth();
    int height = (int)this->target->getHeight();
    int cx = width / 2;
    int cy = height / 2;

    xOut = cx + xIn;
    yOut = cy - yIn;
}

void Canvas::drawLineEx(int x0, int y0, int x1, int y1, const Color &color) {
    this->checkTarget();

    float dx = (float)(x1 - x0);
    float dy = (float)(y1 - y0);
    float dist = std::sqrt(dx * dx + dy * dy);
    float ux = dx / dist;
    float uy = dy / dist;

    int width = (int)this->target->getWidth();
    int height = (int)this->target->getHeight();
    for (unsigned int i = 0; i <= (unsigned int)std::round(dist); i++) {
        int x = x0 + (int)std::round((ux * (float)i));
        int y = y0 + (int)std::round((uy * (float)i));
        if ((0 <= x < width) && (0 <= y < height)) {
            this->target->put(x, y, color);
        }
    }
}

void Canvas::drawRectEx(int x0, int y0, int x1, int y1, const Color &color) {
    this->checkTarget();
    int width = (int)this->target->getWidth();
    int height = (int)this->target->getHeight();
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            if ((0 <= x < width) && (0 <= y < height)) {
                this->target->put(x, y, color);
            }
        }
    }
}

