// FUNC_NAME: PositionBasedTriggerUpdateManager::updateProximities
// Function address: 0x00701ab0
// Role: Updates proximity-based triggers: retrieves listener position, checks distance to each trigger object,
//       and if within threshold, stores listener position and global timestamp into the trigger's data fields.

void __fastcall PositionBasedTriggerUpdateManager::updateProximities(int thisPtr)
{
    int currentTime = g_currentTime;  // DAT_01205224
    int lastUpdate = *(int *)(thisPtr + 0x514);
    if (currentTime - lastUpdate > 0xFA)  // 250ms interval
    {
        updateTimer();  // FUN_007079a0

        int listenerEntity = getListenerEntity();  // FUN_00471610
        float *listenerPos = (float *)(listenerEntity + 0x30);

        setListenerTransform(thisPtr, listenerPos, 1, *(undefined4 *)(thisPtr + 0x360), 0);  // FUN_0084b9a0

        *(int *)(thisPtr + 0x514) = currentTime;  // store new update timestamp

        // Iterate over all trigger objects
        int triggerListPtr = g_triggerListPtr;  // DAT_012233a0
        int triggerCount = getTriggerCount();  // FUN_0043ff40
        for (int i = 0; i < (uint)triggerCount; ++i)
        {
            int triggerObj = *(int *)(*(int *)(triggerListPtr + 4) + i * 4);
            if (triggerObj != 0 && triggerObj != 0x1F30)  // valid and not a sentinel
            {
                int otherEntity = getListenerEntity();  // FUN_00471610 (returns same or updated listener?)
                float *otherPos = (float *)(otherEntity + 0x30);
                float dx = otherPos[0] - listenerPos[0];
                float dy = otherPos[1] - listenerPos[1];
                float dz = otherPos[2] - listenerPos[2];
                float distSq = dx*dx + dy*dy + dz*dz;
                float threshold = *(float *)(triggerObj + 0x119c);  // proximity radius
                if (distSq < threshold)
                {
                    // Store listener position into trigger's target position fields (+0x11a8, +0x11b0)
                    *(long long *)(triggerObj + 0x11a8) = *(long long *)listenerPos;  // copy first two floats
                    *(float *)(triggerObj + 0x11b0) = listenerPos[2];  // third float
                    *(int *)(triggerObj + 0x11b4) = g_someGlobalTimestamp;  // DAT_01205228
                }
            }
        }
    }
}