// FUNC_NAME: setDebugColor
// Address: 0x005398d0
// Role: Sets a global 4-by-4 color/vector (RGBA) and, if a specific debug state is active, forwards it to the debug renderer with a subtype selector.

// Global debug color buffer (16 bytes / 4 ints)
static int* gDebugColor = &DAT_0121b7f0; // actually a block of 4 ints at 0x0121b7f0

// Other globals (from decompiled)
// DAT_012058e8 - pointer to current debug manager interface or static instance
// DAT_0121b740 - base address of a debug data structure (likely a color palette or slot)
// DAT_0121b754 - tag/selector for which color to use (0 = draw, 1 = fill? or something like that)
// DAT_0121bbb0, DAT_0121bbb8 - constant pointers indicating two different modes
// DAT_0121b994, DAT_0121b9dc - pointers to specific color data arrays

// Forward declaration of the renderer function
extern void DEBUG_submitColor(int* basePtr, int* colorDataPtr, int* color);

void __fastcall setDebugColor(int* color) // color points to 4 ints (RGBA)
{
    // Store the provided color to global debug color buffer
    gDebugColor[0] = color[0];
    gDebugColor[1] = color[1];
    gDebugColor[2] = color[2];
    gDebugColor[3] = color[3];

    // Check if the current debug system is active (DAT_012058e8 points to the default instance)
    if (DAT_012058e8 == &DAT_0121b740) {
        // Select which color data to forward based on the mode tag
        if (DAT_0121b754 == DAT_0121bbb0) {
            DEBUG_submitColor(DAT_0121bbb0, DAT_0121b994, &DAT_0121b7f0);
        } else if (DAT_0121b754 == DAT_0121bbb8) {
            DEBUG_submitColor(DAT_0121bbb0, DAT_0121b9dc, &DAT_0121b7f0);
        }
    }
}