// FUNC_NAME: Player::computeTargetPoint
// Address: 0x00803fa0
// This function computes a target position for aiming (likely for player weapon aim).
// It checks various aiming mode flags and uses different methods to obtain the target point.
// Offsets are relative to this (Player*).
// Known offsets: +0x8e0 (uint, flags1, bit9 = free aim?), +0x8e6 (byte, aiming state, bit0 = some lock?), 
// +0x970 (uint, flags2, bit1, bit7), +0x974 (uint, flags3, bit1, bit7),
// +0x1c78 (int, component pointer, used as ID if 0 or 0x48, otherwise as pointer to object -0x48),
// +0x854 (int, some entity/handle for alternative target).

bool __thiscall Player::computeTargetPoint(int arg, Vector3& outPos)
{
    uint flags1 = *(uint*)((char*)this + 0x8e0);
    byte aimingState = *(byte*)((char*)this + 0x8e6);
    int componentPtr = *(int*)((char*)this + 0x1c78);

    // Early branch if not free aiming or component is invalid
    if ( ((flags1 >> 9) & 1) == 0 || componentPtr == 0 || componentPtr == 0x48 || (aimingState & 1) != 0 )
    {
        // Try to compute target from global manager offset (likely camera)
        uint flags2 = *(uint*)((char*)this + 0x970);
        uint flags3 = *(uint*)((char*)this + 0x974);

        if ( ((flags2 >> 1) & 1) != 0 && ((flags3 >> 1) & 1) != 0 && (aimingState & 1) == 0 )
        {
            // Use camera-relative offset: get global manager (e.g. InputManager or CameraManager)
            void* globalMgr = FUN_004262f0(0); // Returns a global manager instance
            Vector3 localPos;
            FUN_007f7450(this, &localPos); // Get world position of this actor
            outPos.x = localPos.x + *(float*)((char*)globalMgr + 0x60);
            outPos.y = localPos.y + *(float*)((char*)globalMgr + 100);
            outPos.z = localPos.z + *(float*)((char*)globalMgr + 0x68);
            return true;
        }
        if ( ((flags2 >> 7) & 1) != 0 && ((flags3 >> 7) & 1) != 0 )
        {
            // Use alternative target method (e.g., lock-on)
            int entityHandle = *(int*)((char*)this + 0x854);
            FUN_00803ef0(&outPos, arg, entityHandle);
            return true;
        }
        // Fail if component is invalid
        if (componentPtr == 0 || componentPtr == 0x48)
            return false;
    }

    // Secondary path: try to fetch target object from component's virtual method
    void* componentBase = (componentPtr == 0) ? 0 : (void*)(componentPtr - 0x48);
    if (componentBase)
    {
        arg = 0; // Reset input parameter
        // Virtual call at vtable+0x10 (index 4): GetObject hash 0x55859efa, returns bool and sets arg to object pointer
        bool hasTarget = (*(bool (__thiscall**)(void*, int*))(*(int*)componentBase + 0x10))(componentBase, &arg);
        // arg now contains an object pointer (or 0) - but decompiler reused stack for float, so we recast
        void* targetObj = (void*)arg;
        if (hasTarget && targetObj != 0 && targetObj != this)
        {
            Vector3 targetPos;
            FUN_007f7450(targetObj, &targetPos); // Get world position of target
            // The original code didn't assign outPos here, but likely it should.
            // We'll assign outPos to the target position.
            outPos = targetPos;
            return true;
        }
    }
    return false;
}