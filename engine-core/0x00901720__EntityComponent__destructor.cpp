// FUNC_NAME: EntityComponent::destructor

void __thiscall EntityComponent::destructor(void* this) {
    // Offsets in bytes (assuming 4-byte fields)
    // +0x00: vtable pointer (base class)
    // +0x3C: interface vtable 1
    // +0x48: interface vtable 2
    // +0x50: interface vtable 3
    // +0x58: list container 1
    // +0x60: list container 2
    // +0x68: list container 3
    // +0x88: resource pointer (int*)
    // +0x90: some flag/pointer (int)
    // +0x94: flags field (bit 1 indicates resource active)

    uint32_t* vtable = reinterpret_cast<uint32_t*>(this);
    int** resourcePtr = reinterpret_cast<int**>(reinterpret_cast<uint8_t*>(this) + 0x88);
    uint32_t* flags = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x94);

    // Set up inheritance vtables
    vtable[0x00] = 0x00d8195c;       // base vtable
    vtable[0x0f] = 0x00d8194c;       // interface1 vtable
    vtable[0x12] = 0x00d81948;       // interface2 vtable
    vtable[0x14] = 0x00d81940;       // interface3 vtable (actually a function)

    // Check if resource is valid and active
    if (*resourcePtr != nullptr && *resourcePtr != reinterpret_cast<int*>(0x48) &&  // 0x48 = sentinel
        *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x90) != 0 &&
        ((*flags >> 1) & 1) != 0) {
        // Destroy sub-object at +0x50
        FUN_009af080(reinterpret_cast<uint8_t*>(this) + 0x50);
        // Clear resource active flag
        *flags &= ~2;
    }

    // Clean up three internal containers (+0x58, +0x60, +0x68)
    FUN_004086d0(reinterpret_cast<uint8_t*>(this) + 0x58); // destructor / release
    FUN_00408310(reinterpret_cast<uint8_t*>(this) + 0x58); // destructor / release
    FUN_004086d0(reinterpret_cast<uint8_t*>(this) + 0x60); // destructor / release
    FUN_00408310(reinterpret_cast<uint8_t*>(this) + 0x60); // destructor / release
    FUN_00408310(reinterpret_cast<uint8_t*>(this) + 0x68); // destructor / release

    // Release a global object
    FUN_004086d0(&DAT_0120e93c);

    // Release the resource if it wasn't the sentinel
    if (*resourcePtr != nullptr) {
        FUN_004daf90(*resourcePtr);
    }

    // Final cleanup (static function, no args)
    FUN_0046c640();
}