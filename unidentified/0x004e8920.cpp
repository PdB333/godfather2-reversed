// FUN_004e8920: RefCountObject::releaseAndCheck
bool __fastcall RefCountedObject::releaseAndCheck(void* unusedParam, int checkParam, RefCountedObject* obj) {
    // param_1 (ECX) is unused
    // param_2 (EDX) = checkParam – argument to virtual check function
    // param_3 (stack) = obj – pointer to ref-counted object with vtable and refCount at +4
    int localZero = 0; // used as a non-null sentinel (returned as a pointer if condition true)

    if (obj != nullptr) {
        // Call virtual function at vtable+8 (third virtual method, returns bool)
        bool checkResult = obj->vtable[2](checkParam);
        if (checkResult) {
            obj->refCount--;
            if (obj->refCount == 0) {
                obj->vtable[1](); // virtual destructor at vtable+4 (second virtual method)
            }
            return true; // (returning address of localZero, interpreted as non-null)
        }
        obj->refCount--;
        if (obj->refCount == 0) {
            obj->vtable[1]();
        }
    }
    return false; // null pointer
}