// FUNC_NAME: CNetworkManager::~CNetworkManager
// Address: 0x004d0160
// Destructor for a manager class with two critical sections (used for thread-safe internal state) and a dynamically allocated pointer.
// The global DAT_012234a8 is reset to 0 upon destruction, indicating this is likely a singleton.

CNetworkManager::~CNetworkManager(uint8_t freeMemory)
{
    // Delete critical sections at offsets +0x40 and +0x68 (byte offsets from this)
    DeleteCriticalSection((LPCRITICAL_SECTION)((uint8_t*)this + 0x40));   // +0x10 * 4
    DeleteCriticalSection((LPCRITICAL_SECTION)((uint8_t*)this + 0x68));   // +0x1A * 4

    // Free the pointer stored at offset +0x18 (6 * 4 bytes)
    if (m_pData != nullptr)
    {
        __FreeObject(m_pData);  // FUN_009c8f10
        m_pData = nullptr;
    }

    // Reset vtable pointer to base class vtable (destructor chain)
    *(void**)this = (void*)&g_pBaseVtable;  // PTR_LAB_00e36cc4

    // Clear global singleton flag
    g_bNetworkManagerInitialized = 0;  // DAT_012234a8

    // If requested, free the object's own memory (destructor delete)
    if (freeMemory & 1)
    {
        __DeleteMemory(this);  // FUN_009c8eb0
    }
}