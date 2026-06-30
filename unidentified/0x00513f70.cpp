// FUN_NAME: SmartPtr::ConditionalRelease
uint32_t* __fastcall SmartPtr::ConditionalRelease(uint32_t edxDestroy, Object* obj) {
    // Object* obj (param_3) - pointer to reference-counted object with vtable
    // vtable[0] = vtable pointer
    // vtable[4] = destructor (offset 0x4)
    // vtable[8] = some check method (offset 0x8)
    // Object layout: +0x00 vtable ptr, +0x04 refCount (int)

    uint32_t result = 0;
    if (obj != nullptr) {
        // Call vtable[2] with edxDestroy as argument
        bool canProceed = (*(bool (__fastcall**)(uint32_t))(*obj + 8))(edxDestroy);
        if (canProceed) {
            int* refCount = (int*)(obj + 1); // +0x04
            (*refCount)--;
            if (*refCount == 0) {
                (*(void (__fastcall**)())(*obj + 4))(); // destructor
            }
            return (uint32_t*)&result; // non-null pointer to stack variable
        } else {
            int* refCount = (int*)(obj + 1); // +0x04
            (*refCount)--;
            if (*refCount == 0) {
                (*(void (__fastcall**)())(*obj + 4))(); // destructor
            }
        }
    }
    return nullptr;
}