// FUNC_NAME: DisplayManager::setDisplayMode
// Function at 0x006073e0 - Sets display mode parameters (width, height, depth) from available modes
// Based on Godfather 2 (EARS engine) decompilation
bool __fastcall DisplayManager::setDisplayMode(
    uint *thisPtr,               // unaff_ESI: target display config structure (56 bytes)
    uint *configData,            // param_2: config data pointer
    ushort *outWidth,            // param_3: desired/result width
    ushort *outHeight,           // param_4: desired/result height
    ushort *outDepth,            // param_5: desired/result depth
    bool fullscreen,             // param_6: 0 = windowed, 1 = fullscreen
    bool vsync                   // param_7: 0 = disable vsync, 1 = enable
) {
    bool success;
    uint modeCount;
    uint bestWidth, bestHeight, bestDepth;
    uint uVar1;
    int i;
    uint *modePtr;
    uint *pModes;
    int numModes;
    char configBuffer[36]; // local_150
    uint flags;             // local_12c
    uint *modeArray;        // local_15c
    int numModeEntries;     // local_158

    // Try to parse config data (e.g., from video options or device enumeration)
    bool configOk = FUN_0060ea60(configBuffer, &DAT_0120575c, configData, thisPtr, !fullscreen);
    if (!configOk) {
        FUN_00609aa0(); // cleanup or reset
        return false;
    }

    // Clear the display config structure (56 bytes)
    memset(thisPtr, 0, 0x38);

    // Get some value from the parsed config buffer (maybe a mode ID or flags)
    uVar1 = *(uint *)(configBuffer + 4); // offset +4 in parsed data

    // Call another setup function (probably initializes mode list from config)
    FUN_006099f0(configBuffer + 8);

    if (!fullscreen) {
        // Windowed mode: clamp desired dimensions to minimum supported
        bestWidth = 0;
        bestHeight = 0;
        bestDepth = 0;

        ushort minWidth = *outWidth;
        if ((uint)minWidth < *modeArray) {
            minWidth = (ushort)*modeArray;
        }
        *outWidth = minWidth;

        ushort minHeight = *outHeight;
        if ((uint)minHeight < modeArray[1]) {
            minHeight = (ushort)modeArray[1];
        }
        *outHeight = minHeight;

        ushort minDepth = *outDepth;
        if ((uint)minDepth < modeArray[2]) {
            minDepth = (ushort)modeArray[2];
        }
        *outDepth = minDepth;

        // Try to find a mode that fits in the requested bounds
        if (numModes != 0) {
            modePtr = modeArray + 2; // start at depth field of first mode
            for (i = numModes; i != 0; i--) {
                uint availWidth = modePtr[-2];
                uint availHeight = modePtr[-1];
                uint availDepth = *modePtr;

                // Check if this mode fits within requested bounds
                if (bestWidth <= availWidth && availWidth <= *outWidth &&
                    bestHeight <= availHeight && availHeight <= *outHeight &&
                    bestDepth <= (uint)*outDepth) {
                    bestWidth = availWidth;
                    bestHeight = availHeight;
                    bestDepth = availDepth;
                }
                modePtr += 4; // advance to next mode (each mode is 3 uint32s? + padding? but +4*4=16 bytes)
            }
        }

        // Update output parameters with best matching mode
        *outWidth = (ushort)bestWidth;
        *outHeight = (ushort)bestHeight;
        *outDepth = (ushort)bestDepth;

        // Store aspect ratio globally (used for projection calculations)
        DAT_01205878 = (float)*outWidth / (float)*outHeight;
    }

    // Fill the display config structure
    thisPtr[0] = *outWidth;       // +0x00: horizontal resolution
    thisPtr[1] = *outHeight;      // +0x04: vertical resolution
    thisPtr[2] = uVar1;           // +0x08: maybe refresh rate or some mode ID
    thisPtr[3] = 1;               // +0x0C: flags, bit0 set
    thisPtr[4] = 0;               // +0x10: flags, bit1 clear
    thisPtr[5] = 0;               // +0x14: flags, bit2 clear
    thisPtr[6] = 1;               // +0x18: flags, bit3 set
    thisPtr[7] = DAT_012058b4;    // +0x1C: global flag (maybe V-sync or triple buffer)
    thisPtr[8] = (uint)fullscreen; // +0x20: 0=windowed, 1=fullscreen
    thisPtr[9] = 0;               // +0x24: reserved
    thisPtr[10] = 0;              // +0x28: reserved
    thisPtr[11] = 0;              // +0x2C: reserved

    if (fullscreen) {
        thisPtr[0xC] = (uint)*outDepth; // +0x30: color depth (e.g., 32)
        if (vsync) {
            // Use vsync mode from flags
            if ((flags & 2) == 0) {
                thisPtr[0xD] = flags & 1; // +0x34: vsync on/off
            } else {
                thisPtr[0xD] = 2;         // maybe adaptive vsync
            }
        } else {
            // No vsync: preserve some flag from config
            thisPtr[0xD] = flags & 0x80000000;
        }
    } else {
        // Windowed mode: no depth stored, use fixed flags
        thisPtr[0xD] = 0x80000000; // high bit set (windowed specific?)
        thisPtr[0xC] = 0;          // no depth info
    }

    // Free the mode list if it was allocated
    if (modeArray != nullptr) {
        FUN_009c8f10(modeArray); // likely free()
    }

    FUN_00609aa0(); // cleanup or restore state
    return true;
}