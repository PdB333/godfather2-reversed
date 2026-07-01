// FUNC_NAME: EntityVisual::resolveColor
void __fastcall EntityVisual::resolveColor(int thisPtr)
{
    // Local 4-float vector (likely RGBA color)
    float color[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    // Check bit 5 of flags at +0x60 (0x20 = "use stored color" flag)
    if ((*(unsigned int*)(thisPtr + 0x60) >> 5 & 1) == 0)
    {
        // No stored override: compute color from source
        if (*(int*)(thisPtr + 0x148) == *(int*)(thisPtr + 0x13c))
        {
            // Source IDs match: use default color
            FUN_00955320(&color);
        }
        else
        {
            // Different source ID: look up resource and get its color
            int resourcePtr = FUN_00849cf0(*(int*)(thisPtr + 0x13c));
            if (resourcePtr != 0)
            {
                FUN_00954ad0(resourcePtr, &color);
            }
        }
    }
    else
    {
        // Use stored color from +0x94..0x9c (3 floats) and global alpha
        *(unsigned int*)(thisPtr + 0x60) &= 0xffffffdf; // Clear bit 5
        color[0] = *(float*)(thisPtr + 0x94);
        color[1] = *(float*)(thisPtr + 0x98);
        color[2] = *(float*)(thisPtr + 0x9c);
        color[3] = _DAT_00d5780c; // Global constant (likely 1.0f)
    }

    // Write the color to the render data object at +0x68, offset +0xd0
    int renderData = *(int*)(thisPtr + 0x68);
    *(float*)(renderData + 0xd0) = color[0];
    *(float*)(renderData + 0xd4) = color[1];
    *(float*)(renderData + 0xd8) = color[2];
    *(float*)(renderData + 0xdc) = color[3];
}