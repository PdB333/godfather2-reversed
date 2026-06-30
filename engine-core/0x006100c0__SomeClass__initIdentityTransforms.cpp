// FUNC_NAME: SomeClass::initIdentityTransforms
void __thiscall SomeClass::initIdentityTransforms(void)
{
    // Initialize a set of four 20-byte blocks (each: float w, float x, float y, float z, float pad) to identity quaternion pattern
    // Global value (likely 1.0f) stored as identity quaternion w component
    
    // Block 0 at offset 0x40
    *(float *)(this + 0x40) = DAT_00e2b1a4; // w = 1.0
    *(float *)(this + 0x44) = 0.0f;         // x = 0
    *(float *)(this + 0x48) = 0.0f;         // y = 0
    *(float *)(this + 0x4C) = 0.0f;         // z = 0
    *(float *)(this + 0x50) = 0.0f;         // pad = 0

    // Block 1 at offset 0x54
    *(float *)(this + 0x54) = DAT_00e2b1a4; // w = 1.0
    *(float *)(this + 0x58) = 0.0f;
    *(float *)(this + 0x5C) = 0.0f;
    *(float *)(this + 0x60) = 0.0f;
    *(float *)(this + 0x64) = 0.0f;         // pad = 0

    // Block 2 at offset 0x68
    *(float *)(this + 0x68) = DAT_00e2b1a4; // w = 1.0
    *(float *)(this + 0x6C) = 0.0f;
    *(float *)(this + 0x70) = 0.0f;
    *(float *)(this + 0x74) = 0.0f;
    *(float *)(this + 0x78) = 0.0f;         // pad = 0

    // Block 3 (single initializer) at offset 0x7C
    *(float *)(this + 0x7C) = DAT_00e2b1a4; // only w set, rest presumably left as is

    // Call further initialization (likely for dependent sub-objects)
    FUN_006101b0();
}