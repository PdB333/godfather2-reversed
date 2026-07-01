// FUNC_NAME: findFloatByKey
// Address: 0x008be7f0
// This function looks up a float value by an integer key from a table stored in the object.
// The table is a dynamic array of (key, value) pairs. Returns 0.0f if key not found.

float __thiscall findFloatByKey(int thisPtr, int key)
{
    uint index = 0;
    int* pPairs = *(int**)(thisPtr + 0x18c); // pointer to array of int pairs (key, floatValue)
    uint count = *(uint*)(thisPtr + 0x190);   // number of pairs

    if (count != 0)
    {
        do
        {
            if (*pPairs == key) // match found
            {
                // Return the float value stored as int bits at the next slot
                return *(float*)(pPairs + 1);
            }
            index++;
            pPairs += 2; // advance to next pair
        } while (index < count);
    }
    return 0.0f;
}