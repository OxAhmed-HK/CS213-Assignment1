#include <iostream>
#include <algorithm>
#include <cmath>
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
// ==================== FILTER 3 ===================== //
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

// ==================== FILTER 9 ===================== //

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

// ==================== FILTER 13 ===================== //

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

// ==================== FILTER 17 ===================== //

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
        cout << "2. Flip\n";
        cout << "3. black_white\n";
        cout << "4. [Teammate Filter 2]\n";
        cout << "5. [Teammate Filter 3]\n";
        cout << "6. [Teammate Filter 4]\n";
        cout << "7. [Teammate Filter 5]\n";
        cout << "8. [Teammate Filter 6]\n";
        cout << "9. merge\n";
        cout << "10. Save Image\n";
        cout << "11. Load New Image\n";
        cout << "13. Wano_Sunlight\n";
        cout << "17. ImageSkewing\n";
        cout << "0. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Grayscale(image);
        }

        else if (choice == 2)
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

        else if (choice == 3)
        {
            black_white(image);
        }

        // ==================== SAVE ==================== //

        else if (choice == 10)
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
        //===============================merge ========================//

        else if (choice == 9)
        {
            string filename;
            cout << "Enter the second image filename: ";
            cin >> filename;
            Image image2(filename);
            image = merge(image, image2);
        }
        // ==================== LOAD NEW IMAGE ==================== //
        else if (choice == 11)
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
        // ==================== Wano_Sunlight ==================== //

        else if (choice == 13)
        {
            Wano_Sunlight(image);
        }

        // ==================== ImageSkewing ==================== //

        else if (choice == 17)
        {
            ImageSkewing(image);
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