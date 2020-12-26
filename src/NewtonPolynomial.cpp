#include <algorithm>
#include <cstdlib>
#include <iostream>

#include <debug.h>
#include <NewtonPolynomial.h>

NewtonPolynomial::NewtonPolynomial(void) {
    this->degree = 0;
}

NewtonPolynomial::~NewtonPolynomial(void) {
}

void NewtonPolynomial::initializeData(std::istream &input, float scaleX, float scaleY) {
    this->data.clear();
    TRACE("data initializing");
    while (true) {
        std::pair<float, float> p;
        input >> p.first >> p.second;
        if (input.good()) {
            p.first = p.first * scaleX;
            p.second = p.second * scaleY;
            this->data.push_back(p);
        } else {
            break;
        }
    }
    std::sort(this->data.begin(), this->data.end());
    TRACE("data initialized");
}

unsigned int NewtonPolynomial::getDegree(void) const {
    return this->degree;
}

void NewtonPolynomial::setDegree(unsigned int degree) {
    this->degree = degree;

    this->samples.clear();
    if (degree > 0) {
        this->samples.push_back(this->data[0]);

        if (degree > 1) {
            int additional = (this->data.size() - 2) / (degree - 1);
            int remainder = (this->data.size() - 2) % (degree - 1);
            int start = 1;
            for (int i = 0; i < degree - 1; i++) {
                float total = 0.0f;
                int count = additional + (remainder > 0 ? 1 : 0);
                for (int j = start; j < start + count; j++) {
                    total = total + this->data[j].second;
                }

                float average = total / (float)count;
                int select = start;
                for (int j = start; j < start + count; j++) {
                    float d = std::abs(this->data[j].second - average);
                    if (d < std::abs(this->data[select].second - average)) {
                        select = j;
                    }
                }
                DUMP(average);
                DUMP(this->data[select].first);
                this->samples.push_back(this->data[select]);

                start = start + count;
                remainder--;
            }
        }

        this->samples.push_back(this->data[this->data.size() - 1]);
    }

    this->dd.destroy();
    this->dd.initialize(degree + 1, degree + 1);
    for (int j = 0; j <= degree; j++) {
        for (int i = 0; i <= degree - j; i++) {
            if (j == 0) {
                this->dd.at(i, 0) = this->samples[i].second;
                DUMP(this->dd.at(i, 0));
            } else {
                float f1 = this->dd.at(i + 1, j - 1);
                float f0 = this->dd.at(i, j - 1);
                float x1 = this->samples[i + j].first;
                float x0 = this->samples[i].first;
                TRACE("===");
                DUMP(f1);
                DUMP(f0);
                DUMP(x1);
                DUMP(x0);
                this->dd.at(i, j) = (f1 - f0) / (x1 - x0);
                DUMP(this->dd.at(i, j));
            }
        }
    }
}

float NewtonPolynomial::interpolate(float x) const {
    float result = 0.0f;

    float *xCalc = new float[this->degree];
    for (int i = 0; i < this->degree; i++) {
        xCalc[i] = (x - this->samples[i].first);
        if (i > 0) {
            xCalc[i] = xCalc[i] * xCalc[i - 1];
        }
    }

    for (int i = 0; i <= this->degree; i++) {
        float term = this->dd.at(0, i);
        if (i > 0) {
            term = term * xCalc[i - 1];
        }
        result = result + term;
    }

    delete[] xCalc;

    return result;
}

