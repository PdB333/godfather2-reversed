// FUNC_NAME: sortByFloatThenPointer
void sortByFloatThenPointer(uint** start, uint** end)
{
    if (start == end)
        return;

    for (uint** currentInsert = start + 1; currentInsert != end; ++currentInsert)
    {
        uint* currentPtr = *currentInsert;
        uint** insertPos = currentInsert;

        if (insertPos != start)
        {
            float currentFloat = *(float*)(currentPtr + 0x3); // +0xC in bytes, but uint* is 4-byte aligned, so offset in uint is 0x3? Actually uint* is 4 bytes, so +0xC bytes = +3 uint elements. However, the original code uses uVar2 + 0xc where uVar2 is a uint (pointer). So it's byte offset. To cast correctly, we use (float*)(currentPtr + 0x3) if currentPtr is uint*, but it's actually a pointer stored as uint. Better to treat as char* or use proper cast. We'll use a float* dereference.

            // Original inner loop: shift elements to the right until correct position found
            do
            {
                uint* previousPtr = *(insertPos - 1);
                float previousFloat = *(float*)(previousPtr + 0x3); // byte offset 0xC

                // Condition to stop shifting: current float <= previous float, with tie-breaker on pointer value
                if ( (currentFloat <= previousFloat) &&
                     ((currentFloat < previousFloat) || (currentPtr <= previousPtr)) )
                    break;

                *insertPos = previousPtr;
                --insertPos;
            } while (insertPos != start);
        }
        *insertPos = currentPtr;
    }
}