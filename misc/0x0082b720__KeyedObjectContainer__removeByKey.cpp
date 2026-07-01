// FUNC_NAME: KeyedObjectContainer::removeByKey
// Reconstructed from address 0x0082b720
// Purpose: Remove an object from a dynamic array by matching a 4-integer key (offsets 0x1c,0x20,0x24,0x28)
// Struct offsets: this+0x0 = vtable? (not used here), this+0x8 = pointer to array of object pointers, this+0xc = count
// Object fields: +0x1c, +0x20, +0x24, +0x28 = key elements (4 ints)

int __thiscall KeyedObjectContainer::removeByKey(void* thisPtr, int* key) {
    uint count = *(uint*)((char*)thisPtr + 0xc);
    uint index = 0;
    if (count != 0) {
        int** array = *(int***)((char*)thisPtr + 0x8);
        do {
            int* object = *array;
            if ( // Match all 4 key ints
                *(int*)(object + 7) == *key &&       // +0x1c
                *(int*)(object + 8) == key[1] &&     // +0x20
                *(int*)(object + 9) == key[2] &&     // +0x24
                *(int*)(object + 10) == key[3]       // +0x28
               )
            {
                if (index < count - 1) {
                    // Shift remaining elements left
                    do {
                        *(int**)(*(int*)((char*)thisPtr + 0x8) + index * 4) =
                            *(int**)(*(int*)((char*)thisPtr + 0x8) + 4 + index * 4);
                        index = index + 1;
                    } while (index < *(int*)((char*)thisPtr + 0xc) - 1U);
                }
                *(int*)((char*)thisPtr + 0xc) = *(int*)((char*)thisPtr + 0xc) - 1;
                return (int)object;
            }
            index = index + 1;
            array = array + 1;
        } while (index < count);
    }
    return 0;
}