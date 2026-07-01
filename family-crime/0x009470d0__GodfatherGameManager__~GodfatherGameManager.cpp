// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* this)
{
    // +0x00: vtable pointer for this class
    *this = &PTR_FUN_00d8b4cc; // Base class vtable (GodfatherGameManager vtable)
    // +0x3C (offset 0xF)
    this->m_pFunc1 = &PTR_LAB_00d8b4bc;
    // +0x48 (offset 0x12)
    this->m_pFunc2 = &PTR_LAB_00d8b4b8;

    // Destroy 5 sequence-number subobjects (each 2 bytes, likely TSLSequence)
    // The pattern: construct then destruct immediately (reset to default state)
    // Offsets: +0x48, +0x4A, +0x4C, +0x4E, +0x50 (word-aligned)
    sub_004086d0(&this->m_sequence1); // Construct sequence #1
    sub_00408310(&this->m_sequence1); // Destruct sequence #1 (zeros out)

    sub_004086d0(&this->m_sequence2);
    sub_00408310(&this->m_sequence2);

    sub_004086d0(&this->m_sequence3);
    sub_00408310(&this->m_sequence3);

    sub_004086d0(&this->m_sequence4);
    sub_00408310(&this->m_sequence4);

    sub_004086d0(&this->m_sequence5);
    sub_00408310(&this->m_sequence5);

    // +0x50 (offset 0x50) - another sequence? Possibly a global object
    sub_004086d0(&g_globalSequence); // Global object at 0x0120e93c
    sub_00408310(&g_globalSequence);

    // +0x208 (offset 0x52) pointer to some dynamic allocation
    // Check if the singleton manager (g_gameManager) is not yet initialized
    // and if this object still holds a pointer to something
    if ((*(int*)(g_gameManager + 0xC) == 0) && (this->m_pManagedObject != nullptr))
    {
        // Release the managed object
        sub_0094b0e0(this->m_pManagedObject); // Likely operator delete or Release()

        // Set a global flag to prevent recursive cleanup
        bool isCleanupAlreadyRunning = g_isCleanupInProgress;
        this->m_pManagedObject = nullptr;

        if (!isCleanupAlreadyRunning)
        {
            sub_004a8f30(this); // Further cleanup on this object (maybe unregister)
            sub_009473d0();     // Static cleanup routine (e.g., manager shutdown)
        }
    }

    // +0xB4 (offset 0x2D) pointer to another sub-object (e.g., sound system, UI)
    if (this->m_pSubObject != nullptr)
    {
        sub_009c8f10(this->m_pSubObject); // Release second sub-object
    }

    // Global cleanup tick (e.g., frame-end cleanup, memory pool flush)
    sub_0046c640();
}