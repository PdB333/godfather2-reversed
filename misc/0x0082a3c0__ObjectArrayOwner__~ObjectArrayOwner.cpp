// FUNC_NAME: ObjectArrayOwner::~ObjectArrayOwner
void __fastcall ObjectArrayOwner::~ObjectArrayOwner(undefined4 *this)
{
    // Set vtable pointer to this class's vtable (offset +0x00)
    *this = &PTR_FUN_00d7378c;

    // Destroy all owned objects in the array
    uint count = this[3]; // +0x0C: number of objects
    if (count != 0) {
        uint index = 0;
        do {
            // +0x08: pointer to array of object pointers
            undefined4 *objectPtr = *(undefined4 **)(this[2] + index * 4);
            if (objectPtr != nullptr) {
                // Call scalar deleting destructor (vtable[0] with flag 1)
                delete objectPtr;
            }
            index++;
        } while (index < count);
    }

    // Free the array memory
    if (this[2] != 0) {
        FUN_009c8f10(this[2]); // likely operator delete[] or custom dealloc
    }
}