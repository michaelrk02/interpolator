#include <Color.h>

Color::Color(void) {
    this->rgb.dword = 0x00000000;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) {
    this->rgb.values.r = r;
    this->rgb.values.g = g;
    this->rgb.values.b = b;
}

Color::Color(unsigned int dword) {
    this->rgb.dword = dword;
}

