// FUNC_NAME: GrowingArray::reserve
void __thiscall GrowingArray::reserve(int* this, uint newCapacity) {
    void* allocator;
    int* newData;
    uint elementSize = 0x14; // 20 bytes per element (5 ints)
    uint i;

    // check if current capacity is insufficient
    if ((uint)this[2] < newCapacity) {
        // get allocator (use default if null)
        allocator = (void*)this[3];
        if (allocator == nullptr) {
            allocator = (void*)0x01218a14; // default allocator
        }
        // allocate new block via vtable[0] (allocate function)
        newData = (int*)((*(int*(__thiscall**)(void*, uint))this[4])(allocator, newCapacity * elementSize));

        if (this[0] != 0) {
            i = 0;
            if (this[1] != 0) {
                // copy existing elements from old buffer to new
                int* dest = newData; // destination start
                int* src = (int*)this[0]; // source start
                do {
                    // copy 5 integers (20 bytes) per element
                    dest[0] = src[0];
                    dest[1] = src[1];
                    dest[2] = src[2];
                    dest[3] = src[3];
                    dest[4] = src[4];
                    i++;
                    dest += 5;
                    src += 5;
                } while (i < (uint)this[1]);
            }
            // free old buffer via vtable[1] (free function)
            (**(void(__thiscall**)(int*))((int*)this[4] + 4))(this[0]);
        }
        // update pointers and capacity
        this[0] = (int)newData;
        this[2] = newCapacity; // store the requested capacity (original value preserved)
    }
}