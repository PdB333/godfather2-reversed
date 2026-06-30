// FUNC_NAME: GameObject::processFlags
void __fastcall GameObject::processFlags(GameObject* thisPtr) {
    // Flags byte at offset +0x114
    unsigned char& flags = *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(thisPtr) + 0x114);
    flags &= ~0x01; // Clear bit 0 (flag0)
    if ((flags & 0x02) == 0) {
        flags |= 0x02; // Set bit 1 (flag1)
        FUN_00728070(thisPtr); // Call sub-function for additional processing
    }
}