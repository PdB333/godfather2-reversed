//FUNC_NAME: UIElement::render
void __fastcall UIElement::render(int thisPtr)
{
    // Check if the element is visible (offset +0xB0)
    if (*(int *)(thisPtr + 0xB0) != 0)
    {
        // Temporary color buffer (4 bytes: RGBA)
        unsigned int colorBuffer;
        
        // Set up rendering state via engine functions
        FUN_004aae90(thisPtr + 0x80);          // Set transformation or texture
        FUN_004aadb0(*(int *)(thisPtr + 0x4C)); // Set some resource handle
        FUN_004aadd0(*(int *)(thisPtr + 0x50)); // Set another handle
        FUN_004aa8c0(*(int *)(thisPtr + 0x54)); // Set another handle
        
        // Scale a float value (e.g., opacity or size) by a global constant
        float scaledValue = *(float *)(thisPtr + 0x58) * DAT_00e445c8;
        FUN_00b99e20();                         // Possibly a state push
        FUN_004aadf0(scaledValue);              // Apply scaled value
        
        FUN_004aae10(*(int *)(thisPtr + 0x5C)); // Set another handle
        FUN_004aaf40(*(int *)(thisPtr + 0x60)); // Set another handle
        FUN_004aaf60(*(int *)(thisPtr + 100));  // Set another handle (offset 0x64)
        
        // Pack color from four floats (scaled by DAT_00e44584, likely 255.0f)
        // Offsets: +0x6C = alpha, +0x90 = red, +0x94 = green, +0x98 = blue
        unsigned char alpha = (unsigned char)(*(float *)(thisPtr + 0x6C) * DAT_00e44584);
        unsigned char blue  = (unsigned char)(*(float *)(thisPtr + 0x98) * DAT_00e44584);
        unsigned char green = (unsigned char)(*(float *)(thisPtr + 0x94) * DAT_00e44584);
        unsigned char red   = (unsigned char)(*(float *)(thisPtr + 0x90) * DAT_00e44584);
        
        // Assemble as RGBA (little-endian: red at lowest byte)
        colorBuffer = (alpha << 24) | (blue << 16) | (green << 8) | red;
        
        FUN_004ab080(&colorBuffer);             // Set the color
        FUN_004aad70(thisPtr + 0xC0);           // Apply final transform or draw call
    }
}