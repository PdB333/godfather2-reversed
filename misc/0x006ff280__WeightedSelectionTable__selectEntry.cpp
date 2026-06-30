// FUNC_NAME: WeightedSelectionTable::selectEntry
// Address: 0x006FF280
// Role: Selects a random entry from a weighted selection table (max 8 entries).
//       Entries with a magic header (4x 32-bit sentinel values) are skipped.
//       The selection uses cumulative weight compared to rand() * globalProbabilityScale * weightMultiplier.
// Offsets:
//   +0x58: Entry array (each 0x10 bytes, contains 4 ints for data, possibly IDs/GUIDs)
//   +0xD8: Weight array (float[8])
//   +0xF8: Weight multiplier (float)
//   Global: DAT_00e44590 (float) - probability scale factor

void __thiscall WeightedSelectionTable::selectEntry(int thisPtr, int* outEntryData) // param_2: output 4 ints
{
    int iRand;
    float fCumulativeWeight = 0.0f;
    uint entryIndex = 0;
    float* pWeight = (float*)(thisPtr + 0xD8); // 8 floats, one per entry
    int* pEntryHeader = (int*)(thisPtr + 0x60); // points to the second int of the first entry? Actually pEntryHeader[0] is the third int of entry at +0x60, but we use offsets as given.

    // Magic sentinel values for entries that are not valid (empty slots)
    const int magic1 = 0xBBADBBBA;
    const int magic2 = 0xBEEFBEEF;
    const int magic3 = 0xEAC15A55;
    const int magic4 = 0x91100911;

    // Loop over up to 8 entries.
    while (entryIndex < 8)
    {
        // Check if the current entry at offset +0x58 + entryIndex*0x10 has the magic header.
        // The header is at the start of the entry (offset +0x58). The decompiled code checks 4 ints at offsets:
        //   pEntryHeader[-2] = entry[0]   (at +0x58)
        //   pEntryHeader[-1] = entry[1]   (at +0x5C)
        //   pEntryHeader[0]  = entry[2]   (at +0x60)
        //   pEntryHeader[1]  = entry[3]   (at +0x64)
        // So pEntryHeader points to the third int of entry0 (at +0x60).
        int* currentEntry = (int*)(thisPtr + 0x58 + entryIndex * 0x10);
        bool hasMagic = (currentEntry[0] == magic1) &&
                        (currentEntry[1] == magic2) &&
                        (currentEntry[2] == magic3) &&
                        (currentEntry[3] == magic4);

        if (hasMagic)
        {
            // Sentinel entry - skip it
            // The loop continues because condition is true.
            // Note: No weight accumulation for sentinel entries.
        }
        else
        {
            // Non-sentinel entry: accumulate its weight.
            fCumulativeWeight += *pWeight;

            // Check if cumulative weight exceeds the random threshold.
            // Threshold = rand() * g_fProbabilityScale * weightMultiplier
            float threshold = (float)_rand() * DAT_00e44590 * *(float*)(thisPtr + 0xF8);
            if (fCumulativeWeight > threshold)
            {
                // This entry is selected; break out of loop (exit while condition becomes false)
                break;
            }
        }

        // Move to next entry
        entryIndex++;
        pWeight++;
        // pEntryHeader is not used beyond initial, but original loop incremented piVar3 by 4 (int*) each iteration.
        // We'll just use currentEntry + 4 for next entry.
    }

    if (entryIndex >= 8)
    {
        // No entry selected (should rarely happen)
        return;
    }

    // Copy the 16 bytes (4 ints) of the selected entry to output.
    int* selectedEntry = (int*)(thisPtr + 0x58 + entryIndex * 0x10);
    outEntryData[0] = selectedEntry[0];
    outEntryData[1] = selectedEntry[1];
    outEntryData[2] = selectedEntry[2];
    outEntryData[3] = selectedEntry[3];
}