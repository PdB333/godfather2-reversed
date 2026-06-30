// FUNC_NAME: CallbackManager::registerAndNotify
bool __thiscall CallbackManager::registerAndNotify(void* this, int* callback) {
    // Callback array is at this+0x8, max 5 entries, count at this+0x1c
    uint callbackCount = *(uint*)((int)this + 0x1c);
    if (callbackCount < 5) {
        *(int**)((int)this + 8 + callbackCount * 4) = callback;
        (*(uint*)((int)this + 0x1c))++; // increment count
    }

    // Get the subject pointer (double indirection from this+0x20)
    int* subject = **(int***)((int)this + 0x20); // subject is an object with vtable

    // Call callback's virtual function at vtable+0x14 (likely returns an ID or value)
    typedef int (__thiscall* CallbackGetValue)(void*);
    int callbackValue = ((CallbackGetValue)(*(int**)(callback))[0x14 / 4])(callback);

    // Notify subject by calling its virtual function at vtable+0x30 with the value
    typedef void (__thiscall* SubjectHandler)(void*, int);
    ((SubjectHandler)(*(int**)subject)[0x30 / 4])(subject, callbackValue);

    // Return true if there was room to register the callback (count < 5)
    return callbackCount < 5;
}