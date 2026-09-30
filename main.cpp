#include <iostream>
#include <string>
#include <fstream>
#include "Image_Class.h"

using namespace std;

// ==================== FILTER 1 ===================== //
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

// ==================== FILTER 2 ===================== //

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

// ==================== FILTER 3 ===================== //

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
    int FrameType;

    cout << "Choose Frame Type:\n";
    cout << "1. Simple Frame\n";
    cout << "2. Fancy Frame\n";
    cout << "Enter your choice: ";
    cin >> FrameType;

    while (FrameType != 1 && FrameType != 2)
    {
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

// ==================== FILTER 5 ===================== //
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

// ==================== FILTER 6 ===================== //
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

// ==================== FILTER 7 ===================== //
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

//=======================Filter8======================//
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

bool checkExtension(string filename)
{
    if ((filename.length() >= 4 &&
         filename[filename.length() - 4] == '.' &&
         filename[filename.length() - 3] == 'j' &&
         filename[filename.length() - 2] == 'p' &&
         filename[filename.length() - 1] == 'g') ||
        (filename.length() >= 5 &&
         filename[filename.length() - 5] == '.' &&
         filename[filename.length() - 4] == 'j' &&
         filename[filename.length() - 3] == 'p' &&
         filename[filename.length() - 2] == 'e' &&
         filename[filename.length() - 1] == 'g') ||
        (filename.length() >= 4 &&
         filename[filename.length() - 4] == '.' &&
         filename[filename.length() - 3] == 'p' &&
         filename[filename.length() - 2] == 'n' &&
         filename[filename.length() - 1] == 'g') ||
        (filename.length() >= 4 &&
         filename[filename.length() - 4] == '.' &&
         filename[filename.length() - 3] == 'b' &&
         filename[filename.length() - 2] == 'm' &&
         filename[filename.length() - 1] == 'p') ||
        (filename.length() >= 4 &&
         filename[filename.length() - 4] == '.' &&
         filename[filename.length() - 3] == 'J' &&
         filename[filename.length() - 2] == 'P' &&
         filename[filename.length() - 1] == 'G') ||
        (filename.length() >= 5 &&
         filename[filename.length() - 5] == '.' &&
         filename[filename.length() - 4] == 'J' &&
         filename[filename.length() - 3] == 'P' &&
         filename[filename.length() - 2] == 'E' &&
         filename[filename.length() - 1] == 'G') ||
        (filename.length() >= 4 &&
         filename[filename.length() - 4] == '.' &&
         filename[filename.length() - 3] == 'P' &&
         filename[filename.length() - 2] == 'N' &&
         filename[filename.length() - 1] == 'G') ||
        (filename.length() >= 4 &&
         filename[filename.length() - 4] == '.' &&
         filename[filename.length() - 3] == 'B' &&
         filename[filename.length() - 2] == 'M' &&
         filename[filename.length() - 1] == 'P'))
    {
        return true;
    }

    return false;
}

bool fileExists(string filename)
{
    ifstream file(filename);
    return file.good();
}

void menu(Image &image)
{
    int choice;

    do
    {
        cout << "\n========== IMAGE PROCESSING MENU ==========\n";

        cout << "1. Grayscale\n";
        cout << "2. Black & White\n";
        cout << "3. Invert\n";
        cout << "4. Add Frame\n";
        cout << "5. Flip\n";
        cout << "6. Rotate\n";
        cout << "7. Darken / Lighten\n";
        cout << "8. Resize\n";
        cout << "9. Save Image\n";
        cout << "10. Load New Image\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        // ==================== GRAYSCALE ==================== //

        if (choice == 1)
        {
            Grayscale(image);
        }

        // ==================== BLACK & WHITE ==================== //

        else if (choice == 2)
        {
            black_white(image);
        }

        // ==================== INVERT ==================== //

        else if (choice == 3)
        {
            invert(image);
        }

        // ==================== FRAME ==================== //

        else if (choice == 4)
        {
            image = FrameFilter(image);
        }

        // ==================== FLIP ==================== //

        else if (choice == 5)
        {
            int direction;

            cout << "\nChoose Flip Direction:\n";
            cout << "1. Horizontal\n";
            cout << "2. Vertical\n";
            cout << "Enter your choice: ";
            cin >> direction;

            if (direction == 1)
            {
                Flip(image, "Horizontal");
            }
            else if (direction == 2)
            {
                Flip(image, "Vertical");
            }
            else
            {
                cout << "Invalid direction.\n";
            }
        }

        // ==================== ROTATE ==================== //

        else if (choice == 6)
        {
            int angle;

            cout << "\nChoose Rotation Angle:\n";
            cout << "1. 90 degrees\n";
            cout << "2. 180 degrees\n";
            cout << "3. 270 degrees\n";
            cout << "Enter your choice: ";
            cin >> angle;

            if (angle == 1)
            {
                rotate_image(image, 90);
            }
            else if (angle == 2)
            {
                rotate_image(image, 180);
            }
            else if (angle == 3)
            {
                rotate_image(image, 270);
            }
            else
            {
                cout << "Invalid angle.\n";
            }
        }

        // ==================== DARKEN / LIGHTEN ==================== //

        else if (choice == 7)
        {
            int option;

            cout << "\nChoose an option:\n";
            cout << "1. Darken\n";
            cout << "2. Lighten\n";
            cout << "Enter your choice: ";
            cin >> option;

            if (option == 1)
            {
                Darken(image);
            }
            else if (option == 2)
            {
                Lighten(image);
            }
            else
            {
                cout << "Invalid choice.\n";
            }
        }

        // ==================== RESIZE ==================== //

        else if (choice == 8)
        {
            image = ResizeFilter(image);
        }

        // ==================== SAVE ==================== //

        else if (choice == 9)
        {
            string saveName;

            cout << "Enter filename to save: ";
            cin >> saveName;

            if (!checkExtension(saveName))
            {
                cout << "Invalid file extension.\n";
            }
            else
            {
                image.saveImage(saveName);
                cout << "Image saved successfully.\n";
            }
        }

        // ==================== LOAD NEW IMAGE ==================== //

        else if (choice == 10)
        {
            char saveCurrent;

            cout << "Do you want to save the current image before loading a new one? (y/n): ";
            cin >> saveCurrent;

            if (saveCurrent == 'y' || saveCurrent == 'Y')
            {
                string saveName;

                cout << "Enter filename to save: ";
                cin >> saveName;

                if (!checkExtension(saveName))
                {
                    cout << "Invalid file extension.\n";
                    continue;
                }

                image.saveImage(saveName);
                cout << "Current image saved successfully.\n";
            }

            string newFilename;

            cout << "Enter new image filename: ";
            cin >> newFilename;

            if (!checkExtension(newFilename))
            {
                cout << "Invalid file extension.\n";
                continue;
            }

            if (!fileExists(newFilename))
            {
                cout << "File does not exist.\n";
                continue;
            }

            image = Image(newFilename);

            cout << "New image loaded successfully.\n";
        }

        // ==================== EXIT ==================== //

        else if (choice == 0)
        {
            char saveCurrent;

            cout << "Do you want to save the current image before exiting? (y/n): ";
            cin >> saveCurrent;

            if (saveCurrent == 'y' || saveCurrent == 'Y')
            {
                string saveName;

                cout << "Enter filename to save: ";
                cin >> saveName;

                if (!checkExtension(saveName))
                {
                    cout << "Invalid file extension.\n";
                }
                else
                {
                    image.saveImage(saveName);
                    cout << "Image saved successfully.\n";
                }
            }

            cout << "Exiting...\n";
        }

        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

int main()
{
    string filename;

    cout << "Enter image filename: ";
    cin >> filename;

    Image image(filename);

    menu(image);

    return 0;
}
