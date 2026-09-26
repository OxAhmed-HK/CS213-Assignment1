#include <iostream>
#include "Image_Class.h"

using namespace std;

// ==================== FILTER 1 ===================== //
void Grayscale(Image &image)
{
    for (int _x = 0; _x < image.width; _x++)
    {
        for (int _y = 0; _y < image.height; _y++)
        {
            int r = image(_x, _y, 0);
            int g = image(_x, _y, 1);
            int b = image(_x, _y, 2);

            int gray = (r + g + b) / 3;

            image(_x, _y, 0) = gray;
            image(_x, _y, 1) = gray;
            image(_x, _y, 2) = gray;
        }
    }
}

// ==================== FILTER 2 ===================== //

int main()
{

    return 0;
}