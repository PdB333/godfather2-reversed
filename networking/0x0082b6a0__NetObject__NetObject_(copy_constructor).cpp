// FUNC_NAME: NetObject::NetObject (copy constructor)
NetObject::NetObject(const NetObject& other)
{
    // Call base class initialization (FUN_0081f9f0)
    // This likely initializes base class members from the source object
    someBaseFunction(&other);

    // Set vtable pointer to class-specific vtable
    // +0x00: vtable pointer
    this->vtable = &NetObject_vtable; // PTR_LAB_00d7377c

    // Copy 8 bytes at offset 0x4C (likely a 64-bit field like GUID or timestamp)
    // +0x4C: field1 (uint64_t)
    *(uint64_t*)((uint8_t*)this + 0x4C) = *(uint64_t*)((uint8_t*)&other + 0x4C);

    // Copy 8 bytes at offset 0x54 (another 64-bit field)
    // +0x54: field2 (uint64_t)
    *(uint64_t*)((uint8_t*)this + 0x54) = *(uint64_t*)((uint8_t*)&other + 0x54);

    // Copy 4 bytes at offset 0x5C (a 32-bit field)
    // +0x5C: field3 (uint32_t)
    *(uint32_t*)((uint8_t*)this + 0x5C) = *(uint32_t*)((uint8_t*)&other + 0x5C);
}