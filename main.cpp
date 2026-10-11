#include <iostream>
#include "Image_Class.h"
#include <cmath>
#include <cstdlib>
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

//filter 10//
void edge_detection(Image& image)
{
	Image gray_image(image.width, image.height);
	for (int x = 0; x < image.width; x++)
	{
		for (int y = 0; y < image.height; y++)
		{
			int average = ( image(x, y, 0) + image(x, y, 1) + image(x, y, 2) ) / 3;
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
			int max_difference= 0;
			if (x<image.width-1)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x+1, y, 0)) ;
			}
			if (difference > max_difference)
			{
				max_difference = difference;
			}
			if (x>0)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x-1, y, 0)) ;
			}
			if (difference > max_difference)
			{
				max_difference = difference;
			}	
			if (y<image.height-1)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x, y+1, 0)) ;
			}	
			if (difference > max_difference)
			{
				max_difference = difference;
			}
			if (y>0)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x, y-1, 0)) ;
			}
			if (difference > max_difference)
			{
				max_difference = difference;
			}
			if (x>0 && y>0)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x-1, y-1, 0)) ;
			}
			if (difference > max_difference)
			{
				max_difference = difference;
			}	
			if (x<image.width-1 && y>0)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x+1, y-1, 0)) ;
			}	
			if (difference > max_difference)
			{
				max_difference = difference;
			}
			if (x>0 && y<image.height-1)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x-1, y+1, 0)) ;
			}
			if (difference > max_difference)
			{
				max_difference = difference;
			}
			if (x<image.width-1 && y<image.height-1)
			{
				difference = abs(gray_image(x, y, 0) - gray_image(x+1, y+1, 0)) ;
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
			}else
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

//filter 14//
void old_TV_effect(Image& image)
{
	for(int y=1; y<image.height;y+=2)
	{
		for (int x=0; x<image.width;x++)
		{
			for (int i = 0; i < 3; i++)
			{
				image(x, y, i)= image(x, y, i)/2;
			}
		}
	}
	for(int y=0; y<image.height;y++)
	{
		for (int x=0; x<image.width;x++)
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

int main()
{

 
}

