#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

//=======================Filter4======================//
void Enter_Colors_Values(int &Red, int &Green, int &Blue)
{
    cout << "Enter value of Red from 0 to 255 : ";
    cin >> Red;
    while (Red < 0 || Red > 255)
    {
        cout << "Enter value of Red from 0 to 255 : ";
        cin >> Red;
    }
    cout << "\nEnter value of Green from 0 to 255 : ";
    cin >> Green;
    while (Green < 0 || Green > 255)
    {
        cout << "\nEnter value of Green from 0 to 255 : ";
        cin >> Green;
    }

    cout << "\nEnter value of Blue from 0 to 255 : ";
    cin >> Blue;
    while (Blue < 0 || Blue > 255)
    {
        cout << "\nEnter value of Blue from 0 to 255 : ";
        cin >> Blue;
    }
}

int Enter_New_Thickness(int &Thickness)
{
    cout << "Enter the thickness of Frame : ";
    cin >> Thickness;
    while (Thickness <= 0 || Thickness > 500)
    {
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

int main()
{
    return 0;
}
