#include <fstream>
#include <iostream>
#include <string>

#include <Bitmap.h>
#include <Canvas.h>
#include <NewtonPolynomial.h>
#include <debug.h>

#define IMAGE_SIZE  800

int main() {
    while (true) {
        std::string inputStr;
        std::cout << "Enter input file: ";
        std::getline(std::cin, inputStr);

        TRACE("loading");

        std::ifstream input(inputStr.c_str());
        if (input.is_open()) {
            NewtonPolynomial np;

            float sx, sy;
            std::cout << "Enter X scale (1 for default): ";
            (std::cin >> sx).ignore();
            std::cout << "Enter Y scale (1 for default): ";
            (std::cin >> sy).ignore();

            np.initializeData(input, sx, sy);

            int degree;
            do {
                std::cout << "Enter polynomial degree (>0): ";
                (std::cin >> degree).ignore();
            } while (degree == 0);
            np.setDegree(degree);

            char show;
            std::cout << "Show interpolated values? (y/n) ";
            (std::cin >> show).ignore();
            if ((show == 'Y') || (show == 'y')) {
                std::cout << "Interpolated values: " << std::endl;
                for (int i = 0; i < np.data.size(); i++) {
                    std::cout << np.data[i].first << " -> " << np.interpolate(np.data[i].first) << std::endl;
                }
            }

            std::string outputStr;
            std::cout << "Enter output file (bitmap): ";
            std::getline(std::cin, outputStr);

            std::ofstream output(outputStr.c_str(), std::ios::binary);
            if (output.is_open()) {
                unsigned int width, height;
                std::cout << "Enter image width (1024 for default): ";
                (std::cin >> width).ignore();
                std::cout << "Enter image height (1024 for default): ";
                (std::cin >> height).ignore();

                std::cout << "Generating bitmap..." << std::endl;

                Bitmap bmp;
                bmp.initialize(width, height);

                Canvas canvas;
                canvas.setTarget(bmp);
                canvas.clear(0xFFFFFF);

                for (int i = 0; i < np.data.size(); i++) {
                    int x = (int)np.data[i].first;
                    int y = (int)np.data[i].second;
                    canvas.drawPoint(x, y, 2, Color(0x000000));
                }

                int xMin = (int)np.data[0].first;
                int xMax = (int)np.data[np.data.size() - 1].first;
                for (int x0 = xMin; x0 <= xMax - 1; x0++) {
                    int y0 = (int)np.interpolate((float)x0);
                    int x1 = x0 + 1;
                    int y1 = (int)np.interpolate((float)x1);
                    canvas.drawLine(x0, y0, x1, y1, Color(0xFF0000));
                }

                bmp.write(output);

                std::cout << "Done" << std::endl;
                output.close();
            } else {
                std::cout << "Cannot write to: " << outputStr << std::endl;
            }

            input.close();
        } else {
            std::cout << "Cannot read from: " << inputStr << std::endl;
        }
    }

    return 0;
}

