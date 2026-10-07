#include <iostream>
#include "Image_Class.h"

using namespace std;




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
 
// ==================== FILTER 11 ===================== //

void crop(Image & image)
{
    int x,y,cropwidth,cropheight;
    cout<<"Image Width : "<<image.width<<endl;
    cout<<"Image Height : "<<image.height<<endl;
    cout<<"Enter x (starting point from the left): ";
    cin>>x;

    cout<<"Enter y (starting point from the top): ";
    cin>>y;

    cout<<"Enter the width of the crop: ";
    cin>>cropwidth;

    cout<<"Enter the height of the crop: ";
    cin>>cropheight;

    if (x>=0 && y>=0 && cropwidth>0 && cropheight>0 && x + cropwidth<=image.width && y + cropheight<=image.height)
    {
      Image cropped_image (cropwidth , cropheight);
        for (int i=0 ; i<cropwidth ; i++)
        {
            for (int j=0 ; j<cropheight ; j++)
            {
                for (int c=0 ; c<3 ; c++)
                {
                    int pixelvalue = image.getPixel(x+i , y+j ,c);
                    cropped_image.setPixel(i , j , c , pixelvalue);
                }
            }
        }
        image = cropped_image;
    }
    else 
    {
        cout<<"Invalid crop dimensions" <<endl;
    }
}

// ==================== FILTER 15 ===================== //

void PurpleLuffy( Image & image)
{
    for (int x=0 ; x<image.width ; x++)
    {
        for (int y=0 ; y<image.height ; y++)
        {
            int old_red = image.getPixel(x,y,0);
            int old_green = image.getPixel(x,y,1);
            int old_blue = image.getPixel(x,y,2);

            int new_red = (0.8 * old_red) +( 0.2*180);
            int new_green =(0.8 * old_green) +( 0.00001*70);
            int new_blue = (0.8 * old_blue) +( 0.2*200);

            image.setPixel(x,y,0,new_red);
            image.setPixel(x,y,1,new_green);
            image.setPixel(x,y,2,new_blue);

        }
    }
}


int main()
{
    
    return 0;
}