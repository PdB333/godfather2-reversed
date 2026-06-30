// FUNC_NAME: GameObject::initThreeSubObjects

// Function address: 0x00603a90
// This function performs a one-time initialization of three sub-objects (likely components or children).
// It checks a flag at offset 0x4c (bit 1) to avoid double initialization.

void __thiscall GameObject::initThreeSubObjects()
{
    // Flags field at offset 0x4c from this
    uint32_t& flags = *(uint32_t*)((uint8_t*)this + 0x4c);

    // Check if already initialized (bit 1 set)
    if (!(flags & 2)) // 1 << 1
    {
        // Create three sub-objects via helper at 0x00603c50
        createSubObject(this);  // FUN_00603c50
        createSubObject(this);
        createSubObject(this);

        // Mark as initialized
        flags |= 2;
    }
}