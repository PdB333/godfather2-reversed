// FUNC_NAME: PendingReleaseQueue::~PendingReleaseQueue
void __fastcall PendingReleaseQueue::destructor(PendingReleaseQueue *this)
{
    int head;
    undefined *element;

    this->vtable = &PTR_FUN_00d5d914;                   // +0x00 vtable for current class
    this->baseVtable = &PTR_LAB_00d5d910;                // +0x0C base class vtable (overridden)

    enterCriticalSection(&DAT_01206940);                  // global mutex lock
    registerCleanupCallback(FUN_006a8f10);                // register atexit callback
    beginGlobalCleanup(&DAT_00d5d8e0);                   // start global cleanup sequence

    // Free a single pending object if present
    if (this->m_pPendingObject != 0) {                    // +0x40
        releaseObject(this->m_pPendingObject);            // FUN_005e3c00 (delete)
        this->m_pPendingObject = 0;
        this->field_0x44 = 0;                             // +0x44 (perhaps reference count or tag)
    }

    performIntermediateCleanup();                         // FUN_00ab4e70

    // Flush the circular buffer of pending objects
    head = this->m_elementCount;                          // +0x54 number of elements to process
    while (head != 0) {
        element = *(undefined4 *)(this->m_pElementBuffer + this->m_headIndex * 4); // +0x48,+0x50
        this->m_headIndex = (this->m_headIndex + 1) % this->m_bufferSize;           // +0x4C
        this->m_elementCount = head - 1;
        decrementRefCount(element);                       // FUN_00603210 (release)
        releaseObject(element);                           // FUN_005e3c00 (delete)
        head = this->m_elementCount;
    }

    // Free the buffer itself
    if (this->m_pElementBuffer != 0) {                    // +0x48
        deallocateArray(this->m_pElementBuffer);           // FUN_009c8f10 (operator delete[])
    }

    completeGlobalCleanup();                              // FUN_00ab4d30
    this->baseVtable = &PTR_LAB_00d5d900;                 // +0x0C restore base vtable after cleanup
    g_cleanupFlag = 0;                                    // DAT_01129950
    leaveCriticalSection();                               // FUN_004083d0
}