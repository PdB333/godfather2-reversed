// FUNC_NAME: NetObject::destroy
// Function address: 0x0044a7c0
// Handles deletion of a network object: sends final state packet (if ghosted) and frees memory.
// Offsets: +0x04 = connection pointer (NetConnection*), +0x08 = unknown pointer (perhaps vtable of a packet sender),
// +0x0C = object state (0 = invalid, 0x48 = deleted), +0x18 = short network ID, +0x1A = flags (bit0 = "needsDestroyPacket").

void NetObject::destroy(void)
{
    int *statePtr;
    undefined4 *connPtr;
    char flags;
    int stateValue;
    code *sendFunc;
    undefined4 *netIdData;
    undefined4 packetHeader[4]; // 0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911

    statePtr = (int *)(this + 0x0C);
    stateValue = *(int *)(this + 0x0C);

    // Two main paths: object already in a terminal state (0 or 0x48) or still active.
    if ((stateValue == 0) || (stateValue == 0x48)) {
        // Object is dead or already being destroyed. Check if we need to send a final packet.
        flags = *(byte *)(this + 0x1A);
        if ((flags & 1) != 0) {
            connPtr = *(undefined4 **)(this + 0x04);
            sendFunc = (code *)FUN_00446bc0(); // Get connection's send packet function?
            if (sendFunc != (code *)0x0) {
                // Call a virtual method on the packet sender (from offset +0x08) to prepare sending.
                (**(code **)(**(int **)(*(int *)(this + 0x08) + 8) + 0x1C))();

                // Fill packet header with magic constants (network signature)
                packetHeader[0] = 0xBADBADBA;
                packetHeader[1] = 0xBEEFBEEF;
                packetHeader[2] = 0xEAC15A55;
                packetHeader[3] = 0x91100911;

                // Get network‑specific data using the object's short ID
                netIdData = (undefined4 *)FUN_00449be0(*(undefined2 *)(this + 0x18));
                packetHeader[0] = *netIdData;
                packetHeader[1] = netIdData[1];
                packetHeader[2] = netIdData[2];
                packetHeader[3] = netIdData[3];

                // Send the packet: first argument is the connection pointer, then packet data, flags 0,0,2.
                (*sendFunc)(*connPtr, packetHeader, 0, 0, 2);
            }
        }
    }
    else {
        // Object is still alive. Compute index into an object table (by subtracting 0x48).
        // This index is used to access a virtual call (destructor or state update).
        int idx;
        if (*statePtr == 0) {
            idx = 0;
        }
        else {
            idx = *statePtr - 0x48;
        }
        // Call a virtual method on some object (located at idx+0x3c?).
        (**(code **)(*(int *)(idx + 0x3C) + 8))();

        // Synchronisation / refcounting: increment a global counter and possibly set a wait flag.
        if (DAT_012067C4 != 0) {
            char lockOk = FUN_00402080(&DAT_012067C4);
            if (lockOk == '\0') {
                _DAT_012067C8 += 1;
                FUN_004084D0(&DAT_012067C4, 0x8000);
            }
        }

        // If the state field is non‑zero, free the object’s memory and reset the pointer.
        if (*statePtr != 0) {
            FUN_004DAF90(statePtr); // likely operator delete or custom free
            *statePtr = 0;
            return;
        }
    }
    return;
}