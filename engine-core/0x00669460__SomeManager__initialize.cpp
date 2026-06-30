// FUNC_NAME: SomeManager::initialize
struct SomeManager {
    int m_state;            // +0x00: some count/state
    int m_pad4;             // +0x04: unused?
    int m_initialized;      // +0x08: flag (0 = not initialized, 1 = initialized)
    uint* m_ptrCount;       // +0x0C: pointer to a count used in precondition check
};

// Returns 0 on success, -2 on alloc failure, -3 if already initialized or invalid state
int SomeManager::initialize(int* outSuccess)
{
    *outSuccess = 0;

    // Precondition: m_initialized must not be 1, and either m_state > 1 or the value pointed by m_ptrCount > 1
    if ((this->m_initialized != 1) && ((this->m_state > 1) || (*(this->m_ptrCount) > 1)))
    {
        // Allocate 256 bytes (4 * 0x40) – likely for a subcomponent array
        void* buffer = _calloc(4, 0x40);
        if (buffer == 0)
        {
            return -2; // out of memory
        }

        int result = FUN_00666ae0(); // internal subcomponent initialization
        if (result == 0)
        {
            // If this is a fresh initialization (m_initialized == 0), call another init routine
            if (this->m_initialized == 0)
            {
                int subResult = FUN_00665c30();
                if (subResult == 0)
                {
                    *outSuccess = 1;
                }
            }
            result = 0;
        }

        FUN_00665b40(); // tear-down or cleanup routine (called unconditionally after setup)
        return result;
    }

    return -3; // precondition failed
}