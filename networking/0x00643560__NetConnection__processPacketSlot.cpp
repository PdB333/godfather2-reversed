// FUNC_NAME: NetConnection::processPacketSlot
//
// Function at 0x00643560: Handles the state machine for a specific packet slot.
// The slot is identified by 'slotData' (index or sequence number) stored in
// the structure pointed to by 'slotState' (EDI). 'this' is the connection object.
//
// The slot goes through states:
// 4 -> something (maybe ACK pending) -> if condition met, get a new value and return.
// 11 -> check if retry limit reached, decrement retry count if within bounds.
// Then transition to state 10 after building a packet header via FUN_006438e0.
//
// param_1: if non-zero, perform a cleanup/abort path (FUN_00643450).

void NetConnection::processPacketSlot(int param_1)
{
    int *slotState;            // EDI: points to a packet slot structure (two ints: state + data)
    int *thisPtr;              // EAX: 'this' pointer
    int iVar1;                 // temporary for results
    int *unaff_EDI;            // copy of slotState (actually from EDI register)

    // Handle forced abort/cleanup case.
    if (param_1 != 0) {
        // FUN_00643450: cleanup call (maybe abort slot processing)
        this->abortSlotProcessing(slotState);
        return;
    }

    // FUN_00642f70: presumably some time-based update or pre-processing.
    this->updateSlotTimers();

    // Check if current state is '4' and a certain condition on the slot data is true.
    if ((*slotState == 4) &&
        (*(int *)(*(int *)(*(int *)thisPtr + 8) + slotState[1] * 8) == 3))
    {
        // Condition met: generate a new sequence number or packet ID.
        iVar1 = this->generateNextSequenceNumber();
        slotState[1] = iVar1;
        return;
    }

    // FUN_00642f30: another state-processing step (maybe check timeouts).
    this->processStateTimers();

    // Check if state is '11' (0xb) and slot data is within retry limits.
    if ((*slotState == 11) &&
        ((thisPtr[13] <= slotState[1] && (slotState[1] < 0xfa))))
    {
        // Decrement retry counter (offset +0x24 from 'this').
        thisPtr[9] = thisPtr[9] - 1;
    }

    // Build a packet header using slot data (shifted 15 bits) or'd with type 0x11,
    // plus a parameter from a buffer at thisPtr[3]+8.
    iVar1 = FUN_006438e0(slotState[1] << 0xf | 0x11,
                          *(int *)(thisPtr[3] + 8));

    // Update slot data and move state to '10' (timeout/complete?).
    slotState[1] = iVar1;
    *slotState = 10;
    return;
}