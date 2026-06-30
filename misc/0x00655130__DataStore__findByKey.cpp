// FUNC_NAME: DataStore::findByKey
// Function at 0x00655130: Searches a dynamic array of large objects for a match on a 20-byte key.
// The key is composed of 2 shorts and 4 ints (total 20 bytes).
// The array is stored at this+0x2c, with count at this+0x24.
// Each element has the key fields at offsets 0x100, 0x102 (shorts), 0x104, 0x108, 0x10c, 0x110 (ints).
// Returns pointer to the matching element, or 0 if not found.

int* __thiscall DataStore::findByKey(short* key)
{
    int count = *(int*)(this + 0x24); // Number of elements in the array
    if (count > 0)
    {
        int** array = *(int***)(this + 0x2c); // Pointer to array of element pointers
        for (int i = 0; i < count; i++)
        {
            int* element = array[i];
            // Compare key fields
            if (key[0] == *(short*)(element + 0x100) &&      // +0x100: first short
                key[1] == *(short*)(element + 0x102) &&      // +0x102: second short
                *(int*)(key + 2) == *(int*)(element + 0x104) && // +0x104: first int
                *(int*)(key + 4) == *(int*)(element + 0x108) && // +0x108: second int
                *(int*)(key + 6) == *(int*)(element + 0x10c) && // +0x10c: third int
                *(int*)(key + 8) == *(int*)(element + 0x110))   // +0x110: fourth int
            {
                return element;
            }
        }
    }
    return 0;
}