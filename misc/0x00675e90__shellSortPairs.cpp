// FUNC_NAME: shellSortPairs
// Address: 0x00675e90
// Role: Shell sort on an array of 8‑byte records (uint key, short value).
// The original x86 code expects the array base pointer in ESI; we expose it as a parameter.
void shellSortPairs(void* arrayBase, int count)
{
    int gap = count / 2;
    while (gap >= 1)
    {
        if (gap < count)
        {
            int remaining = count - gap;
            for (int i = 0; i < remaining; i++)
            {
                // Pointer to current element (index = gap + i)
                uint* curKey   = (uint*)((uint8_t*)arrayBase + (gap + i) * 8);
                short* curVal  = (short*)((uint8_t*)arrayBase + (gap + i) * 8 + 4);
                // Start comparison with element 'gap' positions earlier
                int j = i;
                uint* cmpKey   = (uint*)((uint8_t*)arrayBase + j * 8);
                short* cmpVal  = (short*)((uint8_t*)arrayBase + j * 8 + 4);
                // Insert current element into the sorted gap‑separated sequence
                while (j >= 0 && *curKey < *cmpKey) // ascending by key
                {
                    // Swap keys
                    uint tmpKey = *cmpKey;
                    *cmpKey = *curKey;
                    *curKey = tmpKey;
                    // Swap values
                    short tmpVal = *cmpVal;
                    *cmpVal = *curVal;
                    *curVal = tmpVal;
                    // Move to previous gap position
                    curKey = cmpKey;
                    curVal = cmpVal;
                    j -= gap;
                    cmpKey = (uint*)((uint8_t*)arrayBase + j * 8);
                    cmpVal = (short*)((uint8_t*)arrayBase + j * 8 + 4);
                }
            }
        }
        gap >>= 1; // halve the gap
    }
}