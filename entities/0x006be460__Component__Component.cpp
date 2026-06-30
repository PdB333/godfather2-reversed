// FUNC_NAME: Component::Component

// 0x006be460 - Constructor for a component class with size 0x74 (116 bytes)
// param_1: this pointer
// param_2: flags byte (bit 0 indicates dynamic allocation from new)
void* __thiscall Component::Component(void* this, byte flags) {
    // Call base class initializer (sets vtable, zeroes fields, etc.)
    this->initBase(); // FUN_006be230

    // If the object was newly allocated with operator new(size=0x74),
    // immediately deallocate it. This may be an error-handling pattern
    // (e.g., if initBase failed and we must free allocated memory),
    // but as written it always runs after initBase.
    if (flags & 1) {
        operator delete(this, 0x74); // FUN_0043b960 - size matches class
    }

    return this;
}