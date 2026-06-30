// FUNC_NAME: Delegate::bind
void __thiscall Delegate::bind(uint32_t *initData)
{
    uint32_t *buffer = *(uint32_t **)(this + 4); // +0x4: preallocated buffer or null
    uint32_t local_c; // unused? 
    uint32_t local_8; // unused?
    uint32_t local_4; // type/flag

    if (buffer == nullptr)
    {
        local_c = 0;
        local_8 = 0;
        local_4 = 0;
        buffer = &local_c; // use stack fallback
    }

    // Virtual call: vtable[0] is likely "allocate" or "createHandle"
    // Takes size (0xc = 12 bytes) and a hint buffer.
    uint32_t *allocated = (uint32_t *)(*(code **)*this)(0xc, buffer); 

    if (allocated != nullptr)
    {
        *allocated = local_4; // type or flag
    }
    if (allocated + 1 != nullptr)
    {
        allocated[1] = _returnAddress; // stored return address (caller's EIP)
    }
    if (allocated + 2 != nullptr)
    {
        allocated[2] = *initData; // first word of initialization data
    }
    return;
}