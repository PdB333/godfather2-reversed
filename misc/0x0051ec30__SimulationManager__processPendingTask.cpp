// FUNC_NAME: SimulationManager::processPendingTask
// Address: 0x0051ec30
// Loops processing a task for a given slot (index * 32) until a continuation flag becomes false.
// Member at offset 0x37c04 is a pointer to a function pointer (callable with slot offset and result struct).
// Early returns non-zero if the callback returns non-zero.

int __thiscall SimulationManager::processPendingTask(int slotIndex, int* pContinueFlag) {
    struct TaskResult { // 12 bytes
        int field0; // +0x00
        int field4; // +0x04
        int field8; // +0x08
    } result;

    do {
        result.field0 = 0;
        result.field4 = 0;
        result.field8 = 0;

        // Dereference member at this+0x37c04: it's a pointer to a function pointer
        // Call with (slotIndex * 32) and address of result
        int callbackResult = (*(int (__stdcall*)(int, TaskResult*))**(int**)(this + 0x37c04))(slotIndex * 32, &result);
        if (callbackResult != 0) {
            return callbackResult; // Immediate return on non-zero (e.g., error or special status)
        }

        // Check continuation condition (e.g., game not paused, not terminated)
    } while (isProcessingAllowed(pContinueFlag) != 0); // FUN_0051eba0

    return 0;
}