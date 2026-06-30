// FUNC_NAME: Animation::initFromData
// Address: 0x005890e0
// Role: Initializes animation data from a raw block, copies 20 ints (80 bytes) to internal buffer,
// reads extended duration/speed/state from a sub‑structure selected by flags, and validates.

int Animation::initFromData(void* this, int* animData) {
    int* src;
    int* dst;
    int copyCount;

    // Base/helper initialization (likely clears or sets default fields)
    FUN_00582090();

    // Copy 20 ints from animData to internal buffer at +0x84
    src = animData;
    dst = (int*)((char*)this + 0x84);   // +0x84: animation data array (80 bytes)
    for (copyCount = 20; copyCount != 0; copyCount--) {
        *dst = *src;
        src++;
        dst++;
    }

    // Clear flag byte at +0x70
    *(unsigned char*)((char*)this + 0x70) = 0;   // +0x70: initialisedFlag

    // Determine which sub‑structure to use for the next read
    // animData[11] (offset 0x2C from start of raw data) contains flags
    // animData[0] is a size/type field
    int flags  = animData[11];   // +0x2C
    int size   = animData[0];    // +0x00

    if ((flags & 0x20) == 0 || size < 3) {
        if ((flags & 0x20) == 0 || size != 2) {
            // Default: skip 7 ints (28 bytes)
            animData += 7;
        } else {
            // size == 2 and flag set: skip 12 ints (48 bytes)
            animData += 12;
        }
    } else {
        // size >= 3 and flag set: follow pointer at animData[12] (offset 0x30)
        animData = (int*)animData[12];
    }

    // If no sub‑structure, set defaults
    if (animData == NULL) {
        *(int*)((char*)this + 0x74) = 0;   // +0x74: startFrame
        *(int*)((char*)this + 0x78) = 0;   // +0x78: endFrame
        *(float*)((char*)this + 0x7C) = 0.0f;   // +0x7C: speed (duration)
        *(int*)((char*)this + 0x2C) = 1;   // +0x2C: loopMode/state
        *(int*)((char*)this + 0x80) = 0;   // +0x80: blendMode
    } else {
        // Read 4 values from the sub‑structure
        int startFrame = animData[0];
        int endFrame   = animData[1];   // stored as int but used as float later
        int state      = animData[2];
        int blendMode  = animData[3];

        *(int*)((char*)this + 0x78) = 0;             // endFrame not used – always 0
        *(int*)((char*)this + 0x74) = startFrame;    // +0x74
        *(float*)((char*)this + 0x7C) = (float)endFrame; // +0x7C: speed
        *(int*)((char*)this + 0x2C) = state;         // +0x2C
        *(int*)((char*)this + 0x80) = blendMode;     // +0x80
    }

    // Validate: the animation ID at +0x14 must not be -1, and speed must be positive
    if (*(int*)((char*)this + 0x14) == -1 || *(float*)((char*)this + 0x7C) <= 0.0f) {
        return 0;   // invalid
    }
    return 1;       // success
}