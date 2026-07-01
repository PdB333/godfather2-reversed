// FUNC_NAME: RefCountedObject::release
void __thiscall RefCountedObject::release() {
    // Check if the "released" flag (bit 4) at offset 0xd0 is set
    if ((m_flags & 0x10) != 0) {
        // Clear the flag
        m_flags &= ~0x10;
        // Call some global cleanup/release function on g_someGlobal
        FUN_004086d0(&g_someGlobal);
        // Decrement reference count at offset 0xd4
        m_refCount--;
    }
}