// FUNC_NAME: NetConnection::connectionStateTransition

void __thiscall NetConnection::connectionStateTransition(void* thisPtr, int connectionIndex, NetConnectionState* state)
{
    int currentState;
    void (*stateFunc)(void*);
    uint32_t eax;

    currentState = state->state; // +0x1b4 (offset 0x6d*4)
    if (currentState == 1 || currentState == 4) {
        // Connecting (1) or Connected (4)
        stateFunc = (void (*)(void*))state->vtable[3]; // vtable +0xc
        stateFunc(thisPtr);
        sendAck(); // FUN_006550d0
    }
    else if (currentState == 7) {
        // Disconnecting (7) -> set to Disconnected (8)
        stateFunc = (void (*)(void*))state->vtable[4]; // vtable +0x10
        state->state = 8;
        stateFunc(thisPtr);

        if (state->reliableFlags == 0) { // +0x124 (offset 0x49*4)
            clearPacketBuffer(); // FUN_0064f2d0
            clearBuffer8(8, &someStackVar); // FUN_0064b810(8, &stack0xfffff83f)
            memset(state->field_0x133, 0, 0x40); // FUN_0064b810(0x40, &state[0x133])
            memset(state->field_0x13b, 0, 0x40); // FUN_0064b810(0x40, &state[0x13b])
            setPacketFlags(eax, 0xFF); // FUN_0064c760
            if (*(char*)((int)state + 0x131) != '\0') {
                char buffer[644]; // size 0x284
                compressData(buffer); // FUN_0065a5e0
                computeChecksum((connectionIndex + 7) >> 3, buffer); // FUN_0064c980
                updateAckSequence(); // FUN_00656aa0
            }
            copyBuffer(connectionIndex + 0x5c, state + 0x40); // FUN_0064cb60
            resetSequenceNumber(); // FUN_0064b440
        }
        processNextState(connectionIndex, state); // FUN_006552f0
    }
    return;
}