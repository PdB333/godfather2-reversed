// FUNC_NAME: Object::destroy
// Function address: 0x00567030
// Role: Object destructor/cleanup method. Releases callbacks, unregisters from global manager, and releases a sub-object.

void __thiscall Object::destroy(void) {
    // If there is a cleanup callback at offset +0x58, invoke it with 0 (likely "context" or "reason")
    if (this->cleanupCallback != nullptr) {
        this->cleanupCallback(0);
    }

    // If the global manager (DAT_012234e0) exists, call its virtual method at vtable offset 0xC (likely unregister/release)
    if (gManager != nullptr) {
        // gManager points to a struct/class with a vtable; offset 0xC is a member function taking no args
        reinterpret_cast<void (*)()>(gManager->vtable[0xC / 4])();
    }

    // If there is a sub-object pointer at offset +0xC, call its virtual method at vtable offset 4 (e.g., release)
    // passing 'this' as argument, then clear the pointer.
    if (this->subObject != nullptr) {
        // subObject points to an object with a vtable; offset 4 is a member function taking an argument
        reinterpret_cast<void (__thiscall*)(void*)>(this->subObject->vtable[0x4 / 4])(this->subObject);
        this->subObject = nullptr;
    }

    // Mark the object as destroyed (offset +0x14)
    this->destroyed = 1;
}