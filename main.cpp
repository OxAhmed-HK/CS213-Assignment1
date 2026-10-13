#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "Image_Class.h"
using namespace std;

// ==================== FILTER 1 : Grayscale ===================== //
void Grayscale(Image &image)
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            int gray = (r + g + b) / 3;

            image(x, y, 0) = gray;
            image(x, y, 1) = gray;
            image(x, y, 2) = gray;
        }
    }
}

// ==================== FILTER 2 : Black & White ===================== //
void black_white(Image &image)
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int average = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
            if (average < 128)
            {
                for (int i = 0; i < 3; i++)
                {
                    image(x, y, i) = 0;
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    image(x, y, i) = 255;
                }
            }
        }
    }
}

// ==================== FILTER 3 : Invert ===================== //

void invert(Image &Image)
{
    for (int x = 0; x < Image.width; x++)
    {
        for (int y = 0; y < Image.height; y++)
        {
            int red = Image.getPixel(x, y, 0);
            int green = Image.getPixel(x, y, 1);
            int blue = Image.getPixel(x, y, 2);

            Image.setPixel(x, y, 0, 255 - red);
            Image.setPixel(x, y, 1, 255 - green);
            Image.setPixel(x, y, 2, 255 - blue);
        }
    }
}

//=======================Filter4 : Frame======================//
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
    int FrameType;

    cout << "Choose Frame Type:\n";
    cout << "1. Simple Frame\n";
    cout << "2. Fancy Frame\n";
    cout << "Enter your choice: ";
    cin >> FrameType;

    while (FrameType != 1 && FrameType != 2)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid choice. Enter 1 for Simple or 2 for Decorated: ";
        cin >> FrameType;
    }

    Enter_New_Thickness(Thickness);

    Calculate_NewHeight_NewWidth(Thickness, NewHeight, NewWidth, image);

    Image image2(NewWidth, NewHeight);

    int Red1, Green1, Blue1;
    int Red2, Green2, Blue2;

    if (FrameType == 1)
    {
        Enter_Colors_Values(Red1, Green1, Blue1);
    }
    else
    {
        cout << "\nEnter the first color:\n";
        Enter_Colors_Values(Red1, Green1, Blue1);

        cout << "\nEnter the second color:\n";
        Enter_Colors_Values(Red2, Green2, Blue2);
    }

    for (int x = 0; x < image2.width; x++)
    {
        for (int y = 0; y < image2.height; y++)
        {
            if (x >= 0 && x < Thickness || x >= image2.width - Thickness && x < image2.width ||
                y >= 0 && y < Thickness || y >= image2.height - Thickness && y < image2.height)
            {
                if (FrameType == 1)
                {
                    image2.setPixel(x, y, 0, Red1);
                    image2.setPixel(x, y, 1, Green1);
                    image2.setPixel(x, y, 2, Blue1);
                }
                else
                {
                    if ((x + y) % 2 == 0)
                    {
                        image2.setPixel(x, y, 0, Red2);
                        image2.setPixel(x, y, 1, Green2);
                        image2.setPixel(x, y, 2, Blue2);
                    }
                    else
                    {
                        image2.setPixel(x, y, 0, Red1);
                        image2.setPixel(x, y, 1, Green1);
                        image2.setPixel(x, y, 2, Blue1);
                    }
                }
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

// ==================== FILTER 5 : Flip ===================== //

void Flip(Image &image, string direction)
{
    int w = image.width;
    int h = image.height;

    // Horizontal  OR  Vertical

    // Horizontal
    if (direction == "Horizontal")
    {
        for (int x = 0; x < w / 2; x++)

        {
            for (int y = 0; y < h; y++)
            {

                int oldValue = image(x, y, 0);
                image(x, y, 0) = image((w - 1) - x, y, 0);
                image((w - 1) - x, y, 0) = oldValue;

                oldValue = image(x, y, 1);
                image(x, y, 1) = image((w - 1) - x, y, 1);
                image((w - 1) - x, y, 1) = oldValue;

                oldValue = image(x, y, 2);
                image(x, y, 2) = image((w - 1) - x, y, 2);
                image((w - 1) - x, y, 2) = oldValue;
            }
        }
    }

    // Vertical
    else if (direction == "Vertical")
    {
        for (int x = 0; x < w; x++)

        {
            for (int y = 0; y < h / 2; y++)
            {
                int oldValue = image(x, y, 0);
                image(x, y, 0) = image(x, (h - 1) - y, 0);
                image(x, (h - 1) - y, 0) = oldValue;

                oldValue = image(x, y, 1);
                image(x, y, 1) = image(x, (h - 1) - y, 1);
                image(x, (h - 1) - y, 1) = oldValue;

                oldValue = image(x, y, 2);
                image(x, y, 2) = image(x, (h - 1) - y, 2);
                image(x, (h - 1) - y, 2) = oldValue;
            }
        }
    }
}

// ==================== FILTER 6 : Rotate ===================== //
void rotate_image(Image &image, int angle)
{
    if (angle != 90 && angle != 180 && angle != 270)
    {
        cout << "Invalid angle";
        return;
    }
    if (angle == 90)
    {
        Image rotated_image(image.height, image.width);
        for (int x = 0; x < image.width; x++)
        {
            for (int y = 0; y < image.height; y++)
            {
                for (int i = 0; i < 3; i++)
                {
                    rotated_image(image.height - 1 - y, x, i) = image(x, y, i);
                }
            }
        }
        image = rotated_image;
    }
    else if (angle == 180)
    {
        Image rotated_image(image.width, image.height);
        for (int x = 0; x < image.width; x++)
        {
            for (int y = 0; y < image.height; y++)
            {
                for (int i = 0; i < 3; i++)
                {
                    rotated_image(image.width - 1 - x, image.height - 1 - y, i) = image(x, y, i);
                }
            }
        }
        image = rotated_image;
    }
    else if (angle == 270)
    {
        Image rotated_image(image.height, image.width);
        for (int x = 0; x < image.width; x++)
        {
            for (int y = 0; y < image.height; y++)
            {
                for (int i = 0; i < 3; i++)
                {
                    rotated_image(y, image.width - 1 - x, i) = image(x, y, i);
                }
            }
        }
        image = rotated_image;
    }
}

// ==================== FILTER 7 : Darken / Lighten ===================== //

void Darken(Image &Image)
{
    for (int x = 0; x < Image.width; x++)
    {
        for (int y = 0; y < Image.height; y++)
        {
            for (int c = 0; c < 3; c++)
            {
                // Darkening the image by 50%
                int pixelvalue = Image.getPixel(x, y, c);
                pixelvalue = pixelvalue * 0.5;
                Image.setPixel(x, y, c, pixelvalue);
            }
        }
    }
}
void Lighten(Image &Image)
{
    for (int x = 0; x < Image.width; x++)
    {
        for (int y = 0; y < Image.height; y++)
        {
            for (int c = 0; c < 3; c++)
            {
                // Lightening the image by 50%
                int pixelvalue = Image.getPixel(x, y, c);
                pixelvalue = pixelvalue + ((255 - pixelvalue) * 0.5);
                Image.setPixel(x, y, c, pixelvalue);
            }
        }
    }
}

//=======================Filter8 : Resize======================//
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

// ==================== FILTER 9 : Merge ===================== //

Image merge(Image &image1, Image &image2)
{
    int newWidth = min(image1.width, image2.width);
    int newHeight = min(image1.height, image2.height);
    Image result(newWidth, newHeight);

    for (int x = 0; x < newWidth; x++)
    {
        for (int y = 0; y < newHeight; y++)
        {
            int r1 = image1(x, y, 0);
            int g1 = image1(x, y, 1);
            int b1 = image1(x, y, 2);
            //===============//
            int r2 = image2(x, y, 0);
            int g2 = image2(x, y, 1);
            int b2 = image2(x, y, 2);
            // Calculate the average colors
            int new_r = (r1 + r2) / 2;
            int new_g = (g1 + g2) / 2;
            int new_b = (b1 + b2) / 2;
            // Set the output pixel
            result(x, y, 0) = new_r;
            result(x, y, 1) = new_g;
            result(x, y, 2) = new_b;
        }
    }
    return result;
}

// ==================== FILTER 10 : Edge Detection ===================== //
void edge_detection(Image &image)
{
    Image gray_image(image.width, image.height);
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int average = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
            for (int i = 0; i < 3; i++)
            {
                gray_image(x, y, i) = average;
            }
        }
    }

    Image final_image(image.width, image.height);
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int difference = 0;
            int max_difference = 0;
            if (x < image.width - 1)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x + 1, y, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (x > 0)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x - 1, y, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (y < image.height - 1)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x, y + 1, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (y > 0)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x, y - 1, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (x > 0 && y > 0)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x - 1, y - 1, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (x < image.width - 1 && y > 0)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x + 1, y - 1, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (x > 0 && y < image.height - 1)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x - 1, y + 1, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (x < image.width - 1 && y < image.height - 1)
            {
                difference = abs(gray_image(x, y, 0) - gray_image(x + 1, y + 1, 0));
            }
            if (difference > max_difference)
            {
                max_difference = difference;
            }
            if (max_difference > 18)
            {
                for (int i = 0; i < 3; i++)
                {
                    final_image(x, y, i) = 0;
                }
            }
            else
            {
                for (int i = 0; i < 3; i++)
                {
                    final_image(x, y, i) = 255;
                }
            }
        }
    }
    image = final_image;
}

