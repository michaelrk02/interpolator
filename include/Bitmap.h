//
// Bitmap.h: helper class for generating bitmap images
//
// Reference: https://en.wikipedia.org/wiki/BMP_file_format
//
#pragma once

#include <iostream>

#include "Array2D.h"
#include "Color.h"
#include "Drawable.h"

#pragma pack(push, 1)

// From BITMAPINFOHEADER (Windows NT, 3.1x or later)
struct DIBHeader {
    unsigned int headerSize;
    int width;
    int height;
    unsigned short colorPlanes;
    unsigned short bitsPerPixel;
    unsigned int compressionMethod;
    unsigned int imageSize;
    int horizontalResolution;
    int verticalResolution;
    unsigned int colors;
    unsigned int importantColors;
};

struct BitmapHeader {
    unsigned short identifier;
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrayOffset;
    DIBHeader dibHeader;
};

#pragma pack(pop)

class Bitmap :
    public IDrawable {
public:
    Bitmap(void);
    ~Bitmap(void);

    void initialize(unsigned int width, unsigned int height);
    void write(std::ostream &output) const;
    void destroy(void);

    Color get(unsigned int x, unsigned int y) const;
    void put(unsigned int x, unsigned int y, const Color &color);
    unsigned int getWidth(void) const;
    unsigned int getHeight(void) const;

protected:
    unsigned int getCols(void) const;
    unsigned int getRows(void) const;

    void check(void) const;

private:
    BitmapHeader header;
    Array2D<unsigned char> pixelData;
};

