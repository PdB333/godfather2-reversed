// FUNC_NAME: UnknownObject::~UnknownObject

void __thiscall UnknownObject::~UnknownObject(UnknownObject* this) {
    // Set vtable to a default/clean vtable pointer
    *(void**)this = (void*)0x00d60a08;  // PTR_FUN_00d60a08

    // Free allocated memory at offset +0x0C (likely a buffer or child object)
    if (this->field_0C != nullptr) {
        FUN_004035f0(this->field_0C, 0x1ff, this);  // Custom deallocation with size 0x1ff and 'this' as context
    }

    // Perform additional cleanup (e.g., release resources, unregister from manager)
    FUN_006bcc90();

    // Call custom destructor function pointer for member at offset +0x10 (e.g., a script or callback)
    if (this->field_10 != nullptr) {
        // Function pointer at offset +0x1C
        ((void(__thiscall*)(void*))this->field_1C)(this->field_10);
    }

    // Final cleanup (e.g., decrement reference counts, notify listeners)
    FUN_004083d0();

    return;
}