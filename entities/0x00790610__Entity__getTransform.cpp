// FUNC_NAME: Entity::getTransform
// Address: 0x00790610
// Returns a pointer to the transform matrix at offset 0x60.
// If the dirty flag at +0x64 is zero, it either copies from a parent transform (+0xC4)
// or constructs the transform from position (+0xB0) and rotation (bit0 of byte at +0xD4).

int __thiscall Entity::getTransform(int thisPtr)
{
    // Dirty flag: 0 means transform needs update
    if (*(int *)(thisPtr + 0x64) == 0) {
        if (*(int *)(thisPtr + 0xC4) != 0) {
            // Copy from parent transform pointer
            copyTransformMatrix(*(int *)(thisPtr + 0xC4), thisPtr + 0x60);
        } else {
            // Build from position vector and rotation flag
            buildTransformFromPositionAndRotation(
                *(int *)(thisPtr + 0xB0),                     // +0xB0: position (float3 pointer?)
                *(unsigned char *)(thisPtr + 0xD4) & 1,       // +0xD4: rotation low bit
                thisPtr + 0x60
            );
        }
    }
    return thisPtr + 0x60;
}