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
int main()
{

	
}