// ==================== FILTER 11 : Crop ===================== //

void crop(Image &image)
{
    int x, y, cropwidth, cropheight;
    cout << "Image Width : " << image.width << endl;
    cout << "Image Height : " << image.height << endl;
    cout << "Enter x (starting point from the left): ";
    cin >> x;

    cout << "Enter y (starting point from the top): ";
    cin >> y;

    cout << "Enter the width of the crop: ";
    cin >> cropwidth;

    cout << "Enter the height of the crop: ";
    cin >> cropheight;

    if (x >= 0 && y >= 0 && cropwidth > 0 && cropheight > 0 && x + cropwidth <= image.width && y + cropheight <= image.height)
    {
        Image cropped_image(cropwidth, cropheight);
        for (int i = 0; i < cropwidth; i++)
        {
            for (int j = 0; j < cropheight; j++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int pixelvalue = image.getPixel(x + i, y + j, c);
                    cropped_image.setPixel(i, j, c, pixelvalue);
                }
            }
        }
        image = cropped_image;
    }
    else
    {
        cout << "Invalid crop dimensions" << endl;
    }
}

/*===============Filter 12 : Blur ==================*/
void Blur(Image &image, Image &image2, int radius)
{
    int size = 2 * radius + 1;     // Calculate the size of the kernel
    int totalPixels = size * size; // Calculate the total number of pixels in the kernel

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

void BlurImage(Image &image, Image &image2)
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

// ==================== FILTER 13 : Wano Sunlight ===================== //

void Wano_Sunlight(Image &image)
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            int new_r = r + 50;
            int new_g = g + 50;
            int new_b = b + 50;

            if (new_r > 255)
            {
                new_r = 255;
            }
            if (new_g > 255)
            {
                new_g = 255;
            }
            if (new_b > 255)
            {
                new_b = 255;
            }

            image(x, y, 0) = new_r;
            image(x, y, 1) = new_g;
            image(x, y, 2) = new_b;
        }
    }
}

