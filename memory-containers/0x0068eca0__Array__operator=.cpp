// FUNC_NAME: Array::operator=
// Function at 0x0068eca0: Copy assignment operator for a simple dynamic array (data pointer, size, capacity)
int * __thiscall Array::operator=(int *thisParam, int *other)
{
    int iVar1;
    int *newData;
    uint i;

    if (thisParam != other) {
        // If current capacity is less than other's size, reallocate
        if ((uint)thisParam[2] < (uint)other[1]) {
            // Deallocate existing data (free)
            FUN_009c8f10(*thisParam);
            iVar1 = other[1];
            thisParam[2] = iVar1; // set new capacity = other's size
            if (iVar1 == 0) {
                newData = 0;
            } else {
                // Allocate new block (iVar1 * 4 bytes)
                newData = (int *)FUN_009c8e80(iVar1 * 4);
            }
            *thisParam = (int)newData; // assign new data pointer
        }
        // Copy elements from other's data to this data
        i = 0;
        if (other[1] != 0) {
            do {
                newData = (int *)(*thisParam + i * 4);
                if (newData != (int *)0x0) {
                    *newData = *(int *)((int)other + i * 4); // other[0] + i*4
                }
                i = i + 1;
            } while (i < (uint)other[1]);
        }
        // Set size to other's size (offset +4)
        thisParam[1] = other[1];
    }
    return thisParam;
}