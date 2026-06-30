// FUNC_NAME: PlayerSM::handleEvent
void __thiscall PlayerSM::handleEvent(Event* event) {
    int idx;
    int slotPtr;

    // Parent object (e.g., Player) is at offset -0x1c from this component
    Player* parent = (Player*)((char*)this - 0x1c);
    int* gStateTable = (int*)DAT_0112a554; // global state table pointer

    // Check if event ID matches this state's expected ID (stored at this+0x14)
    if (event->id == *(int*)(this + 0x14)) {
        parent->processEvent(event);  // FUN_006accf0 - let parent handle the event
        freeEvent(event);             // FUN_0046c6a0 - delete the event
        return;
    }

    // Check for a global event ID constant
    if (event->id == DAT_0120e93c) { // kGlobalEventId
        idx = parent->getStateIndex();  // FUN_006ac320 - get index into global table
        slotPtr = idx * 0x30 + 0x10 + (int)gStateTable;
        if (slotPtr != 0) {
            // Store data from this component (offset +0x1c) into the global table slot at +0x20
            *(int*)(slotPtr + 0x20) = *(int*)(this + 0x1c);
        }
        releaseGlobalEvent(&DAT_0120e93c); // FUN_004086d0 - deregister or cleanup
    }

    freeEvent(event); // always delete the event
}