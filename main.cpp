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

void invertColors(Image &image)
{
    for (int _x = 0; _x < image.width; _x++)
    {
        for (int _y = 0; _y < image.height; _y++)
        {
            image(_x, _y, 0) = 255 - image(_x, _y, 0);
            image(_x, _y, 1) = 255 - image(_x, _y, 1);
            image(_x, _y, 2) = 255 - image(_x, _y, 2);
        }
    }
}


// ==================== FILTER 3 ===================== //

void invert(Image & Image)
{
    for(int x=0; x<Image.width; x++)
    {
        for(int y=0; y<Image.height; y++) 
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


// ==================== FILTER 7 ===================== //

void Darken(Image & Image)
{
    for(int x=0; x<Image.width; x++)
    {
        for(int y=0; y<Image.height; y++) 
        {
            for(int c=0; c<3;c++)
            {
                // Darkening the image by 50% 
                int pixelvalue = Image.getPixel(x, y, c);
                pixelvalue = pixelvalue * 0.5; 
                Image.setPixel(x, y, c, pixelvalue);
                


            }
        }
    }
}
void Lighten(Image & Image)
{
    for(int x=0; x<Image.width; x++)
    {
        for(int y=0; y<Image.height; y++) 
        {
            for(int c=0; c<3;c++)
            {
                // Lightening the image by 50% 
                int pixelvalue = Image.getPixel(x, y, c);
                pixelvalue = pixelvalue +((255-pixelvalue)*0.5);
                Image.setPixel(x, y, c, pixelvalue);
            }
        }
    }
}
int main()
{


    return 0;
}