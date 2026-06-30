// FUNC_NAME: Entity::resetAndCopyFrom
void __thiscall Entity::resetAndCopyFrom(Entity *this, Entity *source) {
    // +0x118 (0x46 * 4): pointer to some allocated object
    int **ppAllocated = reinterpret_cast<int **>(reinterpret_cast<uint8_t *>(this) + 0x118);
    if (this->field_0x118 != 0 && *ppAllocated != nullptr) {
        // Release the pointed object
        FUN_004daf90(*ppAllocated);
        *ppAllocated = nullptr;
    }

    // +0xB0: clear field
    this->field_0xB0 = 0;
    // +0xB4: set bit 0 (flags)
    this->field_0xB4 |= 1;

    // Three calls to a global function (likely singleton getter or reference count)
    FUN_005f5ce0();
    FUN_005f5ce0();
    FUN_005f5ce0();

    // Copy first three DWORDs from source (likely identity/class data)
    this->field_0x00 = source->field_0x00;
    this->field_0x04 = source->field_0x04;
    this->field_0x08 = source->field_0x08;

    // +0x40: clear a byte (e.g., a bool flag)
    *reinterpret_cast<char *>(reinterpret_cast<uint8_t *>(this) + 0x40) = 0;
}