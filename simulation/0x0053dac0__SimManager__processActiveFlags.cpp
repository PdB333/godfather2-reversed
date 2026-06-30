// FUNC_NAME: SimManager::processActiveFlags
void SimManager::processActiveFlags(int count)
{
    // Iterate over a set of objects indexed by i (0 to count-1)
    // Active flag check uses global array gActiveFlags
    // The offset within gActiveFlags is computed as gActiveFlagsBlockSize * 0x1b + i
    // gActiveFlagsBlockSize (DAT_0121bf30) is likely the stride/block size for each manager group
    // 0x1b = 27 suggests a fixed per-group offset (e.g., per type/map)
    for (int i = 0; i < count; i++)
    {
        // Check if this slot is active
        if (gActiveFlags[gActiveFlagsBlockSize * 0x1b + i] != 0)
        {
            // Call the per-object update function (likely updates the ith object)
            updateObject(); // FUN_006063b0
        }
    }
}