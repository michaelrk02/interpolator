#pragma once

union RGBValue {
    struct {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    } values;
    unsigned int dword;
};

struct Color {
    RGBValue rgb;

    Color(void);
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(unsigned int dword);
};

