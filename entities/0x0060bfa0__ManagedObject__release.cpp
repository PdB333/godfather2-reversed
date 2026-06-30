// FUNC_NAME: ManagedObject::release

// Function address: 0x0060bfa0
// Destructor/cleanup method for ManagedObject which holds two pointers.
// When the managed inner object is the current active object, it clears the global and notifies the manager.
// Then releases the inner object via vtable[2] (offset 8) and handles a second pointer via a resource manager.

void ManagedObject::release()
{
    // Global managers (externals, from data segment)
    extern void* g_pManager;             // DAT_01205750
    extern void* g_pCurrentObject;       // DAT_0120583c
    extern void* g_pResourceManager;     // DAT_01205868

    // Class layout (based on this function):
    // offset 0: pointer to inner object (m_pInner)
    // offset 4: pointer to secondary object (m_pSecondary)
    // The inner object has a vtable at first DWORD.

    // Check if the inner object is the current global active one
    if ( (g_pManager != nullptr) && (this->m_pInner != nullptr) && (this->m_pInner == g_pCurrentObject) )
    {
        g_pCurrentObject = nullptr;
        // Call manager's unregister function (vtable offset 0x1a0 / 0x68 in vtable indices? but on 32-bit, offset 0x1a0 = 0x68*4? Actually pointer size is 4, so offset 0x1a0 / 4 = 104th function? Possibly a RemoveActive or similar)
        ((void (*)(void*, int))((*reinterpret_cast<int**>(g_pManager))[0x68]))(g_pManager, 0);
    }

    // Release inner object: call its virtual destructor/release at vtable offset 8
    ((void (*)(void*))((*reinterpret_cast<int**>(this->m_pInner))[2]))(this->m_pInner);

    // Handle secondary pointer
    if (this->m_pSecondary != nullptr)
    {
        if (g_pResourceManager != nullptr)
        {
            // Call resource manager's release/dec ref at vtable offset 4
            ((void (*)(void*, int))((*reinterpret_cast<int**>(g_pResourceManager))[1]))(this->m_pSecondary, 0);
        }
        // If the secondary pointer is not the same as 'this', clear the field
        if (this != this->m_pSecondary)
        {
            this->m_pSecondary = nullptr;
        }
    }
    return;
}