//FUNC_NAME: BaseManager::destructor
void __thiscall BaseManager::destructor() {
    // Set vtable pointers to intermediate destructor vtables
    this->vtable = &PTR_FUN_00e3a574;          // +0x00
    this->vtable2 = &PTR_FUN_00e3a58c;         // +0x04

    // Release sub-object at offset 0x20
    if (this->subObject != nullptr) {          // +0x20
        FUN_00569500();                         // Pre-release cleanup
        if (this->subObject != nullptr) {
            // Call release method on sub-object with argument 1
            this->subObject->vtable->release(1);
        }
        this->subObject = nullptr;
    }

    // Release resource handle at offset 0x128
    if (this->resourceHandle != 0) {           // +0x128
        FUN_009c8eb0(this->resourceHandle);     // Free resource
        this->resourceHandle = 0;
    }

    // Set vtable to fully destructed state
    this->vtable = &PTR_LAB_00e3a598;          // +0x00

    // Clear global singleton flag
    DAT_012233c0 = 0;
}