// FUN_NAME: ActionNodeArray::operator=
int* __thiscall ActionNodeArray::operator=(ActionNodeArray* other) {
    // Deep copy assignment for dynamic array of 0x34-byte elements with three owned pointer sub-objects
    // Each element: 3 int fields (offset 0x00, 0x04, 0x08), then a pointer at +0x0c, +0x18, +0x24, and a final int at +0x30
    if (this == other) {
        return this;
    }

    // Destroy current elements (iterate from count-1 down to 0)
    int oldIdx = this->size - 1; // size at offset 4
    if (oldIdx >= 0) {
        int byteOffset = oldIdx * 0x34;
        do {
            int* elemBase = this->arrayPtr + byteOffset; // arrayPtr at offset 0

            // Free owned pointers at offsets 0x24, 0x18, 0x0c
            int* ptr = (int*)elemBase[9]; // offset 0x24 / 4 = 9
            if (ptr != 0) {
                destroyDynamicObject(ptr); // FUN_009c8f10
            }
            ptr = (int*)elemBase[6]; // offset 0x18 / 4 = 6
            if (ptr != 0) {
                destroyDynamicObject(ptr);
            }
            ptr = (int*)elemBase[3]; // offset 0x0c / 4 = 3
            if (ptr != 0) {
                destroyDynamicObject(ptr);
            }

            oldIdx--;
            byteOffset -= 0x34;
        } while (oldIdx >= 0);
    }

    // Reallocate if current capacity < other's size
    if ((unsigned int)this->capacity < (unsigned int)other->size) {
        destroyDynamicObject(this->arrayPtr); // free old array
        this->capacity = other->size; // capacity at offset 8
        if (this->capacity == 0) {
            this->arrayPtr = 0;
        } else {
            this->arrayPtr = (int*)allocateMemory(this->capacity * 0x34); // FUN_009c8e80
        }
    }

    // Copy elements from other
    unsigned int i = 0;
    if (other->size != 0) {
        int srcOffset = 0;
        do {
            int* dest = this->arrayPtr + srcOffset;
            if (dest != 0) {
                int* src = other->arrayPtr + srcOffset;

                // Shallow copy first 12 bytes (3 ints)
                dest[0] = src[0];
                dest[1] = src[1];
                dest[2] = src[2];

                // Deep copy owned pointers at +0x0c, +0x18, +0x24
                copyDynamicObject(&dest[3]); // FUN_00498500 on &(elem.+0x0c)
                copyDynamicObject(&dest[6]); // +0x18
                copyDynamicObject(&dest[9]); // +0x24

                // Copy final int at +0x30
                dest[12] = src[12];
            }
            i++;
            srcOffset += 0x34;
        } while (i < (unsigned int)other->size);
    }

    this->size = other->size; // size at offset 4
    return this;
}