// FUN_00459800: EventManager::processPendingEvents
void __thiscall EventManager::processPendingEvents(void) {
    // +0x34: count of pending events
    uint pendingCount = *(uint *)((char *)this + 0x34);
    if (pendingCount != 0) {
        // +0x50: base pointer to array of 0xB0-byte pending event structures
        char *arrayBase = *(char **)((char *)this + 0x50);
        int currentOffset = 0;
        for (uint i = 0; i < pendingCount; i++) {
            char *event = arrayBase + currentOffset;
            // [event+6] is a boolean flag; [event+0x4C] indicates already processed
            if (*(char *)(event + 6) != 0 && *(int *)(event + 0x4C) == 0) {
                // Allocate a new event node (FUN_004596c0)
                EventNode *newNode = allocateEventNode();
                // Insert at head of singly-linked list stored at +0x70
                newNode->next = *(EventNode **)((char *)this + 0x70);
                *(EventNode **)((char *)this + 0x70) = newNode;
            }
            currentOffset += 0xB0;
        }
    }
}