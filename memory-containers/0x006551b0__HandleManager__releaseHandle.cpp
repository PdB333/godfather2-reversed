// FUNC_NAME: HandleManager::releaseHandle
void HandleManager::releaseHandle(short* key) {
    // this = edi, array of pointers at +0x2c, count at +0x24
    // key: [0]=short, [1]=short, then ints at offsets 2,4,6,8 (in short* units)
    int index = 0;
    if (this->count > 0) {
        int* currentPtr = this->objectArray; // +0x2c
        while (true) {
            int obj = *currentPtr; // object pointer
            // compare key fields at offset 0x100 in the object
            if (key[0] == *(short*)(obj + 0x100) &&
                key[1] == *(short*)(obj + 0x102) &&
                *(int*)(key + 2) == *(int*)(obj + 0x104) &&
                *(int*)(key + 4) == *(int*)(obj + 0x108) &&
                *(int*)(key + 6) == *(int*)(obj + 0x10c) &&
                *(int*)(key + 8) == *(int*)(obj + 0x110)) {
                // found
                break;
            }
            index++;
            currentPtr++;
            if (index >= this->count) {
                return;
            }
        }
        // found object at index
        int* foundObj = this->objectArray[index];
        int* refCountPtr = foundObj + 2; // +8 bytes: reference count
        (*refCountPtr)--;
        if (*refCountPtr == 0) {
            // call virtual destructor at vtable+8 (third function)
            void (*destructor)(void*) = *(void(**)(void*))*foundObj + 8;
            destructor(foundObj);
        }
        // remove entry by shifting array
        if (index < this->count - 1) {
            do {
                this->objectArray[index] = this->objectArray[index + 1];
                index++;
            } while (index < this->count - 1);
        }
        this->count--;
    }
}