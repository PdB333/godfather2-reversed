// FUNC_NAME: applyViewportScale
// Function address: 0x004ecd50
// Role: Computes scaled viewport coordinates (width/height) based on object flags and global aspect ratio factors.
// Parameters:
//   outWidth (ecx)  - Output for scaled width
//   outHeight (edx) - Output for scaled height
//   obj (stack)     - Pointer to an object with fields at known offsets (likely a viewport/UI element)
//   uniformScale (stack) - Additional uniform scale factor when flag 0x4000 is set

void __fastcall applyViewportScale(float* outWidth, float* outHeight, int obj, float uniformScale)
{
    float fVar1;
    ushort flags;
    uint mask_uVar3;
    double threshold_dVar4;
    float fVar5;
    float fVar6;
    float fVar7;

    // Global constants (likely from EARS engine initialization)
    threshold_dVar4 = DAT_00e44768;        // A threshold for division (e.g., epsilon)
    mask_uVar3 = DAT_00e44680;             // Bitmask used to truncate float bits (fast truncate trick)
    flags = *(ushort*)(obj + 0x2c);        // +0x2c: flags field (bitfield)

    if ((flags & 0x200) == 0) {
        // Default: just copy raw width and height from object
        *outHeight = *(float*)(obj + 0x40);  // +0x40: base height
        *outWidth = *(float*)(obj + 0x44);   // +0x44: base width
    }
    else {
        // Flag 0x200: Apply aspect ratio correction using global scaling factors
        fVar1 = *(float*)(obj + 8);           // +0x08: source width (e.g., texture width)
        fVar5 = *(float*)(obj + 0x40) * DAT_00e3ac58;  // DAT_00e3ac58 = horizontal aspect factor
        fVar6 = *(float*)(obj + 0x44) * _DAT_00e44770; // _DAT_00e44770 = vertical aspect factor
        fVar7 = (float)((uint)fVar1 & DAT_00e44680);   // Truncate fVar1 to integer bits (fast truncation)

        *outHeight = fVar5;
        *outWidth = fVar6;

        // If truncated source width exceeds threshold, divide height by source width (scaling)
        if (threshold_dVar4 < (double)fVar7) {
            *outHeight = fVar5 / fVar1;
        }

        // Similarly for source height (obj + 0x0c)
        if (threshold_dVar4 < (double)(float)((uint)*(float*)(obj + 0xc) & mask_uVar3)) {
            *outWidth = fVar6 / *(float*)(obj + 0xc);
        }
    }

    if ((flags & 0x4000) != 0) {
        // Flag 0x4000: Apply a uniform scale factor passed as parameter
        *outHeight = *outHeight * uniformScale;
        *outWidth = *outWidth * uniformScale;
        return;
    }

    // Otherwise apply a per-object scale factor stored at +0x48
    fVar1 = *(float*)(obj + 0x48);   // +0x48: general scale factor
    fVar5 = *outWidth;
    *outHeight = *outHeight * fVar1;
    *outWidth = fVar1 * fVar5;
    return;
}