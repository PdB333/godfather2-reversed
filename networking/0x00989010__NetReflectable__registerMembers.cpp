// FUNC_NAME: NetReflectable::registerMembers
void __thiscall NetReflectable::registerMembers() {
    // Static initialization for the reflection system (e.g., register class descriptor)
    initReflectionSystem();

    // Register each reflected member variable with the network system.
    // Parameters: (memberDescriptor pointer, address of field, size, flags, padding, arrayCount)
    registerMember(&ms_memberDesc0, reinterpret_cast<char*>(this) + 0x54, 1, 0, 0, 1);   // +0x54: 1-byte field (bool/byte)
    registerMember(&ms_memberDesc1, reinterpret_cast<char*>(this) + 0x70, 1, 0, 0, 1);   // +0x70: 1-byte field
    registerMember(&ms_memberDesc2, reinterpret_cast<char*>(this) + 0x74, 5, 0, 0, 1);   // +0x74: 5-byte field (char[5] or struct)
    registerMember(&ms_memberDesc3, reinterpret_cast<char*>(this) + 0xF8, 4, 0, 0, 1);   // +0xF8: 4-byte field (int/float)
    registerMember(&ms_memberDesc4, reinterpret_cast<char*>(this) + 0xFC, 4, 0, 0, 1);   // +0xFC: 4-byte field
    registerMember(&ms_memberDesc5, reinterpret_cast<char*>(this) + 0x60, 1, 0, 0, 1);   // +0x60: 1-byte field
    registerMember(&ms_memberDesc6, reinterpret_cast<char*>(this) + 0x5C, 0, 0, 0, 1);   // +0x5C: zero-sized (bitfield or placeholder)
}