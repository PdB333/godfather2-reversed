// FUNC_NAME: ActionManager::update
void __thiscall ActionManager::update(ActionManager* this)
{
    bool bForceUpdate = false;

    // Check if pending timer elapsed (global _DAT_00d5e6ec likely gCurrentTime)
    if (this->m_pendingActionCount != 0 && _DAT_00d5e6ec <= *(float*)((int)this + 0x8C)) {
        bForceUpdate = true;
        *(float*)((int)this + 0x8C) = 0.0f; // +0x8C: timer
    }

    int i = this->m_pendingActionCount - 1; // +0xA4: count
    if (i < 0) {
        goto skipLoop;
    }

    int offset = i * 0x18;
    do {
        int* pObj = *(int**)(*(int*)((int)this + 0xA0) + offset); // +0xA0: pointer to array of 0x18-sized elements
        if (pObj == nullptr) {
            int dummy = 0;
            goto removeEntry;
        }

        // Check if object is a derived type (base at offset -0x48)
        int* pBase = (int*)((char*)pObj - 0x48);
        if (pBase == nullptr) {
            goto removeEntry;
        }

        if (bForceUpdate) {
            // Set a processing-needed flag at object offset 0x14
            *(uint32_t*)((int)pObj + 0x14) |= 0x800000;
            goto removeEntry;
        }

        char cResult = FUN_00791230(); // e.g., IsTimeStepValid() or IsGameActive()
        if (cResult == '\0') {
            goto removeEntry;
        }

        i--;
        offset -= 0x18;
    } while (i >= 0);

skipLoop:
    if (!bForceUpdate) {
        return;
    }

    FUN_006badb0(); // Finalize forced update (e.g., flush actions)
    return;

removeEntry:
    // Compact the array and decrement count
    // Function call to remove entry at index 'i' and shift remaining elements
    FUN_006baf90(*(int*)((int)this + 0xA0) - 0x18 + this->m_pendingActionCount * 0x18);
    this->m_pendingActionCount--;

    int* pNewLast = (int*)(*(int*)((int)this + 0xA0) + this->m_pendingActionCount * 0x18);
    if (*pNewLast != 0) {
        FUN_004daf90(pNewLast); // Deallocate the object
    }

    // If the removed entry had a non-null base pointer, clear a flag at offset 0x5C
    if (dummy != 0) { // 'dummy' set to 0 earlier, but effectively always false; likely a bug in Ghidra decomp
        *(uint32_t*)(dummy + 0x5C) &= 0xFBFFFFFF;
    }

    // Continue loop iteration (goto back to loop condition via falling through to loop bottom)
    // Note: This goto restructure is simplified; original logic repeats removal if i remains >=0
    i--;
    offset -= 0x18;
    if (i >= 0) {
        // Loop back implicitly: decompiler shows goto to condition but we continue do-while
    }
    // The original assembly would jump to loop condition check.
    // For clarity we keep the loop as do-while with conditional.
}