// FUNC_NAME: BaseVehicle::resetState
// Address: 0x0086cc70
// Role: Resets vehicle state, saving current velocity/position to a cached copy and zeroing acceleration/angular velocity.
// If a timer (float at +0xA4) is zero, the current velocity/position are also zeroed.

void __fastcall BaseVehicle::resetState(BaseVehicle* this)
{
    // Pointer to a subcomponent (e.g., Havok rigid body) at +0x50. If non-null, get its parent container by subtracting 0x48.
    void* subComponentPtr = *(void**)((char*)this + 0x50);
    int iVar1;
    if (subComponentPtr == 0) {
        iVar1 = 0;
    } else {
        iVar1 = (int)subComponentPtr - 0x48;
    }
    // Call helper to reset subcomponent (e.g., HavokVehicle::resetMotion)
    FUN_008fa130(iVar1);

    // Save current velocity/position (+0x8C, +0x90) to cached copy (+0x94, +0x9C)
    *(float*)((char*)this + 0x94) = *(float*)((char*)this + 0x8C);
    *(float*)((char*)this + 0x9C) = *(float*)((char*)this + 0x90);

    // Zero acceleration, angular velocity, and other state
    *(float*)((char*)this + 0x98) = 0.0f; // +0x98: likely acceleration X
    *(float*)((char*)this + 0xA0) = 0.0f; // +0xA0: likely angular velocity X
    *(float*)((char*)this + 0xA8) = 0.0f; // +0xA8: likely angular velocity Y or Z

    // If elapsed time (float at +0xA4) is zero, also clear current velocity/position
    if (*(float*)((char*)this + 0xA4) == 0.0f) {
        *(float*)((char*)this + 0x8C) = 0.0f;
        *(float*)((char*)this + 0x90) = 0.0f;
    }
}