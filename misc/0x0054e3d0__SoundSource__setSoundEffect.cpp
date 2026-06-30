// FUNC_NAME: SoundSource::setSoundEffect

void __thiscall SoundSource::setSoundEffect(uint this, void* newSoundEffect)
{
    float maxExtent;
    // Bounding box struct (likely minX, maxX, minY, maxY)
    struct BoundingBox2D {
        float minX; // +0x00 (fStack_94)
        float maxX; // +0x04 (fStack_84)
        float minY; // +0x08 (fStack_8c)
        float maxY; // +0x0c (fStack_7c)
    } bounds;

    // Release previous sound effect (ref counted object at +0x18)
    FUN_009e7530(*(void**)(this + 0x18));
    *(void**)(this + 0x18) = newSoundEffect;
    FUN_009e7450(newSoundEffect);

    // Get bounding box from the sound effect via virtual function at vtable+0x18
    (*(void (**)(BoundingBox2D*))(**(int**)newSoundEffect + 0x18))(&bounds);

    // Compute maximum axis-aligned dimension (clamped to 0)
    maxExtent = 0.0f;
    float dx = bounds.maxX - bounds.minX;
    if (0.0f <= dx) {
        maxExtent = dx;
    }
    float dy = bounds.maxY - bounds.minY;
    if (maxExtent <= dy) {
        maxExtent = dy;
    }

    // Build parameter block for sound property update
    struct SoundParamBlock {
        byte pad0[0x20];  // offset 0x00 – uStack_74 to uStack_54? Actually zeroed area
        int uStack_54;   // +0x20 - set to DAT_00e2b1a4 (likely 0)
        byte pad1[0x10]; // +0x24 to +0x33
        int uStack_40;   // +0x34 - set to DAT_00e2b1a4
        byte pad2[0x08]; // +0x38 to +0x3f? Actually uStack_44, uStack_3c, uStack_38, uStack_34 were zeroed
        int uStack_28;   // +0x44 - set to DAT_00e2b334
        float fStack_24; // +0x48 - set to (float)DAT_00e2b1a4 then overwritten
        int uStack_20;   // +0x4c - set to 4
        int uStack_2c;   // +0x50 - set to newSoundEffect pointer (later)
    } params; // Stack layout from ebp-0x74 to ebp-0x1c, size 0x58 bytes

    // Zero-initialize the block (as done in asm)
    __asm { memset(&params, 0, sizeof(params)); } // Equivalent to all the zero assignments

    params.uStack_54 = DAT_00e2b1a4;
    params.uStack_40 = DAT_00e2b1a4;
    params.uStack_28 = DAT_00e2b334;
    params.fStack_24 = (float)DAT_00e2b1a4;
    params.uStack_20 = 4;

    FUN_00552340(); // Begin parameter update

    params.uStack_2c = *(void**)(this + 0x18); // The new sound effect
    params.fStack_24 = maxExtent * DAT_00e2cd54 * *(float*)(this + 0x80); // Scale factor at +0x80

    FUN_005523c0(); // Apply parameter update
}