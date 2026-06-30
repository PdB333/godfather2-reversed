// FUNC_NAME: Transform::applyOffsetFromSource
void Transform::applyOffsetFromSource()
{
    // Local vector for offset (likely quaternion or position offset)
    Vector4 offset; // +0x00: x, +0x04: y, +0x08: z, +0x0c: w
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = 0.0f;
    offset.w = kConstantW; // DAT_00e2b1a4

    // Another local vector for intermediate calculation
    Vector4 temp; // +0x10: x, +0x14: y, +0x18: z, +0x1c: w
    temp.x = 0.0f;
    temp.y = 0.0f;
    temp.z = 0.0f;
    temp.w = kConstantW; // DAT_00e2b1a4

    // Call helper functions
    FUN_00582ac0(); // Possibly some initialization or pre-calculation
    FUN_0056cba0(&offset); // Compute offset from something (e.g., rotation matrix)

    // Read source transform components (from EDI)
    float srcX = *(float*)(unaff_EDI + 0x10);
    float srcY = *(float*)(unaff_EDI + 0x14);
    float srcZ = *(float*)(unaff_EDI + 0x18);
    float srcW = *(float*)(unaff_EDI + 0x1c);

    // Apply offset to destination transform (ESI)
    *(float*)(unaff_ESI + 0x10) = *(float*)(unaff_EDI + 0x10) + temp.x;
    *(float*)(unaff_ESI + 0x14) = srcX + temp.y; // Note: likely a bug in decompiled code, should be srcY + temp.y? But original uses fVar1 + fStack_1c, so it's srcX + temp.y? Actually fVar1 = srcX, fStack_1c = temp.y, so it's srcX + temp.y. That seems odd. Possibly the decompiler misordered. We'll follow the original logic.
    *(float*)(unaff_ESI + 0x18) = srcY + temp.z; // fVar2 + fStack_18
    *(float*)(unaff_ESI + 0x1c) = srcZ + temp.w; // fVar3 + fStack_14

    // Force the last component to the constant
    *(float*)(unaff_ESI + 0x1c) = kConstantW; // DAT_00e2b1a4
}