// FUNC_NAME: DynamicArray::ensureCapacity
// Function address: 0x0082dc60
// Role: Ensures the dynamic array has at least 'requiredCapacity' elements of storage.
//                If current capacity is insufficient, allocates new buffer, copies existing
//                elements, frees old buffer, and updates capacity. Part of EA EARS engine
//                custom container (likely a simple dynamic array with int* data).
// Structure fields:
//   this[0] = int* data (pointer to element array, each element 4 bytes)
//   this[1] = int size   (number of elements currently in use)
//   this[2] = int capacity (number of allocated elements)

void __thiscall DynamicArray::ensureCapacity(int *this, unsigned int requiredCapacity)
{
    // Only grow if needed
    if (this[2] < requiredCapacity)
    {
        // Allocate new buffer (element size = 4 bytes)
        int *newBuffer = (int *)FUN_009c8e80(requiredCapacity * 4); // likely allocate / operator new
        
        // Copy existing elements if we had any
        if (this[0] != 0)
        {
            unsigned int count = 0;
            int *dest = newBuffer;
            if (this[1] != 0)
            {
                do
                {
                    // The safety check for null dest is defensive (allocation should succeed)
                    if (dest != (int *)0x0)
                    {
                        *dest = *(int *)(this[0] + count);
                    }
                    count = count + 1;
                    dest = dest + 1;
                } while (count < (unsigned int)this[1]);
            }
            // Free old buffer
            FUN_009c8f10((void *)this[0]); // likely deallocate / operator delete
        }
        // Update data pointer and capacity
        this[0] = (int)newBuffer;
        this[2] = requiredCapacity;
    }
    // No change to size (this[1]) – caller handles that separately
    return;
}