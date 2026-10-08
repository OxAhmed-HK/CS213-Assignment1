#include <iostream>
#include <string>
#include <limits>
#include "Image_Class.h"
using namespace std;
//=======================Filter4======================//
void Enter_Colors_Values(int &Red, int &Green, int &Blue)
{
    cout << "Enter value of Red from 0 to 255 : ";
    cin >> Red;
    while (Red < 0 || Red > 255 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter value of Red from 0 to 255 : ";
        cin >> Red;
    }
    cout << "\nEnter value of Green from 0 to 255 : ";
    cin >> Green;
    while (Green < 0 || Green > 255 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "\nEnter value of Green from 0 to 255 : ";
        cin >> Green;
    }

    cout << "\nEnter value of Blue from 0 to 255 : ";
    cin >> Blue;
    while (Blue < 0 || Blue > 255 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "\nEnter value of Blue from 0 to 255 : ";
        cin >> Blue;
    }
}

int Enter_New_Thickness(int &Thickness)
{
    cout << "Enter the thickness of Frame : ";
    cin >> Thickness;
    while (Thickness <= 0 || Thickness > 500 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter the thickness of Frame : ";
        cin >> Thickness;
    }

    return Thickness;
}

void Calculate_NewHeight_NewWidth(int &Thickness, int &NewHeight, int &NewWidth, Image &image)
{
    NewWidth = (image.width) + (2 * Thickness);
    NewHeight = (image.height) + (2 * Thickness);
}

Image FrameFilter(Image &image)
{
    int NewWidth, NewHeight, Thickness;

    Enter_New_Thickness(Thickness);

    Calculate_NewHeight_NewWidth(Thickness, NewHeight, NewWidth, image);

    Image image2(NewWidth, NewHeight);

    int Red, Green, Blue;

    Enter_Colors_Values(Red, Green, Blue);

    for (int x = 0; x < image2.width; x++)
    {
        for (int y = 0; y < image2.height; y++)
        {
            if (x >= 0 && x < Thickness || x >= image2.width - Thickness && x < image2.width ||
                y >= 0 && y < Thickness || y >= image2.height - Thickness && y < image2.height)
            {
                image2.setPixel(x, y, 0, Red);
                image2.setPixel(x, y, 1, Green);
                image2.setPixel(x, y, 2, Blue);
            }
            else
            {
                image2.setPixel(x, y, 0, image.getPixel(x - Thickness, y - Thickness, 0));
                image2.setPixel(x, y, 1, image.getPixel(x - Thickness, y - Thickness, 1));
                image2.setPixel(x, y, 2, image.getPixel(x - Thickness, y - Thickness, 2));
            }
        }
    }
    return image2;
}
//=======================Filter8======================//
void EnterNewSize(int &NewHeight, int &NewWidth)
{
    cout << "Enter new height: ";
    cin >> NewHeight;
    while (NewHeight <= 0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter new height: ";
        cin >> NewHeight;
    }
    cout << "Enter new width: ";
    cin >> NewWidth;

    while (NewWidth <= 0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter new width: ";
        cin >> NewWidth;
    }
}

void Calculate_xRatio_yRatio(double &x, double &y, int &NewHeight, int &NewWidth, Image &image)
{
    x = double(image.width) / NewWidth;
    y = double(image.height) / NewHeight;
}
void ReSizeImage(int &NewHeight, int &NewWidth, double &x, double &y, Image &image, Image &image2)
{
    for (int i = 0; i < NewWidth; i++)
    {
        for (int j = 0; j < NewHeight; j++)
        {
            image2.setPixel(i, j, 0, image.getPixel(i * x, j * y, 0));
            image2.setPixel(i, j, 1, image.getPixel(i * x, j * y, 1));
            image2.setPixel(i, j, 2, image.getPixel(i * x, j * y, 2));
        }
    }
}

Image ResizeFilter(Image &image)
{
    int NewWidth, NewHeight;
    double x, y;

    EnterNewSize(NewHeight, NewWidth);
    Image image2(NewWidth, NewHeight);
    Calculate_xRatio_yRatio(x, y, NewHeight, NewWidth, image);
    ReSizeImage(NewHeight, NewWidth, x, y, image, image2);
    return image2;
}

/*===============Filter 12 Bluer ==================*/
void Blur(Image& image, Image& image2, int radius)
{
    int size = 2 * radius + 1;// Calculate the size of the kernel
    int totalPixels = size * size;// Calculate the total number of pixels in the kernel

    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;

            for (int k = x - radius; k <= x + radius; k++)
            {
                for (int l = y - radius; l <= y + radius; l++)
                {
                    int dk = (k + image.width) % image.width;
                    int dl = (l + image.height) % image.height;

                    sumR += image.getPixel(dk, dl, 0);
                    sumG += image.getPixel(dk, dl, 1);
                    sumB += image.getPixel(dk, dl, 2);
                }
            }

            image2.setPixel(x, y, 0, sumR / totalPixels);
            image2.setPixel(x, y, 1, sumG / totalPixels);
            image2.setPixel(x, y, 2, sumB / totalPixels);
        }
    }
}

void BlurImage(Image& image, Image& image2)
{
    int level;

    cout << "Choose Blur Level:" << endl;
    cout << "1 - Weak" << endl;
    cout << "2 - Medium" << endl;
    cout << "3 - Strong" << endl;

    cout << "Enter Level: ";
    cin >> level;

    while (level != 1 && level != 2 && level != 3)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid Level! Enter Level Again: ";
        cin >> level;
    }

    if (level == 1)
    {
        Blur(image, image2, 5);
    }
    else if (level == 2)
    {
        Blur(image, image2, 7);
    }
    else
    {
        Blur(image, image2, 12);
    }
}
/*================ Filter 16 Infrared ============*/
void Infrared(Image &image)
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int gray = (r + g + b) / 3;

            image.setPixel(x, y, 0, 255);
            image.setPixel(x, y, 1, gray);
            image.setPixel(x, y, 2, gray);
        }
    }
}

int main()
{
    return 0;
}