// ==================== FILTER 14 : Old TV Effect ===================== //
void old_TV_effect(Image &image)
{
    for (int y = 1; y < image.height; y += 2)
    {
        for (int x = 0; x < image.width; x++)
        {
            for (int i = 0; i < 3; i++)
            {
                image(x, y, i) = image(x, y, i) / 2;
            }
        }
    }
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            for (int i = 0; i < 3; i++)
            {
                int noise = rand() % 101 - 50;
                int new_value = image(x, y, i) + noise;
                if (new_value < 0)
                {
                    new_value = 0;
                }
                if (new_value > 255)
                {
                    new_value = 255;
                }
                image(x, y, i) = new_value;
            }
        }
    }
}

// ==================== FILTER 15 : Purple Luffy ===================== //

void PurpleLuffy(Image &image)
{
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int old_red = image.getPixel(x, y, 0);
            int old_green = image.getPixel(x, y, 1);
            int old_blue = image.getPixel(x, y, 2);

            int new_red = (0.8 * old_red) + (0.2 * 180);
            int new_green = (0.8 * old_green) + (0.00001 * 70);
            int new_blue = (0.8 * old_blue) + (0.2 * 200);

            image.setPixel(x, y, 0, new_red);
            image.setPixel(x, y, 1, new_green);
            image.setPixel(x, y, 2, new_blue);
        }
    }
}

