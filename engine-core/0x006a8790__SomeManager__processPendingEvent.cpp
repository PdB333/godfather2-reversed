// FUNC_NAME: SomeManager::processPendingEvent
void SomeManager::processPendingEvent() {
    // param_1 is the 'this' pointer
    int* pThis = reinterpret_cast<int*>(this);
    
    int* pFirst = reinterpret_cast<int*>(pThis[0]); // +0x00: pointer to first object
    int* pSecond = reinterpret_cast<int*>(pThis[2]); // +0x08: pointer to second object

    if (pFirst != nullptr && pSecond != nullptr) {
        // Clear bit 2 (0x04) in the byte at offset 0x21 of the second object
        *(reinterpret_cast<byte*>(pSecond) + 0x21) &= 0xfb;
        
        // Check if bit 1 (0x02) is still set after clearing bit 2
        if ((*(reinterpret_cast<byte*>(pSecond) + 0x21) & 2) != 0) {
            // Call function with first object, second object, and three zeros (likely a command dispatch)
            FUN_006a8100(pFirst, pSecond, 0, 0, 0);
            
            // Access global singleton via DAT_012233a0 (offset 4) to get a pointer
            int* globalPtr = *reinterpret_cast<int**>(DAT_012233a0 + 4);
            if (globalPtr != nullptr && *globalPtr != 0x1f30) {
                // Call debug/log function with a global string and an offset
                FUN_00408c70(&DAT_0112b914, *globalPtr - 0x1ef4, 0);
            }
        }
    }
}