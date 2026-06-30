// FUNC_NAME: FixedArray::growCapacity
void FixedArray::growCapacity(uint newCapacity)
{
    // Check if we need to grow (newCapacity > capacity)
    if (newCapacity > this->capacity) {                 // unaff_ESI[2] is capacity, offset +0x08
        // Allocate new memory block (element size 4 bytes)
        int *newData = (int *)internalAlloc(newCapacity * 4);  // FUN_009c8e80 is alloc

        // If old data exists, copy elements up to current count
        if (this->data != NULL) {                       // *unaff_ESI is data pointer, offset +0x00
            uint copiedCount = 0;
            int *dest = newData;
            if (this->count != 0) {                     // unaff_ESI[1] is count, offset +0x04
                do {
                    if (dest != NULL) {
                        *dest = *(int *)(this->data + copiedCount * 4);
                    }
                    copiedCount++;
                    dest++;
                } while (copiedCount < this->count);
            }
            // Free old data
            internalFree(this->data);                   // FUN_009c8f10 is free
        }
        // Update pointers and capacity
        this->data = newData;                           // *unaff_ESI = newData
        this->capacity = newCapacity;                   // unaff_ESI[2] = newCapacity
    }
}