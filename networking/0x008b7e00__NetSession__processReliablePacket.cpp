// FUNC_NAME: NetSession::processReliablePacket
// Function address: 0x008b7e00
// Processes a packet type 1 (reliable) and adds entries to a pending queue.
// Packet format: [type(int), count(int), entries...] each entry = 5 ints (20 bytes)
// The queue is at this+0x8, max 64 entries (0x40), count at this+0x508.

int __thiscall NetSession::processReliablePacket(void* this, int unused, int* packetData) {
    int* piVar1;
    int iVar2;
    int* piVar3;
    int* piVar4;
    int iVar5;
    uint entryIndex;

    preprocessPacket(); // FUN_008b79d0 - likely initializes or checks state

    if (*packetData == 1) { // packet type = 1 (reliable data)
        piVar4 = packetData + 2; // pointer to first entry's field0
        entryIndex = 0;
        piVar3 = packetData; // used to index into entries via offset 3
        if (packetData[1] != 0) { // number of entries
            do {
                iVar2 = *piVar4; // entry field0 (e.g., sequence number)
                iVar5 = findEntryInList(piVar3 + 3); // FUN_008b7bb0 - check if entry already exists (field1 key)
                if (iVar5 < 0) { // entry not found
                    if (*(int*)((int)this + 0x508) == 0x40) { // queue full (64 entries)
                        flushBuffer(0); // FUN_008b7a40 - flush or reallocate queue
                    }
                    piVar1 = (int*)((int)this + 8 + *(int*)((int)this + 0x508) * 20); // address of new slot
                    *(int*)((int)this + 0x508) = *(int*)((int)this + 0x508) + 1; // increment count
                    *piVar1 = iVar2; // field0
                    piVar1[1] = piVar3[3]; // field1
                    piVar1[2] = piVar3[4]; // field2
                    piVar1[3] = piVar3[5]; // field3
                    piVar1[4] = piVar3[6]; // field4
                }
                piVar4 += 5; // advance to next entry
                entryIndex++;
                piVar3 += 5; // advance offset pointer
            } while (entryIndex < (uint)packetData[1]);
        }
    }
    return 1; // always returns true
}