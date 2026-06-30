// FUNC_NAME: readPaletteColorToFloat

void __thiscall readPaletteColorToFloat(int index, int* paletteBasePtr, float* outColor) // outColor passed in EAX
{
    // Get thread-local offset: dereference TEB FS:0x2c -> pointer to structure -> +8
    uint32_t fsBase = __readfsdword(0x2c);
    int threadLocalOffset = *(int*)(*(int*)fsBase + 8);

    // Compute address of the indexed palette entry (each entry is 0x50 bytes)
    int baseValue = *paletteBasePtr;
    int entryAddress = baseValue + threadLocalOffset + index * 0x50;

    // Read color components as bytes (offsets: +0x5F = R, +0x5E = G, +0x5D = B)
    byte colorR = *(byte*)(entryAddress + 0x5F);
    byte colorG = *(byte*)(entryAddress + 0x5E);
    byte colorB = *(byte*)(entryAddress + 0x5D);

    // Set alpha from a global constant (presumably 1.0 or default)
    outColor[3] = DAT_00e44764;

    // Convert bytes to float
    outColor[0] = (float)colorR;
    outColor[1] = (float)colorG;
    outColor[2] = (float)colorB;

    // Scale all four components by a global factor (likely 1.0f/255.0f)
    float scale = DAT_00e2dd1c;
    outColor[0] = scale * outColor[0];
    outColor[1] = scale * outColor[1];
    outColor[2] = scale * outColor[2];
    outColor[3] = scale * outColor[3];
}