// FUNC_NAME: Player::handleFocusEvent
void __fastcall Player::handleFocusEvent(int thisPtr) {
    // Debug trace with hash for this event
    debugTrace(0xdab8f267); // likely "Player: handleFocusEvent start"

    // Build event data from offset +0x29c (e.g., target entity handle)
    int eventData;      // local_c
    int eventData2;     // local_8
    char eventPad;      // local_4
    eventData = *(int *)(thisPtr + 0x29c); // +0x29c: event parameter 1 (e.g., target ID)
    eventData2 = 0;
    eventPad = 0;
    setEventParameter(&eventData, 0); // 0 = clear event flags

    // Check if the owner's flag at +0x180->+0x34 has bit 26 (0x4000000) set
    int *ownerFlags = (int *)(*(int *)(thisPtr + 0x180) + 0x34); // +0x180: m_pOwnerData, +0x34: m_flags
    if (((*ownerFlags >> 0x1a) & 1) == 0) { // bit 26 not set
        debugTrace(0x33affd55); // "Player: handleFocusEvent set flag"

        // Set the flag
        *ownerFlags |= 0x4000000;

        // Build event data from offset +0x2a4 (e.g., second parameter)
        eventData = *(int *)(thisPtr + 0x2a4); // +0x2a4: event parameter 2
        eventData2 = 0;
        eventPad = 0;
        setEventParameter(&eventData, 0);
    }
}