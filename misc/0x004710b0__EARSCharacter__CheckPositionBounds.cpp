// FUNC_NAME: EARSCharacter::CheckPositionBounds
void __thiscall EARSCharacter::CheckPositionBounds(void* pTransformOwner)
{
    // Global constants for position validation
    extern float g_fDriftThreshold;     // DAT_00e44598
    extern float g_fGridSnapOffset;     // DAT_00e2b1a4
    extern uint  g_uGridMask;           // DAT_00e44680

    // Read position vector (x,y,z) from pTransformOwner at offsets +0x134, +0x138, +0x13C
    float x = *(float*)((char*)pTransformOwner + 0x134);
    float y = *(float*)((char*)pTransformOwner + 0x138);
    float z = *(float*)((char*)pTransformOwner + 0x13C);

    // Apply offset, then bitwise mask (quantization), compare to threshold
    if (g_fDriftThreshold < (float)((uint)(x - g_fGridSnapOffset) & g_uGridMask) ||
        g_fDriftThreshold < (float)((uint)(y - g_fGridSnapOffset) & g_uGridMask) ||
        g_fDriftThreshold < (float)((uint)(z - g_fGridSnapOffset) & g_uGridMask))
    {
        // Reset or handle drift (calls FUN_0043a2a0 with this as both arguments)
        FUN_0043a2a0(this, this);
    }
}