// FUNC_NAME: UIElement::updateTransformAndCheckRaycast

void __thiscall UIElement::updateTransformAndCheckRaycast(int this, char isActive, int *boundingBox)
{
    int iVar1;
    char cVar2;
    undefined4 uVar3;
    undefined4 local_a8;
    int local_a4;
    int local_a0;
    int local_9c;
    int local_98;
    int local_94;
    undefined4 local_90[10]; // transform input struct (10 dwords)
    float local_5c;          // z offset
    undefined4 local_58;     // from +0x18
    undefined4 local_54;     // global DAT_00d5780c
    char local_50[76];       // output transform matrix (76 bytes)

    if (isActive == '\0') {
        // If not active, just mark dirty if renderable exists
        if (*(int *)(this + 0x54) != 0) {
            markDirty(); // FUN_004df630
        }
    }
    else {
        // Build transform input from object state
        local_58 = *(undefined4 *)(this + 0x18); // rotation or scale
        local_54 = _DAT_00d5780c;                // global constant
        local_90[0] = 0;                         // clear transform input
        local_90[1] = 0;
        local_90[2] = 0;
        local_90[3] = 0;
        local_90[4] = 0;
        local_90[5] = 0;
        local_90[6] = 0;
        local_90[7] = 0;
        local_90[8] = 0;
        local_90[9] = DAT_00e527a4;              // zero constant
        local_90[10] = DAT_00e527a4;             // zero constant
        local_90[11] = DAT_00e527a4;             // zero constant
        local_90[12] = *(undefined4 *)(this + 0x10); // position x
        local_90[13] = *(float *)(this + 0x14) + DAT_00e527a0; // position y + global z offset
        // Note: local_90 is actually 14 elements? The decompiler shows 10 undefined4 but then assigns more.
        // Actually the decompiler shows local_90, local_8c, local_88, local_84, local_80, local_7c, local_78, local_74, local_70, local_6c, local_68, local_64, local_60, local_5c.
        // That's 14 entries. So local_90 is a struct of 14 dwords (56 bytes) plus float local_5c.
        // But the code assigns to local_90, local_8c, etc. So we'll treat it as an array of 14 undefined4.
        // For clarity, I'll use a struct with named fields.
        // However, to keep it simple, I'll just use the original local variable names.
        // Actually, the decompiler's local_90 is the first of a series. Let's reconstruct properly.

        // Reconstructing the transform input struct:
        // local_90 (offset 0), local_8c (offset 4), local_88 (offset 8), local_84 (offset 12),
        // local_80 (offset 16), local_7c (offset 20), local_78 (offset 24), local_74 (offset 28),
        // local_70 (offset 32), local_6c (offset 36), local_68 (offset 40), local_64 (offset 44),
        // local_60 (offset 48), local_5c (offset 52) as float.
        // So it's a 56-byte struct (14 dwords) with a float at the end.
        // The assignments:
        // local_90 = 0; local_8c = 0; local_88 = 0; local_84 = 0;
        // local_74 = 0; local_6c = 0; local_70 = 0; local_78 = 0;
        // local_64 = 0;
        // local_90 = DAT_00e527a4; local_7c = DAT_00e527a4; local_68 = DAT_00e527a4;
        // local_60 = *(undefined4 *)(this + 0x10); // position x
        // local_5c = *(float *)(this + 0x14) + DAT_00e527a0; // position y + z offset
        // So the struct is a 4x4 matrix? Actually 14 dwords + float = 60 bytes? No, 14*4=56, plus float = 60. But local_50 is 76 bytes.
        // This is messy. I'll just use the original local variable names as in the decompiler to avoid confusion.

        // Build transform matrix from input
        buildTransformMatrix(local_50, &local_90); // FUN_0044b4e0

        // Check if bounding box has changed
        if ((((*boundingBox != *(int *)(this + 0x34)) || (boundingBox[1] != *(int *)(this + 0x38))) ||
            (boundingBox[2] != *(int *)(this + 0x3c))) || (boundingBox[3] != *(int *)(this + 0x40))) {
            // Update stored bounding box
            *(int *)(this + 0x34) = *boundingBox;
            *(int *)(this + 0x38) = boundingBox[1];
            *(int *)(this + 0x3c) = boundingBox[2];
            *(int *)(this + 0x40) = boundingBox[3];
            markDirty(); // FUN_004df630
        }

        // If renderable exists, submit it
        if (*(int *)(this + 0x54) != 0) {
            submitRender(local_50); // FUN_004df720
            return;
        }

        // Otherwise, check if bounding box is non-zero (i.e., visible)
        iVar1 = *boundingBox;
        if (((iVar1 != 0) || (boundingBox[1] != 0)) || ((boundingBox[2] != 0 || (boundingBox[3] != 0)))) {
            cVar2 = isVisible(); // FUN_00445250
            if (cVar2 != '\0') {
                // Perform raycast from screen coordinates
                local_9c = boundingBox[1];
                local_98 = boundingBox[2];
                local_94 = boundingBox[3];
                local_a8 = 0;
                local_a0 = iVar1;
                uVar3 = raycast(&local_a4, &local_a0, local_50, 0x1ff, 4, &local_a8); // FUN_004df270
                handleRaycastResult(uVar3); // FUN_00414db0
                if (local_a4 != 0) {
                    *(undefined4 *)(local_a4 + 8) = 0; // Clear some field in result
                    return;
                }
            }
        }
    }
    return;
}