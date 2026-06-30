// FUNC_NAME: PacketWindow::getSlot
int __thiscall PacketWindow::getSlot(void* thisPtr, uint32_t inputData)
{
    // Extract sequence number from packed data
    int32_t sequence = extractSequence(inputData);  // FUN_006948e0

    // Null check
    if (thisPtr == nullptr) {
        panic();  // FUN_00b97aea
    }

    // Check if sequence is within the current window
    if (sequence != *(int32_t*)((char*)thisPtr + 4)) {  // +0x04: m_numSlots or m_windowSize?
        int32_t result = isSequenceInWindow(sequence + 0x0c);  // FUN_004d4b20
        if (result >= 0) {
            goto done;  // sequence already valid, skip release and lookup
        }
    }

    // Sequence not in window, release the input data (e.g., free packet)
    releaseInputData(inputData);  // FUN_004d3b50

    // Prepare for lookup
    uint32_t local8 = 0;
    uint32_t local4 = 0;
    int32_t local18[3];
    // local20 is likely a temporary structure (8 bytes)
    // The function lookupSlot returns a pointer to a pair of ints:
    // first int = new thisPtr, second int = new sequence (slot address)
    int* resultPair = lookupSlot(local20, thisPtr, sequence, local18);  // FUN_00696890
    thisPtr = (void*)(*resultPair);
    sequence = resultPair[1];
    if (local18[0] != 0) {
        // (potential destructor call - original code had uninitialized local_c)
        // (*cleanupFunc)(local18[0]);  // local_c was uninitialized in decomp - likely a cleanup callback
    }

done:
    // Validate final state
    if (thisPtr == nullptr) {
        panic();
    }
    if (sequence == *(int32_t*)((char*)thisPtr + 4)) {  // +0x04: m_numSlots?
        panic();
    }

    // Return pointer to payload at offset 0x1c from slot base
    return sequence + 0x1c;
}