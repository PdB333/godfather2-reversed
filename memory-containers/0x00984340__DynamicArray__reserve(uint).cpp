// FUNC_NAME: DynamicArray::reserve(uint)
void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // this->data = *param_1
    // this->count = param_1[1]
    // this->capacity = param_1[2]
    if (capacity < newCapacity) {
        // Allocate new buffer: capacity * elementSize (0x28 = 40 bytes per element)
        void* newBuffer = alloc_memory(newCapacity * 0x28); // FUN_009c8e80

        if (data != 0 && count != 0) {
            // New element pointer starts 0x14 bytes into the new buffer (header area)
            int* newElem = (int*)((uint)newBuffer + 0x14);
            for (uint i = 0; i < count; i++) {
                // Compute old element pointer relative to new element
                int* oldElem = (int*)((uint)newElem + (uint)data - (uint)newBuffer - 0x14);

                // Copy element header (first 4 bytes) to offset -0x14 from element start
                newElem[-5] = *oldElem;

                // Process second word (pointer) via copy/move function
                copy_element_member(oldElem + 1); // FUN_004d3b50

                // Copy remaining fields:
                // +0x14: word 5
                // +0x18: word 6
                // +0x1C: word 7
                // +0x20: byte 8 (low)
                // +0x0D from element start (byte)
                // +0x24: word 9
                *newElem       = oldElem[5];
                newElem[1]     = oldElem[6];
                newElem[2]     = oldElem[7];
                *(byte*)(newElem + 3) = *(byte*)(oldElem + 8);
                *(byte*)((uint)newElem + 0x0D) = *(byte*)((uint)oldElem + 0x21);
                newElem[4]     = oldElem[9];

                // If old element has a non-null pointer at index 1, call its destructor
                if (oldElem[1] != 0) {
                    (*(void(__thiscall*)(void*))oldElem[4])((void*)oldElem[1]);
                }

                // Advance to next element (10 ints = 0x28 bytes)
                newElem += 10;
            }
        }

        // Free old buffer
        free_memory(data); // FUN_009c8f10

        // Update container state
        data = newBuffer;     // *param_1 = newBuffer
        capacity = newCapacity; // param_1[2] = newCapacity
    }
    return;
}