/*================ Filter 16 : Infrared ============*/
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

// ==================== FILTER 17 : Skewing ===================== //

void ImageSkewing(Image &image)
{
    double angle;
    cout << "Enter the skew angle in degrees : ";
    cin >> angle;
    double radian = angle * ((3.14) / 180.0);
    double skewFactor = tan(radian);

    int extraWidth = ceil(abs(image.height * skewFactor));
    int newWidth = image.width + extraWidth;
    int newHeight = image.height;
    Image result(newWidth, newHeight);

    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int shift = y * skewFactor;
            int newx = x + shift;
            int newy = y;

            // بنتأكد إن البكسل مش هيخرج خارج الصورة الجديدة قبل ما نكتب فيه
            if (newx >= 0 && newx < newWidth && newy >= 0 && newy < newHeight)
            {
                result(newx, newy, 0) = image(x, y, 0);
                result(newx, newy, 1) = image(x, y, 1);
                result(newx, newy, 2) = image(x, y, 2);
            }
        }
    }
    image = result;
}

// filter 18//
void oil_painting_effect(Image &image)
{
    Image input_image = image;
    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int start_x = max(x - 2, 0);
            int end_x = min(x + 2, input_image.width - 1);
            int start_y = max(y - 2, 0);
            int end_y = min(y + 2, input_image.height - 1);
            int count[20] = {};
            int red_sum[20] = {};
            int green_sum[20] = {};
            int blue_sum[20] = {};

            for (int nx = start_x; nx <= end_x; nx++)
            {
                for (int ny = start_y; ny <= end_y; ny++)
                {
                    int i_sum = 0;

                    for (int i = 0; i < 3; i++)
                    {
                        i_sum += input_image(nx, ny, i);
                    }

                    int intensity = i_sum / 3;
                    int level = intensity * 20 / 256;
                    count[level]++;
                    red_sum[level] += input_image(nx, ny, 0);
                    green_sum[level] += input_image(nx, ny, 1);
                    blue_sum[level] += input_image(nx, ny, 2);
                }
            }
            int max_count = 0;
            int dominant_level = 0;

            for (int i = 0; i < 20; i++)
            {
                if (count[i] > max_count)
                {
                    max_count = count[i];
                    dominant_level = i;
                }
            }

            image(x, y, 0) =
                red_sum[dominant_level] / count[dominant_level];

            image(x, y, 1) =
                green_sum[dominant_level] / count[dominant_level];

            image(x, y, 2) =
                blue_sum[dominant_level] / count[dominant_level];
        }
    }
}

//=======================Menu======================//
bool checkExtension(string filename)
{
    int n = filename.length();
    if (n < 4)
        return false;

    string ext4 = filename.substr(n - 4);
    string ext5 = (n >= 5) ? filename.substr(n - 5) : "";

    return ext4 == ".jpg" || ext4 == ".png" || ext4 == ".bmp" || ext5 == ".jpeg" ||
           ext4 == ".JPG" || ext4 == ".PNG" || ext4 == ".BMP" || ext5 == ".JPEG";
}

bool fileExists(string filename)
{
    ifstream file(filename);
    return file.good();
}

