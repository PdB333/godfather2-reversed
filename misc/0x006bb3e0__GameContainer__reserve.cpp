// FUNC_NAME: GameContainer::reserve
// Address: 0x006BB3E0
// Description: Resizes the container's internal buffer to accommodate at least 'newCapacity' elements.
// Each element is 24 bytes (0x18). The buffer stores elements with embedded linked list pointers.
// On resize, elements are relocated and old buffer freed.

void __thiscall GameContainer::reserve(GameContainer* this, uint newCapacity)
{
    int* newBuffer;
    int iVar1;
    int* oldElementPtr;
    uint i;
    int* newElementPtr;

    // Only resizes if current capacity is less than requested
    if ((uint)this->capacity < newCapacity) {
        // Allocate new buffer (likely zeroed) for newCapacity elements of 24 bytes each
        newBuffer = (int*)Memory::allocate(newCapacity * 0x18); // FUN_009c8e80 assumed to allocate zeroed memory

        // If there's an existing buffer and elements to copy
        if (this->buffer != nullptr) {
            if (this->count != 0) {
                // Start of new buffer + offset to first element's data (skips 4 ints header? Actually newBuffer+0x10)
                // The new buffer layout: each element occupies 6 ints (24 bytes), first four ints are metadata/pointers
                newElementPtr = newBuffer + 4; // +0x10 in bytes
                i = 0;
                do {
                    // Compute pointer to old element corresponding to this new element position
                    // oldElementPtr = newElementPtr + oldBuffer - newBuffer - 0x10
                    oldElementPtr = (int*)((int)newElementPtr + (int)this->buffer - 0x10 - (int)newBuffer);
                    // Only copy if we're past the initial header (newElementPtr != 0x10? This is a check for first element)
                    // Actually the condition checks if newElementPtr is not equal to (int*)0x10 i.e., not the first element? Weird.
                    // Possibly a guard against copying header data.
                    if (newElementPtr != (int*)0x10) {
                        // Copy the element's next pointer
                        iVar1 = *oldElementPtr;
                        newElementPtr[-4] = iVar1;          // +0x00: "next" pointer
                        newElementPtr[-3] = 0;              // +0x04: some field initialized to 0
                        if (iVar1 != 0) {
                            newElementPtr[-3] = *(int*)(iVar1 + 4); // copy data from next node's +0x04
                            *(int**)(iVar1 + 4) = newElementPtr - 4; // update prev pointer of next node
                        }
                        // Copy remaining fields (4 ints = 16 bytes)
                        newElementPtr[-2] = oldElementPtr[2]; // +0x08
                        newElementPtr[-1] = oldElementPtr[3]; // +0x0C
                        *newElementPtr = oldElementPtr[4];    // +0x10
                        newElementPtr[1] = oldElementPtr[5];  // +0x14
                    }
                    // Run cleanup/destructor on old element (if it has a non-null pointer in first field)
                    if (*oldElementPtr != 0) {
                        Element::release((Element*)oldElementPtr); // FUN_004daf90
                    }
                    i++;
                    newElementPtr += 6; // move to next element (6 ints)
                } while (i < (uint)this->count);
            }
            // Free old buffer
            Memory::free(this->buffer); // FUN_009c8f10
        }
        // Update buffer pointer and capacity
        this->buffer = newBuffer;
        this->capacity = newCapacity;
    }
    return;
}