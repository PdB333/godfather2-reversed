// FUN_0046dfb0: EventManager::processEvent
void EventManager::processEvent(uint eventId, uint32_t* payload) {
    // Global game state at 0x01223398
    uint8_t* gameState = *(uint8_t**)0x01223398;
    // +0x08: pointer to hash table structure
    uint8_t* hashTable = *(uint8_t**)(gameState + 8);

    // +0x04: pointer to bucket array (each entry is a pointer to a linked list node)
    uint32_t** bucketArray = *(uint32_t***)(hashTable + 4);
    // +0x08: number of buckets
    uint32_t bucketCount = *(uint32_t*)(hashTable + 8);

    uint32_t bucketIndex = eventId % bucketCount;
    // Each node: +0x00 = event ID, +0x08 = next pointer
    EventNode* node = (EventNode*)bucketArray[bucketIndex];
    while (node != nullptr && node->id != eventId) {
        node = node->next;
    }

    // Copy the 16 dword payload into a local buffer (64 bytes)
    uint32_t eventData[16];
    for (int i = 0; i < 16; ++i) {
        eventData[i] = payload[i];
    }

    // Dispatch the event (actual handler at 0x0049f420)
    FUN_0049f420(eventData);
}