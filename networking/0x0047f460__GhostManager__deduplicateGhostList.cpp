// FUNC_NAME: GhostManager::deduplicateGhostList

void GhostManager::deduplicateGhostList()
{
    // Temporary array of 32 ghost entries (each 6 ints = 24 bytes)
    int tempEntries[32][6];
    uint32_t tempCount = 0;

    // Clear the temp array
    memset(tempEntries, 0, sizeof(tempEntries));

    // Initialize temp (likely sorts or prepares for dedup)
    FUN_0047f610(tempEntries, &tempCount); // First pass

    uint32_t numSourceEntries = *(uint32_t*)(this + 0x394);
    if (numSourceEntries != 0)
    {
        // Iterate over source entries (list starts at +0x94)
        int* sourceEntryPtr = (int*)(this + 0x9c); // Points to first entry's third int? Actually array base is +0x94, but we use sourceEntryPtr[-2] to access first int.
        for (uint32_t i = 0; i < numSourceEntries; i++)
        {
            bool isDuplicate = false;
            // Check against existing temp entries
            for (uint32_t j = 0; j < tempCount; j++)
            {
                int* tempEntry = &tempEntries[j][0];
                if (tempEntry[0] == sourceEntryPtr[-2] &&
                    tempEntry[1] == sourceEntryPtr[-1] &&
                    tempEntry[2] == sourceEntryPtr[0] &&
                    tempEntry[3] == sourceEntryPtr[1])
                {
                    // Match found; ignore
                    isDuplicate = true;
                    break;
                }
            }

            if (!isDuplicate)
            {
                // Add new entry to temp list
                int* destEntry = &tempEntries[tempCount][0];
                destEntry[0] = sourceEntryPtr[-2];
                destEntry[1] = sourceEntryPtr[-1];
                destEntry[2] = sourceEntryPtr[0];
                destEntry[3] = sourceEntryPtr[1];
                destEntry[4] = sourceEntryPtr[2];
                destEntry[5] = sourceEntryPtr[3];
                tempCount++;
            }
            sourceEntryPtr += 6; // Move to next source entry (24 bytes)
        }
    }

    // Second sort/compact pass
    FUN_0047f610(tempEntries, &tempCount);

    // Final processing (likely hash update or validation)
    FUN_0047fe30();

    // Copy deduplicated entries back into the object's list
    if (tempCount != 0)
    {
        int* tempEntry = &tempEntries[0][0];
        do
        {
            uint32_t currentEntryCount = *(uint32_t*)(this + 0x394);
            if (currentEntryCount < 32) // Maximum capacity
            {
                int* destEntry = (int*)(this + 0x94 + currentEntryCount * 24);
                destEntry[0] = tempEntry[0];
                destEntry[1] = tempEntry[1];
                destEntry[2] = tempEntry[2];
                destEntry[3] = tempEntry[3];
                destEntry[4] = tempEntry[4];
                destEntry[5] = tempEntry[5];
                *(uint32_t*)(this + 0x394) = currentEntryCount + 1;
            }
            tempEntry += 6;
            tempCount--;
        } while (tempCount != 0);
    }

    // Mark that the list needs update
    *(uint8_t*)(this + 0x91) = 1;
}