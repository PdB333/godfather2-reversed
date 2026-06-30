// FUNC_NAME: NetSession::processPacket
// Function address: 0x0063f4f0
// Role: State machine for processing incoming packet data. Handles various packet types (states 0x28-0x11E).
// Structure offsets: +0x04 = prevState, +0x08 = stateBackup, +0x0C = currentState,
// +0x10 = stateBuffer, +0x14 = nextState, +0x18 = altState, +0x1C = packetHeaderPtr

void __thiscall NetSession::processPacket(NetSession* this) {
    int state;
    int* packetHeader;  // from this+0x1C
    int result;
    char localBuffer[24]; // size unknown, used for temporary data

    packetHeader = *(int**)(this + 0x1C);
    FUN_0063f440(); // beginStreamRead

    state = *(int*)(this + 0x0C);
    while ((uint)(state - 0x28) < 0xF7) {
        switch (state - 0x28) {
            case 0x28: // state 0x50? Actually state = 0x28+0x28=0x50
            case 0x7B: // state 0x28+0x7B=0xA3
            case 0x11E: // state 0x28+0x11E=0x146
                // These states all result in a call to FUN_00642ec0 (likely stream cleanup) then fallthrough
                FUN_00642ec0(); // cleanupStream
                goto LAB_0063f614;
            case 0x2E: // state 0x28+0x2E=0x56
                FUN_0063e790(this); // handleSpecialPacket
                break;
            case 0x3A: // state 0x28+0x3A=0x62
                *(int*)(this + 0x08) = *(int*)(this + 0x04); // backup state
                if (*(int*)(this + 0x14) == 0x11F) {
                    // Transition with deserialization
                    int readResult = FUN_00639c70(this + 0x10); // readFromBuffer
                    *(int*)(this + 0x0C) = readResult;
                } else {
                    *(int*)(this + 0x0C) = *(int*)(this + 0x14); // use nextState
                    *(int*)(this + 0x10) = *(int*)(this + 0x18); // copy altBuffer
                    *(int*)(this + 0x14) = 0x11F; // reset nextState to sentinel
                }
                // Prepare local buffer for timestamp/sequence
                int (*timestamp)() = FUN_0063dd40; // getTimestamp
                *(int*)&localBuffer[0] = 4;
                *(int*)&localBuffer[4] = 4; // sizes?
                *(int*)&localBuffer[8] = 0xFFFFFFFF;
                *(int*)&localBuffer[12] = 0xFFFFFFFF;
                *(int*)&localBuffer[16] = FUN_00642970(*(int*)(this + 0x1C), &localBuffer[0]); // allocatePacketData
                FUN_00643170(&localBuffer[4]); // copyPacketData
            LAB_0063f614:
                FUN_0063f300(this); // advanceState
                break;
            case 0x5B: // state 0x28+0x5B=0x83
                int eax = FUN_00642b00(); // getPacketHeader
                if (eax == 0xB) {
                    // Specific packet type
                    if (*(int*)(this + 0x04) < *(int*)(packetHeader + 0x34)) {
                        // Fallback to cleanup
                        FUN_00642ec0(); // cleanupStream
                    } else {
                        FUN_00642d90(*(int*)(this + 0x04)); // processPacketData
                    }
                } else {
                    FUN_00642ec0(); // cleanupStream
                }
                FUN_0063e860(); // finalizePacket
                int stateResult = FUN_00642fc0(); // getNextState
                *(int*)(eax + 8) = stateResult; // store state
                *(int*)eax = 8; // set packet type?
                break;
            default:
                return; // unrecognized state
        }
        state = *(int*)(this + 0x0C); // reload state after processing
    }
    // If loop condition fails (state out of range), function returns
    return;
}