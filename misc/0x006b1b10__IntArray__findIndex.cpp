// FUNC_NAME: IntArray::findIndex
// Address: 0x006b1b10
// Role: Linear search for an integer value in a simple dynamic array.
// Known class: Simple array wrapper with pointer and count fields (similar to EARS::DataArray).
// Structure offsets: +0x0: int* mData (pointer to array of ints)
//                   +0x4: int mSize (number of elements)

uint __thiscall IntArray::findIndex(const int* pValue) const
{
    // If the array is non-empty, iterate through elements.
    if (mSize != 0) {
        int* pData = mData;
        uint index = 0;
        // Compare each element with the value pointed to by pValue.
        while (*pData != *pValue) {
            index++;
            pData++;
            // If we've reached the end, return not found.
            if (index >= mSize) {
                return 0xffffffff;
            }
        }
        return index;
    }
    return 0xffffffff;
}