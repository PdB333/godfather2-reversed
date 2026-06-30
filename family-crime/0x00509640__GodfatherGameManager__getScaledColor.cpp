// FUNC_NAME: GodfatherGameManager::getScaledColor
void __thiscall GodfatherGameManager::getScaledColor(float* outColor, int slotIndex, int* baseOffset)
{
    // Get TLS pointer (Windows FS:[0x2C] -> Thread Local Storage array)
    int* tlsArray = *(int**)(*(int**)(FS_OFFSET + 0x2C));
    // Read global base from TLS: first DWORD from TLS array + 8
    int baseAddr = tlsArray[0];  // TLS index 0 is used for some global instance
    int offset = *baseOffset + baseAddr + slotIndex * 0x50;

    // Read 3 bytes from the structure (presumably RGB color stored as packed at end)
    byte r = *(byte*)(offset + 0x5F);
    byte g = *(byte*)(offset + 0x5E);
    byte b = *(byte*)(offset + 0x5D);

    // Alpha comes from a global constant
    float alpha = DAT_00e44764;  // e.g., 1.0f

    // Store as float colors
    outColor[0] = (float)r;
    outColor[1] = (float)g;
    outColor[2] = (float)b;
    outColor[3] = alpha;

    // Apply global intensity/scale factor
    float scale = DAT_00e2dd1c;  // e.g., 1/255.0f or brightness multiplier
    outColor[0] *= scale;
    outColor[1] *= scale;
    outColor[2] *= scale;
    outColor[3] *= scale;
}