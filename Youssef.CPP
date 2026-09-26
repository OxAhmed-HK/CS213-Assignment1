#include <iostream>
#include <string>

#include "Image_Class.h"

using namespace std;

// ==========================================
// Get Current Image Filename
// ==========================================
string filename_CurrenImage(string &filename)
{
    cout << "Enter image filename: ";
    cin >> filename;

    return filename;
}

// ==========================================
// Enter New Image Size
// ==========================================
void EnterNewSize(int &NewHeight, int &NewWidth)
{
    cout << "Enter new height: ";
    cin >> NewHeight;
    while (NewHeight <= 0)
    {
        cout << "Enter new height: ";
        cin >> NewHeight;
    }
    cout << "Enter new width: ";
    cin >> NewWidth;
    while (NewWidth <= 0)
    {
        cout << "Enter new width: ";
        cin >> NewWidth;
    }
}

// ==========================================
// Get Original Image Dimensions
// ==========================================
void Calculate_OldWidth_Oldheight(int &OldWidth, int &OldHeight, Image &image)
{
    OldHeight = image.height;
    OldWidth = image.width;
}

// ==========================================
// Calculate Resize Ratios
// ==========================================
void Calculate_xRatio_yRatio(double &x, double &y, int &NewHeight, int &NewWidth, int &OldHeight, int &OldWidth)
{
    x = double(OldWidth) / NewWidth;
    y = double(OldHeight) / NewHeight;
}

// ==========================================
// Resize Image
// ==========================================
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

// ==========================================
// Get New Image Filename
// ==========================================
string NewNameforImage(string &NewName)
{
    cout << "Enter filename for resized image: ";
    cin >> NewName;

    return NewName;
}

// ==========================================
// Resize Filter
// ==========================================
void ResizeFilter(Image &image)
{
    int NewWidth, NewHeight;
    int OldHeight, OldWidth;
    double x, y;
    string NewName;

    EnterNewSize(NewHeight, NewWidth);

    Image image2(NewWidth, NewHeight);

    Calculate_OldWidth_Oldheight(OldWidth, OldHeight, image);

    Calculate_xRatio_yRatio(x, y, NewHeight, NewWidth, OldHeight, OldWidth);

    ReSizeImage(NewHeight, NewWidth, x, y, image, image2);

    NewNameforImage(NewName);

    image2.saveImage(NewName);
}

// ==========================================
// Enter Frame Color Values
// ==========================================
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

// ==========================================
// Enter Frame Thickness
// ==========================================
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

// ==========================================
// Calculate New Frame Dimensions
// ==========================================
void Calculate_NewHeight_NewWidth(int &Thickness, int &NewHeight, int &NewWidth, Image &image)
{
    NewWidth = (image.width) + (2 * Thickness);
    NewHeight = (image.height) + (2 * Thickness);
}

// ==========================================
// Frame Filter
// ==========================================
void FrameFilter(Image &image)
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

    string outputFilename;

    cout << "Enter filename for framed image: ";
    cin >> outputFilename;

    image2.saveImage(outputFilename);
}

// ==========================================
// Main Menu
// ==========================================
void Menu(Image &image)
{
    cout << "\n";
    cout << "====================================\n";
    cout << "          IMAGE FILTER MENU         \n";
    cout << "====================================\n";
    cout << "1. Resize Image\n";
    cout << "2. Frame Image\n";
    cout << "====================================\n";

    int NumFilter;

    cout << "Enter the number of the filter: ";
    cin >> NumFilter;

    if (NumFilter == 1)
    {
        ResizeFilter(image);
    }
    else if (NumFilter == 2)
    {
        FrameFilter(image);
    }
}

// ==========================================
// Main
// ==========================================
int main()
{
    string filename;

    filename_CurrenImage(filename);

    Image image(filename);

    Menu(image);
}