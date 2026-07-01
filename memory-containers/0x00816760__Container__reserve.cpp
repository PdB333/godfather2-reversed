// FUNC_NAME: Container::reserve
void __thiscall Container::reserve(int *this, uint newCapacity) {
    int iVar1;
    undefined8 *newBuffer;
    int iVar3;
    uint index;
    undefined8 *oldBuffer;

    // If current capacity < new capacity, reallocate
    if ((uint)this[2] < newCapacity) {
        // Allocate new buffer: newCapacity * 16 bytes
        newBuffer = (undefined8 *)allocateMemory(newCapacity << 4);
        
        if (this[0] != 0) {
            index = 0;
            if (this[1] != 0) {
                iVar3 = 0;
                oldBuffer = newBuffer;
                do {
                    // Copy element (16 bytes) from old buffer to new
                    iVar1 = this[0];
                    if (oldBuffer != (undefined8 *)0x0) {
                        *oldBuffer = *(undefined8 *)(iVar1 + iVar3);
                        oldBuffer[1] = ((undefined8 *)(iVar1 + iVar3))[1];
                    }
                    // Call copy constructor / assignment for element
                    copyElement();
                    index = index + 1;
                    iVar3 = iVar3 + 0x10; // next element (16 bytes)
                    oldBuffer = oldBuffer + 2; // move by 2 undefined8 (16 bytes)
                } while (index < (uint)this[1]);
            }
            // Free old buffer
            freeMemory(this[0]);
        }
        // Update container metadata
        this[0] = (int)newBuffer;
        this[2] = newCapacity;
    }
}