bool saveWithCheck(Image &image, string &currentFile)
{
    int option;
    cout << "\nSave Options:\n";
    cout << "1. Save on the same file (" << currentFile << ")\n";
    cout << "2. Save as a new file\n";
    cout << "Enter your choice: ";
    cin >> option;

    while (option != 1 && option != 2)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Invalid choice! Enter 1 or 2: ";
        cin >> option;
    }

    string saveName;

    if (option == 1)
    {
        saveName = currentFile;
    }
    else
    {
        cout << "Enter new filename (with extension): ";
        cin >> saveName;

        if (!checkExtension(saveName))
        {
            cout << "Invalid file extension.\n";
            return false;
        }
    }

    image.saveImage(saveName);
    currentFile = saveName;
    cout << "\n>> Image saved as " << saveName << "\n";
    return true;
}

bool loadNewImage(Image &image, bool imageLoaded, bool &unsaved, string &currentFile)
{
    if (imageLoaded)
    {
        char saveCurrent;
        cout << "Do you want to save the current image before loading a new one? (y/n): ";
        cin >> saveCurrent;

        if (saveCurrent == 'y' || saveCurrent == 'Y')
        {
            saveWithCheck(image, currentFile);
        }
    }

    string newFilename;
    cout << "Enter image filename: ";
    cin >> newFilename;

    if (!checkExtension(newFilename))
    {
        cout << "Invalid file extension.\n";
        return imageLoaded;
    }
    if (!fileExists(newFilename))
    {
        cout << "File does not exist.\n";
        return imageLoaded;
    }

    image = Image(newFilename);
    currentFile = newFilename;
    unsaved = false;
    cout << "\n>> Image loaded: " << newFilename << "\n";
    return true;
}

// helper for the extra questions asked by Flip / Rotate / Darken-Lighten
int askChoice(string message)
{
    int value;
    cout << message;
    cin >> value;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << message;
        cin >> value;
    }
    return value;
}

