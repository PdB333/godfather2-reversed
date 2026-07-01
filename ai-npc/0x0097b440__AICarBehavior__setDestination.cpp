// FUNC_NAME: AICarBehavior::setDestination
void __thiscall AICarBehavior::setDestination(int this, int entityHandle, const DestinationData* pDest, int waypointIndex, int extraParam)
{
    // Resolve handle to an object pointer
    int* objectPtr = FUN_00849cf0(entityHandle);
    if (objectPtr != NULL && ((~(*(byte*)(objectPtr + 0x58)) & 1) != 0))
    {
        // Determine which target slot to use based on driving mode (state at +0x14c)
        int currentTarget;
        int drivingMode = *(int*)(this + 0x14c);
        if (drivingMode == 1 || 1 < (drivingMode - 3U))
        {
            // Use normal forward target slot
            currentTarget = *(int*)(this + 0x140);
        }
        else
        {
            // Use reverse/alternate target slot
            currentTarget = *(int*)(this + 0x144);
        }

        // If the requested entity is different from the current target, set a new destination
        if (entityHandle != currentTarget)
        {
            // Mark destination as pending (bit 0x20 in flags)
            *(uint*)(this + 0x60) |= 0x20;
            // Copy destination data (likely 12 bytes: e.g., position or target)
            *(uint64_t*)(this + 0x94) = *((uint64_t*)pDest);
            *(uint32_t*)(this + 0x9C) = *((uint32_t*)pDest + 2);
            // Apply the new destination (start moving)
            FUN_0097b380(entityHandle, waypointIndex);
            return;
        }
        else
        {
            // Same destination: clear pending flag and update path
            *(uint*)(this + 0x60) &= 0xFFFFFFDF;
            // Continue/advance along the current path
            FUN_00954c40(pDest, waypointIndex, 0, extraParam);
            FUN_0097b380(entityHandle, waypointIndex);
        }
    }
}