// FUNC_NAME: EARSHandle::release
// Function at 0x004df650 - Releases internal data and resource pointer for an EARS object handle.
// The handle object contains a pointer to internal data at offset 0.
// Internal data has flags at +0xC and a pointer-to-pointer (resource) at +0x8.
void __fastcall EARSHandle::release(int* param_1) // param_1 = this (pointer to handle)
{
    EARSInternalData* pData = reinterpret_cast<EARSInternalData*>(*param_1); // Dereference handle to get internal data pointer
    if (pData != nullptr) {
        // Clear bit 0 (LSB) and bit 31 (highest bit) of flags
        pData->m_flags &= 0x7FFFFFFE; // +0xC

        // If the "resource allocated" flag (bit 17) is not set, set it and call global release
        if ((pData->m_flags & 0x20000) == 0) { // Check bit 17 (0x20000)
            pData->m_flags |= 0x20000;         // Set bit 17
            FUN_0051b120();                    // Global resource release callback
        }

        // Clear bit 18 (0x40000) from flags
        pData->m_flags &= 0xFFFBFFFF; // +0xC

        // If the resource pointer-to-pointer is non-null, zero out the pointed resource and null the pointer
        if (pData->m_ppResource != nullptr) { // +0x8
            *pData->m_ppResource = nullptr;   // Zero the resource pointer stored externally
            pData->m_ppResource = nullptr;    // Clear the pointer-to-pointer in internal data
        }
    }
}