void menu(Image &image)
{
    int choice;
    bool imageLoaded = false;
    bool unsaved = false;
    string currentFile;

    do
    {
        cout << "\n========== IMAGE PROCESSING MENU ==========\n";
        if (!imageLoaded)
        {
            cout << "No image loaded yet.\n";
        }
        else
        {
            cout << "Current image: " << image.width << " x " << image.height;
            cout << (unsaved ? "  (unsaved changes)" : "  (saved)") << "\n";
            cout << "1  ====>>> Grayscale\n";
            cout << "2  ====>>> Black & White\n";
            cout << "3  ====>>> Invert\n";
            cout << "4  ====>>> Frame\n";
            cout << "5  ====>>> Flip\n";
            cout << "6  ====>>> Rotate\n";
            cout << "7  ====>>> Darken / Lighten\n";
            cout << "8  ====>>> Resize\n";
            cout << "9  ====>>> Merge\n";
            cout << "10 ====>>> Edge Detection\n";
            cout << "11 ====>>> Crop\n";
            cout << "12 ====>>> Blur\n";
            cout << "13 ====>>> Wano Sunlight\n";
            cout << "14 ====>>> Old TV Effect\n";
            cout << "15 ====>>> Purple Luffy\n";
            cout << "16 ====>>> Infrared\n";
            cout << "17 ====>>> Skewing\n";
            cout << "18 ====>>> Oil Painting\n";
            cout << "20 ====>>> Save Image\n";
        }
        cout << "19 ====>>> Load Image\n";
        cout << "0  ====>>> Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        if (choice == 19)
        {
            imageLoaded = loadNewImage(image, imageLoaded, unsaved, currentFile);
        }
        else if (choice == 0)
        {
            if (imageLoaded)
            {
                char saveCurrent;
                cout << "Do you want to save the current image before exiting? (y/n): ";
                cin >> saveCurrent;

                if (saveCurrent == 'y' || saveCurrent == 'Y')
                {
                    saveWithCheck(image, currentFile);
                }
            }
            cout << "Exiting...\n";
        }
        else if (!imageLoaded && ((choice >= 1 && choice <= 18) || choice == 20))
        {
            cout << "Please load an image first (option 19).\n";
        }
        else if (choice == 1)
        {
            Grayscale(image);
            unsaved = true;
            cout << "\n>> Grayscale filter applied.\n";
        }
        else if (choice == 2)
        {
            black_white(image);
            unsaved = true;
            cout << "\n>> Black & White filter applied.\n";
        }
        else if (choice == 3)
        {
            invert(image);
            unsaved = true;
            cout << "\n>> Invert filter applied.\n";
        }
        else if (choice == 4)
        {
            image = FrameFilter(image);
            unsaved = true;
            cout << "\n>> Frame filter applied.\n";
        }
        else if (choice == 5)
        {
            int d;
            cout << "1. Horizontal\n2. Vertical\n";
            d = askChoice("Enter your choice: ");
            while (d != 1 && d != 2)
            {
                d = askChoice("Invalid choice! Enter 1 or 2: ");
            }
            if (d == 1)
                Flip(image, "Horizontal");
            else
                Flip(image, "Vertical");
            unsaved = true;
            cout << "\n>> Flip filter applied.\n";
        }
        else if (choice == 6)
        {
            int angle = askChoice("Enter rotation angle (90 / 180 / 270): ");
            while (angle != 90 && angle != 180 && angle != 270)
            {
                angle = askChoice("Invalid angle! Enter 90, 180 or 270: ");
            }
            rotate_image(image, angle);
            unsaved = true;
            cout << "\n>> Rotate filter applied.\n";
        }
        else if (choice == 7)
        {
            int d;
            cout << "1. Darken\n2. Lighten\n";
            d = askChoice("Enter your choice: ");
            while (d != 1 && d != 2)
            {
                d = askChoice("Invalid choice! Enter 1 or 2: ");
            }
            if (d == 1)
                Darken(image);
            else
                Lighten(image);
            unsaved = true;
            cout << "\n>> Darken / Lighten filter applied.\n";
        }
        else if (choice == 8)
        {
            image = ResizeFilter(image);
            unsaved = true;
            cout << "\n>> Resize filter applied.\n";
        }
        else if (choice == 9)
        {
            string secondName;
            cout << "Enter the second image filename: ";
            cin >> secondName;
            if (!checkExtension(secondName))
            {
                cout << "Invalid file extension.\n";
            }
            else if (!fileExists(secondName))
            {
                cout << "File does not exist.\n";
            }
            else
            {
                Image second(secondName);
                image = merge(image, second);
                unsaved = true;
                cout << "\n>> Merge filter applied.\n";
            }
        }
        else if (choice == 10)
        {
            edge_detection(image);
            unsaved = true;
            cout << "\n>> Edge Detection filter applied.\n";
        }
        else if (choice == 11)
        {
            crop(image);
            unsaved = true;
            cout << "\n>> Crop filter applied.\n";
        }
        else if (choice == 12)
        {
            Image blurred(image.width, image.height);
            BlurImage(image, blurred);
            image = blurred;
            unsaved = true;
            cout << "\n>> Blur filter applied.\n";
        }
        else if (choice == 13)
        {
            Wano_Sunlight(image);
            unsaved = true;
            cout << "\n>> Wano Sunlight filter applied.\n";
        }
        else if (choice == 14)
        {
            old_TV_effect(image);
            unsaved = true;
            cout << "\n>> Old TV Effect filter applied.\n";
        }
        else if (choice == 15)
        {
            PurpleLuffy(image);
            unsaved = true;
            cout << "\n>> Purple Luffy filter applied.\n";
        }
        else if (choice == 16)
        {
            Infrared(image);
            unsaved = true;
            cout << "\n>> Infrared filter applied.\n";
        }
        else if (choice == 17)
        {
            ImageSkewing(image);
            unsaved = true;
            cout << "\n>> Skewing filter applied.\n";
        }
        else if (choice == 18)
        {
            oil_painting_effect(image);
            unsaved = true;
            cout << "\n>> Oil Painting filter applied.\n";
        }
        else if (choice == 20)
        {
            if (saveWithCheck(image, currentFile))
            {
                unsaved = false;
            }
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

int main()
{
    Image image;

    menu(image);

    return 0;
}