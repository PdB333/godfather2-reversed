// FUNC_NAME: EARSObject::getPointerAtOffset18
uint32_t __fastcall EARSObject::getPointerAtOffset18(void* thisPtr) {
    // Returns the 4-byte value stored at offset +0x18 from the object's base.
    // Commonly used as a generic accessor for a pointer field (e.g., m_pData, m_pInternal).
    return *(uint32_t*)((uint8_t*)thisPtr + 0x18);
}