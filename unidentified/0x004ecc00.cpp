// FUN_NAME: setGlobalColorValues
// Address: 0x004ecc00
// Role: Stores four values (likely RGBA color) into global color struct, then optionally applies via another function if a certain condition is met.

__fastcall void setGlobalColorValues(unsigned int* colorData) // colorData likely points to a 4-integer color (RGBA)
{
    // Store the four color components into global variables at 0x01219b40
    g_colorRed   = colorData[0];
    g_colorGreen = colorData[1];
    g_colorBlue  = colorData[2];
    g_colorAlpha = colorData[3];

    // Check if the global singleton pointer matches and the indexed slot is active
    // +0x30 size per element in the array at g_uiElementArray
    if (g_singletonPointer == &g_singletonAddress && 
        *(int*)(&g_uiElementArray + (unsigned int)g_currentIndex * 0x30) != 0)
    {
        applyColorToUIElement(g_uiSomeValue, *(int*)(&g_uiElementArray + (unsigned int)g_currentIndex * 0x30), colorData);
    }
}