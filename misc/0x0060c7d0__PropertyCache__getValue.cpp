// FUNC_NAME: PropertyCache::getValue

// Address: 0x0060c7d0
// This function returns a 32-bit value from an object that caches a property.
// It checks a dirty flag (byte at +0x28). If set, it calls virtual method index 13
// on an inner object (pointed to by +0x00) to compute the value, which is placed
// in a 12-byte stack buffer, and returns the last 4 bytes (offset +8 in buffer).
// Otherwise, it returns the cached value at +0x20.

uint32_t PropertyCache::getValue(void) __thiscall
{
    // In_EAX is this pointer (PropertyCache*)
    // Offsets:
    // +0x00: pointer to inner object (e.g., IPropertyComputer*)
    // +0x10: (unused in this function)
    // +0x20: cached value (uint32_t)
    // +0x28: dirty flag (byte)
    uint32_t* thisPtr = reinterpret_cast<uint32_t*>(this);
    bool isDirty = (*(char*)(thisPtr + 0x28 / 4)) != 0; // offset 0x28

    if (isDirty)
    {
        uint8_t buffer[12]; // local_14[8] and uStack_c combined
        uint32_t* inner = reinterpret_cast<uint32_t*>(*thisPtr); // +0x00: inner object pointer

        // inner object's vtable at offset 0, function at vtable+0x34 (index 13)
        // Call (inner->vtable[13])(inner, buffer)
        typedef void (__thiscall* VirtualMethod)(uint32_t*, uint8_t*);
        VirtualMethod func = *(VirtualMethod*)(*(uint32_t*)inner + 0x34);
        func(inner, buffer);

        // Return the second 4-byte part of the buffer (offset 8)
        return *(uint32_t*)(buffer + 8);
    }
    else
    {
        // Return cached value at offset 0x20
        return thisPtr[0x20 / 4]; // *(uint32_t*)(this + 0x20)
    }
}