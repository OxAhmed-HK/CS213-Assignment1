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
        cout << "9. [Teammate Filter 7]\n";
        cout << "10. Save Image\n";
        cout << "11. Load New Image\n";
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