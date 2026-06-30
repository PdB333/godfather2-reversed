// FUNC_NAME: NetSession::processReliablePacket

// Function address: 0x005f4df0
// Role: Process a received reliable packet for a specific connection.
// Searches a list of up to 10 connection slots (each 0x5c bytes) for a matching ID.
// Then accesses a larger per-connection state block (0x170 bytes stride) to handle packet window.
// Uses two sub-arrays: one for packet sequence/state (at +0x9c within state block),
// and one for receive buffer entries (at +0x81bc, each 0x10 bytes).
// Handles duplicate detection, lock/unlock, and calls encryption/decryption helpers.

int __thiscall NetSession::processReliablePacket(int thisPtr, int connectionId)
{
    int foundIndex;
    uint resultLowByte;
    int *slotPtr;
    int stateBlockIndex;
    int *receiveEntryPtr;
    undefined4 hashInput1[2];
    float someFloat[2];
    undefined4 hashInput2[7];

    foundIndex = 0;
    receiveEntryPtr = (int *)0x0;

    // Scan the connection ID list at +0x82b0 (array of 10 entries, stride 0x5c)
    slotPtr = (int *)(thisPtr + 0x82b0);
    while ((*slotPtr < 0 || (*slotPtr != connectionId))) {
        foundIndex = foundIndex + 1;
        slotPtr = slotPtr + 0x5c / 4; // advance by 0x5c bytes
        if (9 < foundIndex) {
            return resultLowByte & 0xffffff00;
        }
    }

    if (foundIndex < 0) {
        return resultLowByte & 0xffffff00;
    }

    // Located the connection slot. Compute pointer to per-connection state block (stride 0x170)
    int *stateBlockBase = (int *)(foundIndex * 0x170 + 0x8210 + thisPtr);
    // Read the current sequence field at +0x9c within the state block (offset 0x82ac - 0x8210 = 0x9c)
    stateBlockIndex = *(int *)(foundIndex * 0x170 + 0x82ac + thisPtr) * 0x10;

    // Pointer to receive buffer entry for this sequence (array at +0x81bc, stride 0x10)
    receiveEntryPtr = (int *)(stateBlockIndex + 0x81bc + thisPtr);

    // Check if the receive buffer entry is valid (flag at +0x81c4, which is +8 from entry start)
    if (*(int *)(stateBlockIndex + 0x81c4 + thisPtr) != 0) {
        // Get some global connection object (FUN_005e9d10 returns a pointer)
        int *globalConnection = (int *)0x5e9d10(); // placeholder: likely returns a pointer to a connection manager

        // Compute hash/checksum of the received packet data
        // FUN_00c9cbe0: hash function with different modes (2 and 3)
        // First parameter: buffer at thisPtr+0x580 (likely the received data)
        // Second parameter: some field from global object +0x10
        // Third parameter: mode
        // Fourth: output array
        FUN_00c9cbe0(*(undefined4 *)(thisPtr + 0x580), *(undefined4 *)(globalConnection + 0x10), 2, hashInput1);
        FUN_00c9cbe0(*(undefined4 *)(thisPtr + 0x580), *(undefined4 *)(globalConnection + 0x10), 3, hashInput2);

        // Lock a mutex (global variable at DAT_00e2aea0)
        FUN_00ab4db0(&DAT_00e2aea0);

        // The hash output becomes the first element of both arrays (possibly the packet timestamp or sequence)
        hashInput1[0] = *(undefined4 *)(stateBlockBase + 0x134 / 4); // offset 0x134 in state block
        hashInput2[0] = hashInput1[0];

        // Check a flag in the state block at +0xa4 (possibly a resend/acknowledged flag)
        if (*(int *)(stateBlockBase + 0xa4 / 4) == 0) {
            // Compare the packet time/sequence to a global threshold (DAT_00e2b05c)
            if (DAT_00e2b05c <= *(float *)(stateBlockBase + 0x134 / 4)) {
                // Compute another set of hashes (FUN_00c9eac0, FUN_00c9cd40, FUN_00c9eae0)
                FUN_00c9eac0();
                FUN_00c9cd40(2, hashInput1);
                FUN_00c9cd40(3, someFloat);
                FUN_00c9eae0();

                if (someFloat[0] == DAT_00e2b05c) {
                    receiveEntryPtr = (int *)0x2; // success case
                } else {
                    receiveEntryPtr = (int *)0x3; // mismatch case
                    LOCK(); // atomic decrement of the receive buffer entry's counter
                    *receiveEntryPtr = *receiveEntryPtr + -1;
                    UNLOCK();
                    // Further processing for failed packet (FUN_005ea0d0)
                    FUN_005ea0d0();
                }
            }
        } else {
            receiveEntryPtr = (int *)0x1; // flag indicates already acknowledged
        }

        // Unlock mutex
        FUN_00ab4e70();

        // Determine return value: success if result is 2 or 1
        if ((receiveEntryPtr == (int *)0x2) || (receiveEntryPtr == (int *)0x1)) {
            return 1;
        }
    }

    // Return masked value (low byte cleared)
    return (int)receiveEntryPtr & 0xffffff00;
}