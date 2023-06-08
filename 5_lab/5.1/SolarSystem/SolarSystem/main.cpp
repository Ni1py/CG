#include "MyApplication.h"
#include "GdiPlusInitializer.h"

CGdiPlusInitializer gdiplusInitializer;
CMyApplication solarSystem("Solar System", 1200, 750);

int main()
{
    solarSystem.MainLoop();
    return 0;
}