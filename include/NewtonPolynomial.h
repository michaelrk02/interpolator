#pragma once

#include <utility>
#include <vector>

#include "Array2D.h"

class NewtonPolynomial {
public:
    NewtonPolynomial(void);
    ~NewtonPolynomial(void);

    void initializeData(std::istream &input, float scaleX = 1.0f, float scaleY = 1.0f);

    unsigned int getDegree(void) const;
    void setDegree(unsigned int degree);

    float interpolate(float x) const;

public:
    std::vector<std::pair<float, float>> data;
    std::vector<std::pair<float, float>> samples;
    Array2D<float> dd;
    unsigned int degree;
};

