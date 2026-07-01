// FUNC_NAME: PodArray::reserve
// Function address: 0x00891ce0
// Role: Ensures the dynamic array has at least the specified capacity, reallocating if necessary.
// Structure layout (PodArray):
//   +0x00: int* data      (pointer to allocated memory)
//   +0x04: int size       (number of elements currently used)
//   +0x08: int capacity   (allocated element count)
// Note: The array stores elements of size 4 (likely int or pointers).
// Renewing capacity uses operator new[]/delete[] (FUN_009c8e80 / FUN_009c8f10).

void __thiscall PodArray::reserve(int* this_, uint capacityRequired)
{
    uint oldCapacity = (uint)this_[2];
    if (oldCapacity < capacityRequired)
    {
        // Allocate new memory block
        int* newData = (int*)operator new[](capacityRequired * 4);
        if (this_[0] != 0)
        {
            uint elementCount = (uint)this_[1];
            if (elementCount != 0)
            {
                // Copy existing elements
                uint i = 0;
                int* src = (int*)this_[0];
                int* dst = newData;
                do {
                    if (dst != (int*)0x0) {
                        *dst = *src;
                    }
                    i++;
                    src++;
                    dst++;
                } while (i < elementCount);
            }
            // Free old memory
            operator delete[]((void*)this_[0]);
        }
        // Update pointer and capacity
        this_[0] = (int)newData;
        this_[2] = (int)capacityRequired;
    }
    // else: no-op, already sufficient capacity
}