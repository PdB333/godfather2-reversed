// FUNC_NAME: SomeManager::shutdown
void __thiscall SomeManager::shutdown(SomeManager *this) {
    uint32_t index = 0;
    // +0x00: vtable pointer (initial)
    this->vtable = &PTR_FUN_00e316d8;
    // +0x04: secondary vtable or interface pointer
    this->field_4 = &PTR_LAB_00e316dc;

    // +0x14: count of items in the array at +0x10
    if (this->count != 0) {
        do {
            // +0x10: array of pointers to child objects
            SomeObject *obj = this->objects[index];
            if (obj != nullptr) {
                // Call the vtable method at offset 0 with argument 1 (likely release/destroy)
                obj->vtable->method0(1);
            }
            index++;
        } while (index < this->count);
    }

    // Free two static global data structures
    operatorDelete(&DAT_0120e960);  // some static buffer
    operatorDelete(&DAT_0120e970);  // some static buffer

    // Free the array itself
    if (this->objects != nullptr) {
        freeArray(this->objects);
    }

    // Base cleanup
    baseShutdown();

    // Set new vtable (possibly to a stub or null class)
    this->vtable = &PTR_LAB_00e316ec;

    // Global shutdown flag
    g_shutdownFlag = 0;
}