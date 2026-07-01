// FUNC_NAME: loadCharacterDataEntry
// Function address: 0x00935390
// Role: Copies character data (large data block, transform, and name) from global sources into a slot in an array (indexed by DAT_0113058c).
// The structure at each slot is 0x504 bytes, with fields at offsets: +0x44 (256 dwords), +0x444 (16 dwords), +0x484 (128-byte string).
// DAT_012234b8 points to a source structure, or is null. DAT_0113055c is the base address of the target array.
// FUN_00566e70 and FUN_00566e60 return pointers to static or pool buffers containing the transform and model data.
// FUN_00699280 and FUN_006987c0 are vector utilities; FUN_009341d0 may enable/disable a feature.

void loadCharacterDataEntry(void)
{
    int sourceBase;
    int *targetSlot;
    int *modelData;
    int *transformData;
    int *dest;
    int i;
    int vec[3];
    int vecResult;
    char enabled;

    // Determine source base: if global pointer exists, subtract 0xc (maybe offset to a superclass)
    if (DAT_012234b8 == 0) {
        sourceBase = 0;
    } else {
        sourceBase = DAT_012234b8 - 0xc;   // +0x148 used later, offset from this base
    }

    // Get pointers to source data buffers
    modelData = (int *)FUN_00566e70();       // Likely getModelData() - 256 dwords (0x400 bytes)
    transformData = (int *)FUN_00566e60();   // Likely getTransformData() - 16 dwords (0x40 bytes)

    // Compute target slot address based on global index DAT_0113058c
    dest = (int *)(DAT_0113055c + DAT_0113058c * 0x504 + 0x44);

    // Copy 0x100 (256) dwords from modelData to target slot at offset +0x44
    for (i = 0x100; i != 0; i--) {
        *dest = *modelData;
        modelData++;
        dest++;
    }

    // Now copy 0x10 (16) dwords from transformData to offset +0x444
    dest = (int *)(DAT_0113055c + DAT_0113058c * 0x504 + 0x444);
    for (i = 0x10; i != 0; i--) {
        *dest = *transformData;
        transformData++;
        dest++;
    }

    // Copy name string (max 128 bytes) from source base +0x148 to target offset +0x484
    _strncpy(
        (char *)(DAT_0113055c + DAT_0113058c * 0x504 + 0x484),
        (char *)(sourceBase + 0x148),
        0x80
    );

    // Initialize a 3-element vector to zero
    vec[0] = 0;
    vec[1] = 0;
    vec[2] = 0;

    // Perform some vector operation (likely position/rotation)
    vecResult = FUN_00699280(vec);            // e.g., getPosition(vec) or initVector
    enabled = FUN_009341d0(vecResult);        // Check/apply state
    if (enabled != '\0') {
        vecResult = FUN_006987c0(vec);        // e.g., setPosition or convert
        FUN_009341d0(vecResult);
    }

    // If first element is non-zero, call a function pointer (callback?) on it
    if (vec[0] != 0) {
        // Note: local_4 is an uninitialized code pointer in the original decompile.
        // Possibly it was set by a missing assignment, or vec[0] is actually a function pointer.
        // The original decompile had: (*local_4)(local_10[0]);
        // This suggests that after the vector ops, vec[0] might hold a function pointer.
        // For now, assume a direct call with vec[0] as a callback argument.
        // We'll place a placeholder comment.
        // (* (void (*)(int)) vec[0] )(vec[0]);  // Call function pointer from vec[0]
    }

    return;
}