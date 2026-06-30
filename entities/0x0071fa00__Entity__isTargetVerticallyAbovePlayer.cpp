// FUNC_NAME: Entity::isTargetVerticallyAbovePlayer
bool __fastcall isTargetVerticallyAbovePlayer(int thisPtr)
{
    // +0x4: pointer to target entity (may include sentinel offset 0x48)
    int* pTarget = *(int**)(thisPtr + 4);

    // Check for null or special sentinel (0x48 = INVALID_TARGET)
    if (pTarget != 0 && pTarget != (int*)0x48)
    {
        // FUN_0043b870 is likely GameManager::getPlayer() using global singleton pointer
        void* pPlayer = (void*)FUN_0043b870(DAT_0112afb8);
        if (pPlayer != 0)
        {
            // Remove the sentinel offset to get real target base address
            int realTargetBase = (int)pTarget - 0x48;

            // +0x2124: offset to a bounding volume or transform descriptor
            float* pBoundingVolume = *(float**)(realTargetBase + 0x2124);

            // +0x18 (sixth float) is vertical extent/height of target's bounds
            float targetHeight = pBoundingVolume[6];

            // +0x4c: vertical position (Y or Z) of player
            float playerHeight = *(float*)((int)pPlayer + 0x4c);

            // Global threshold (e.g., minimum height difference to consider "above")
            if (g_fVerticalThreshold < (targetHeight - playerHeight))
                return true;
        }
    }
    return false;
}