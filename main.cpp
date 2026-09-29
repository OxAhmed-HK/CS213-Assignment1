#include <iostream>
#include "Image_Class.h"
using namespace std;
//filter 2//
void black_white(Image& image)
{
	for (int x = 0; x < image.width; x++)
	{
		for (int y = 0; y < image.height; y++)
		{
			int average = ( image(x, y, 0) + image(x, y, 1) + image(x, y, 2) ) / 3;
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

//filter 6//
void rotate_image(Image& image, int angle)
{
	if (angle != 90 && angle != 180 && angle != 270)
	{
		cout << "Invalid angle" ;	
		return;
	}
	if (angle==90)
	{	
		Image rotated_image(image.height, image.width);	
				for (int x = 0; x < image.width; x++)
		{
			for (int y = 0; y < image.height; y++)
			{
				for (int i = 0; i < 3; i++)
				{
					rotated_image(image.height-1-y, x, i) = image(x, y, i);
				}
			}
		}
		image = rotated_image;
	}	
	else if (angle==180)
	{
		Image rotated_image(image.width, image.height);	
		for (int x = 0; x < image.width; x++)
		{
			for (int y = 0; y < image.height; y++)
			{
				for (int i = 0; i < 3; i++)
				{
					rotated_image(image.width-1-x, image.height-1-y, i) = image(x, y, i);
				}
			}
		}
		image = rotated_image;
	}	
	else if (angle==270)
	{
		Image rotated_image(image.height, image.width);	
		for (int x = 0; x < image.width; x++)
		{
			for (int y = 0; y < image.height; y++)
			{
				for (int i = 0; i < 3; i++)
				{
					rotated_image(y, image.width-1-x, i) = image(x, y, i);
				}
			}
		}
		image = rotated_image;
	}
		
}

int main()
{
	
}  