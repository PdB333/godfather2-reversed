// FUNC_NAME: Entity::assignCoreData
// Function at 0x006016e0: Copies three core dwords from source to this, with cleanup and flag setting.

void __thiscall Entity::assignCoreData(Entity *this, Entity *other)
{
    // Check if pointer at offset +0x118 (0x46*4) is non-null and points to allocated memory
    uint32_t **ppBuffer = reinterpret_cast<uint32_t **>(reinterpret_cast<uint8_t *>(this) + 0x118);
    if (this->field_0x118 != 0 && *ppBuffer != 0)
    {
        // Release previous buffer
        releaseMemory(*ppBuffer);  // FUN_004daf90
        *ppBuffer = 0;
    }

    // Clear flag field at +0xB0
    this->field_0xB0 = 0;

    // Set flag bit 0 at +0xB4
    this->field_0xB4 |= 1;

    // Three calls to global update/release function (maybe decrement ref counts)
    doSomething();  // FUN_005f5ce0
    doSomething();  // FUN_005f5ce0
    doSomething();  // FUN_005f5ce0

    // Copy three core dwords (first three fields) from source
    this->field_0x00 = other->field_0x00;
    this->field_0x04 = other->field_0x04;
    this->field_0x08 = other->field_0x08;

    // Zero out field at +0x40
    this->field_0x40 = 0;
}