//FUNC_NAME: StateMachine::handleStateChange

void __thiscall StateMachine::handleStateChange(int thisPtr, char flagSelector)
{
    uint flags = *(uint *)(thisPtr + 0x11c); // +0x11c: state flags
    uint shifted;
    if (flagSelector == '\0') {
        shifted = flags >> 9; // check bit 9
    } else {
        shifted = flags >> 8; // check bit 8
    }

    if ((shifted & 1) == 0) {
        // Selected bit is 0 (falling edge)
        if ((flags >> 0x18 & 1) != 0) { // bit 24: completion flag
            onStateExit(); // FUN_00949850
            *(uint *)(thisPtr + 0x11c) = flags & 0xfeffffff; // clear bit 24
        }
    } else {
        // Selected bit is 1 (rising edge)
        if ((flags >> 0x18 & 1) == 0) { // bit 24 not set
            onStateEnter(); // FUN_00949800
            *(uint *)(thisPtr + 0x11c) = flags | 0x1000000; // set bit 24
        }
    }
}