// FUNC_NAME: DialogManager::handleUnsuppressAll
// Reconstructed C++ for function at 0x0093af20
// Clears suppression flags and potentially triggers immediate unsuppress or deferred completion.

void __thiscall DialogManager::handleUnsuppressAll(DialogManager *this, bool bWaitForUnsuspend)
{
    // Clear bit 10 (0x400) of suppression flags – likely "suppressAll" flag
    this->m_suppressionFlags &= ~0x400;

    if (!bWaitForUnsuspend) {
        // Immediate unsuppress path
        this->unsuppressAllImmediate(); // FUN_0093a2f0
    } else {
        // Deferred unsuppress path: clear bit 30 (0x40000000)
        this->m_suppressionFlags &= ~0x40000000;

        // Call debug/log print with string "UnSuppressAll"
        // FUN_005a04a0: likely debugPrint(const char*, int, const char*, int)
        debugPrint("UnSuppressAll", 0, (const char*)&DAT_00d8a64c, 0);

        // Check if pending unsuppress count is zero and specific flags are clear
        if (this->m_pendingUnsuppressCount == 0 && 
            (this->m_suppressionFlags & 0x40000008) == 0) {
            // Trigger completion of unsuppress (e.g., resume audio/dialog)
            this->completeUnsuppress(); // FUN_005c1b40
        }
    }
}