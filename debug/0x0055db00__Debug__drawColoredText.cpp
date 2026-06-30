// FUNC_NAME: Debug::drawColoredText
// Address: 0x0055db00
// Draws colored debug text using a color struct from EAX and a string parameter.
// Checks a state byte at (this+0x18)->+0xd8 == 0x07 to trigger additional draw.

struct Color3 {
    uint32_t r; // red component
    uint32_t g; // green component
    uint32_t b; // blue component
};

void __thiscall Debug::drawColoredText(Color3 *color, const char *text) {
    // Build a 4-element color array (RGB + alpha from global)
    uint32_t colorData[4];
    colorData[0] = color->r;
    colorData[1] = color->g;
    colorData[2] = color->b;
    colorData[3] = DAT_00e2b1a4; // global alpha value (offset unclear)

    // Set text color and render the string
    FUN_00aa36a0(colorData, text);

    // Check if debug overlay is active (byte at offset 0xd8 of sub-object at this+0x18)
    if (*(char *)(*(int *)((char *)this + 0x18) + 0xd8) == '\a') {
        FUN_009f4240(1, 1, 0); // maybe draw additional info or toggle debug
    }

    // Clean up temporary buffer (28 bytes, possibly a string buffer)
    char tempBuf[28];
    FUN_009f4c70(tempBuf);
}