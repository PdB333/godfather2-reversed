// FUN_NAME: NetConnection::handleRecvWindowSlot
void __thiscall NetConnection::handleRecvWindowSlot(int param_1, int param_2)
{
    int *windowEntryPtr;
    int sequence;

    if ((param_2 != 0) && (*(byte *)(param_2 + 0x1ac) < 0x19)) {
        // param_2 is a connection object with a slot index at +0x1AC (< 25)
        // param_1 points to a PacketWindowManager, which has a pointer to an array of 12-byte window entries at +0x24
        // Each window entry: first int at offset +4, so the actual entry start is offset +4 from the array base
        windowEntryPtr = (int *)(*(int *)(param_1 + 0x24) + 4 + (uint)*(byte *)(param_2 + 0x1ac) * 0xc);
        sequence = *windowEntryPtr;

        // If the entry has a sequence number that is non-zero and not the special sentinel 0x48, process it
        if ((sequence != 0) && (sequence != 0x48)) {
            // The inner condition is always true because sequence is already non-zero from the outer check
            // So this just calls the processing subroutine
            FUN_008dd250();
            return;
        }
        // Note: compiler optimization led to identical call in both branches; effectively just one call when condition holds
    }
    return;
}