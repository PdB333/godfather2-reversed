// FUNC_NAME: Color::lookupColorIndex
uint lookupColorIndex(const char* colorName)
{
    // Global table of color name strings (0x18 entries, striding by 2 pointers each)
    // +0x00: char* colorName
    // +0x04: unknown (color value or padding)
    extern const char* gColorNames[0x18][2]; // actual layout: pairs of pointers

    for (uint i = 0; i < 0x18; i++)
    {
        // Compare against the name pointer in each pair
        if (__stricmp(gColorNames[i][0], colorName) == 0)
        {
            return i;
        }
    }

    // Return sentinel for "not found" (index beyond valid range)
    return 0x18;
}