// FUNC_NAME: setupDrawRectForCurrentScreen
void setupDrawRectForCurrentScreen(void)
{
    // Construct a rectangle: left=0, top=0, right=gScreenSize, bottom=gScreenSize
    // Note: gScreenSize is used for both dimensions, implying a square region.
    int rect[4] = { 0, 0, gScreenSize, gScreenSize }; // may represent left, top, right, bottom

    // Array of screen data structures (each 0x38 bytes) indexed by current screen index.
    int currentScreenIndex = gCurrentScreenIndex;
    // +0x00: first field of screen data – probably a pointer to a surface/texture.
    int* screenData = (int*)(gScreenArrayBase + currentScreenIndex * 0x38);
    if (*screenData != 0) {
        // gDevice: global rendering device or context.
        // *screenData: the surface pointer from the current screen data.
        // rect: the square region to draw.
        drawRectangle(gDevice, *screenData, rect);
    }
}