// FUNC_NAME: SystemStateManager::checkAndTriggerAction
void SystemStateManager::checkAndTriggerAction(void)
{
    // DAT_012233b8 is a global singleton pointer to SystemStateManager
    // +0x10 holds flag bits (uint)
    // Set bit 4 (0x10) to indicate "active" state
    *(uint *)(DAT_012233b8 + 0x10) |= 0x10;

    uint flags = *(uint *)(DAT_012233b8 + 0x10);
    // Check if bit 1 (0x4) is set – "pending" flag
    if ((flags & 0x4) != 0)
    {
        // Clear the pending flag
        *(uint *)(DAT_012233b8 + 0x10) = flags & 0xFFFFFFFA;

        // Build a 12-byte resource key (GUID or similar)
        // DAT_01206a20 is a constant used as base resource ID
        uint keyParts[3]; // 12 bytes total
        keyParts[0] = DAT_01206a20;
        keyParts[1] = 0;
        keyParts[2] = 0;

        // Queue the resource load (0 = synchronous? or priority flag)
        FUN_00408a00(keyParts, 0);
    }
}