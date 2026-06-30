// FUNC_NAME: CheckDistanceToPlayer
// Address: 0x00743000
// Purpose: Checks if a given target object is within a certain distance from the player.
// Parameters:
//   ECX: pointer to target object (likely a component or sub-object)
//   EBX: float targetX (X coordinate used in distance calculation)
//   ESI: float targetY (Y coordinate used in distance calculation)
// Returns: Modified handle with low byte set if within range, else cleared.

uint __fastcall CheckDistanceToPlayer(int targetObj, float targetX, float targetY)
{
    // Read handle/pointer at offset +0x54 from the target object
    uint handle = *(uint *)(targetObj + 0x54);

    // Validate handle: subtract 0x48 to compute parent pointer's base, and ensure flags at +0x60 are valid
    // The flags must have the low 2 bits clear (i.e., aligned to 4-byte boundary)
    if ((handle != 0) && (handle = handle - 0x48, handle != 0) &&
        ((*(uint *)(targetObj + 0x60) & 0xfffffffc) != 0))
    {
        int *parentPtr;
        if (*(int *)(targetObj + 0x54) == 0)
        {
            parentPtr = nullptr;
        }
        else
        {
            // Parent structure is found by subtracting 0x48 from the pointer at +0x54
            parentPtr = (int *)(*(int *)(targetObj + 0x54) - 0x48);
        }

        // Call virtual function at vtable offset 0xA4 on the parent structure
        // This function takes an output vector (3 floats) and a pointer to data at targetObj+0x60
        float targetPosition[3];
        (**(code **)(*parentPtr + 0xA4))(targetPosition, targetObj + 0x60);

        // Get the player's current position via a global function
        int playerBase = FUN_00471610();
        float playerX = *(float *)(playerBase + 0x30);
        float playerY = *(float *)(playerBase + 0x34);
        float playerZ = *(float *)(playerBase + 0x38);

        // Compute differences: player position minus the supplied coordinates
        float diffX = playerX - targetX;
        float diffY = playerY - targetY;
        float diffZ = playerZ - targetPosition[0];

        // Modify handle: build an ID from the player pointer and set low bit as "in range" flag
        handle = ((uint)(playerBase + 0x30) >> 8) | 1;

        // Check squared distance against a global threshold
        if ((diffX * diffX + diffY * diffY + diffZ * diffZ) < DAT_00d5f540)
        {
            return handle;   // within range, return handle with low bit set
        }
    }

    // Clear low byte of handle (remove "in range" flag) if conditions not met
    return handle & 0xffffff00;
}