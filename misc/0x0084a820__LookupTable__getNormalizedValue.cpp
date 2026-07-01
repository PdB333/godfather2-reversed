// FUNC_NAME: LookupTable::getNormalizedValue
// Address: 0x0084a820
// Returns a normalized ratio (value / maxValue) from a key-value pair lookup table.
// The object contains: 
//   +0x00: m_pData (pointer to a struct with maxValue at +0x04)
//   +0x10: m_pPairs (array of {key, value} int pairs)
//   +0x14: m_nCount (number of pairs)
float __thiscall LookupTable::getNormalizedValue(int* thisPtr, int key)
{
    uint index;
    int value;
    int* pairs;
    float fValue;
    float fMax;

    index = 0;
    if (thisPtr[5] != 0) {          // m_nCount != 0
        pairs = (int*)thisPtr[4];   // m_pPairs
        do {
            if (*pairs == key) {    // found matching key
                if (index != 0xffffffff) {
                    value = ((int*)thisPtr[4])[index * 2 + 1];
                    goto LAB_0084a845;
                }
                break;
            }
            index++;
            pairs += 2;             // advance to next pair
        } while (index < (uint)thisPtr[5]);
    }
    value = 0;                      // default if not found

LAB_0084a845:
    fValue = (float)value;
    if (value < 0) {
        fValue = fValue + (float)DAT_00e44578;  // conversion adjustment (0x80000000 as float)
    }
    fMax = (float)*(int*)(*thisPtr + 4);        // m_pData->maxValue
    if (*(int*)(*thisPtr + 4) < 0) {
        fMax = fMax + (float)DAT_00e44578;
    }
    return fValue / fMax;                       // normalized result in [0,1]
}