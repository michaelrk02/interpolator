#include <cstring>
#include <stdexcept>

#include <Bitmap.h>
#include <debug.h>

Bitmap::Bitmap(void) {
    std::memset(&this->header, 0, sizeof(BitmapHeader));
}

Bitmap::~Bitmap(void) {
    this->destroy();
}

void Bitmap::initialize(unsigned int width, unsigned int height) {
    if (!this->pixelData.isInitialized()) {
        std::memset(&this->header, 0, sizeof(BitmapHeader));

        BitmapHeader &h = this->header;
        h.identifier = 0x4d42; // 'BM'
        h.pixelArrayOffset = sizeof(BitmapHeader);

        DIBHeader &dh = h.dibHeader;
        dh.headerSize = sizeof(DIBHeader);
        dh.width = (int)width;
        dh.height = -((int)height); // use top-down scanline
        dh.colorPlanes = 1;
        dh.bitsPerPixel = 24;
        dh.compressionMethod = 0;
        dh.horizontalResolution = 2835;
        dh.verticalResolution = 2835;

        unsigned int rows = this->getRows();
        unsigned int cols = this->getCols();
        DUMP(rows);
        DUMP(cols);

        h.fileSize = sizeof(BitmapHeader) + rows * cols * 4;

        this->pixelData.initialize(rows, cols * 4);
    } else {
        throw std::runtime_error("the bitmap was already initialized");
    }
}

void Bitmap::write(std::ostream &output) const {
    this->check();

    output.write((char *)&this->header, sizeof(BitmapHeader));

    unsigned int rows = this->getRows();
    unsigned int cols = this->getCols();
    output.write((char *)this->pixelData.getData(), rows * cols * 4);
}

void Bitmap::destroy(void) {
}

Color Bitmap::get(unsigned int x, unsigned int y) const {
    this->check();

    unsigned int width = this->getWidth();
    unsigned int height = this->getHeight();
    if ((x >= width) || (y >= height)) {
        throw std::out_of_range("unable to get pixel: out of range error");
    }

    Color color;
    unsigned int cols = this->getCols();
    unsigned int offset = y * cols * 4 + x * 3;
    std::memcpy(&color.rgb.dword, this->pixelData.getData() + offset, 3);
    return color;
}

void Bitmap::put(unsigned int x, unsigned int y, const Color &color) {
    this->check();

    unsigned int width = this->getWidth();
    unsigned int height = this->getHeight();
    if ((x >= width) || (y >= height)) {
        throw std::out_of_range("unable to put pixel: out of range error");
    }

    unsigned int cols = this->getCols();
    unsigned int offset = y * cols * 4 + x * 3;
    std::memcpy(this->pixelData.getData() + offset, &color.rgb.dword, 3);

    TRACE("Bitmap::put_end");
}

unsigned int Bitmap::getWidth(void) const {
    return (unsigned int)this->header.dibHeader.width;
}

unsigned int Bitmap::getHeight(void) const {
    return (unsigned int)(-this->header.dibHeader.height);
}

unsigned int Bitmap::getRows(void) const {
    return (unsigned int)(-this->header.dibHeader.height);
}

unsigned int Bitmap::getCols(void) const {
    return (24 * this->header.dibHeader.width + 31) / 32;
}

void Bitmap::check(void) const {
    if (!this->pixelData.isInitialized()) {
        throw std::logic_error("cannot write bitmap to stream: pixel data was not initialized");
    }
}

