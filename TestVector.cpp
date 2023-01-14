#include <iostream>
#include <FreeImage.h>
#undef M_PI

float M_PI = 3.14159265358979323846;

FIBITMAP* BMPBuff;

float Clamp(float Min, float Max, float Num)
{
    if (Num < Min)
        return Min;
    else if (Num > Max)
        return Max;
    else
        return Num;
}

class Vector2D
{
public:
    float X;
    float Y;
    float R;
    float F;
    Vector2D(float PosX, float PosY, float Rot, float Force)
    {
        X = PosX;
        Y = PosY;
        R = Clamp(0, 360, Rot);
        F = Force;
    }
};

void drawLineConsole(int x1, int y1, int x2, int y2) {
    int x, y;

    int dx = x2 - x1;
    int dy = y2 - y1;

    bool steep = (abs(dy) > abs(dx));
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int error = 0;
    int derror = abs(dy) * 2;

    y = y1;

    for (x = x1; x <= x2; x++) {
        if (steep) {
            std::cout << "\033[" << y << ";" << x << "H";
        }
        else {
            std::cout << "\033[" << x << ";" << y << "H";
        }
        

        // Printing
        //::cout << "\033[" << y << ";" << x << "H";
        //std::cout << "\033[2K";
        putchar('#');

        error += derror;

        if (error >= dx) {
            y += (y2 > y1 ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void drawLineBMP(int x1, int y1, int x2, int y2)
{
    RGBQUAD color;
    color.rgbRed = 0;
    color.rgbGreen = 0;
    color.rgbBlue = 0;

    FIBITMAP* BMP;
    
    BMP = BMPBuff;
    

    int x, y;

    int dx = x2 - x1;
    int dy = y2 - y1;

    bool steep = (abs(dy) > abs(dx));
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
        std::swap(dx, dy);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int error = 0;
    int derror = abs(dy) * 2;

    y = y1;

    for (x = x1; x <= x2; x++) {
        if (steep) {
            FreeImage_SetPixelColor(BMP, y, x, &color);
        }
        else {
            FreeImage_SetPixelColor(BMP, x, y, &color);
        }

        error += derror;

        if (error >= dx) {
            y += (y2 > y1 ? 1 : -1);
            error -= dx * 2;
        }
    }


    BMPBuff = BMP;
    //FreeImage_Unload(BMP);
}

void drawVector(Vector2D Drawable, bool ImageOut = false)
{
    double Radian = Drawable.R * M_PI / 180;

    float X2 = Drawable.X + Drawable.F * std::cos(Radian);
    float Y2 = Drawable.Y + Drawable.F * std::sin(Radian);

    if (!ImageOut) {
        drawLineConsole(Drawable.X, Drawable.Y, X2, Y2);
    }
    else{
        drawLineBMP(Drawable.X, Drawable.Y, X2, Y2);
    }
}

void drawVectorArray(Vector2D Drawables[], bool ImageOut = false)
{
    for (int i = 0; i <= (sizeof(Drawables)); ++i)
    {
        drawVector(Drawables[i], ImageOut);
    }
}

int main()
{
    // Initialize "Screen"
    int w = 100, h = 100;

    RGBQUAD BG;
    BG.rgbRed = 255;
    BG.rgbGreen = 255;
    BG.rgbBlue = 255;

    FreeImage_Initialise();
    BMPBuff = FreeImage_Allocate(w, h, 32);

    FreeImage_FillBackground(BMPBuff, &BG);

    // Define Vectors to be drawn
    Vector2D Deg45 = Vector2D(20, 20, 45, 10);
    Vector2D Deg90 = Vector2D(27, 27, 315, 9);
    Vector2D Deg180 = Vector2D(20, 20, 0, 13);

    // Defien and draw the array of vectors
    Vector2D Vectors[] = { Deg45,Deg90,Deg180 };
    drawVectorArray(Vectors, true);
   

    FreeImage_Save(FIF_PNG, BMPBuff, "Bitmap.png", 0);
    FreeImage_Unload(BMPBuff);
    FreeImage_DeInitialise();
}