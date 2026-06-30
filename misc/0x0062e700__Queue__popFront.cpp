// FUNC_NAME: Queue::popFront

int Queue::popFront()
{
    int* pRead = *(int**)(this + 0x0C);                       // +0x0C: read pointer (m_readPtr)
    if ((pRead < *(int**)(this + 0x08)) &&                     // +0x08: write pointer (m_writePtr)
        (pRead != nullptr) && (0 < *pRead)) {                  // element must have positive type
        if ((pRead < *(int**)(this + 0x08)) && (pRead != nullptr)) {
            if (*pRead == 4) {
                // direct object pointer at offset 4 (m_pObj)
                pRead = (int*)(pRead[1] + 0x10);               // m_pObj + 0x10
            } else {
                int cmpResult = validateElement(this);          // compare key? (FUN_00633990)
                if (cmpResult == 0) {
                    pRead = nullptr;                           // invalid element
                } else {
                    pRead = (int*)(pRead[1] + 0x10);           // m_pObj + 0x10
                }
                // Check if the container needs to grow (size >= capacity)
                // Header at +0x10: capacity at +0x20, size at +0x24
                int* header = *(int**)(this + 0x10);           // +0x10: pointer to header
                if (*(uint*)(header + 0x20) <= *(uint*)(header + 0x24)) { // if capacity <= size
                    growBuffer();                              // FUN_00627360
                }
            }
            if (pRead != nullptr) goto LAB_0062e775;
        }
        // Error: no valid element
        reportError("queue empty");                            // FUN_00627ac0
    } else {
        pRead = nullptr;
    }

LAB_0062e775:
    int oldWrite = *(int*)(this + 0x08);                       // save write pointer
    int oldRead  = *(int*)(this + 0x0C);                       // save read pointer
    if (checkValidPointer(pRead) != 0) {                       // FUN_006290c0
        return getErrorCode();                                 // FUN_006338a0
    }
    // Remove the element at the back of the buffer (writePtr - 8)
    removeElementAt(this, *(int*)(this + 0x08) - 8, 0xFFFFFFFF); // FUN_006362d0
    // Return change in element count (after removal vs before)
    return ( (*(int*)(this + 0x08) - *(int*)(this + 0x0C) ) >> 3 ) -
           ( (oldWrite - oldRead) >> 3 );
}