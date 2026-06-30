// FUNC_NAME: EventManager::addEvent

void __thiscall EventManager::addEvent(EventManager* this, void* owner, int eventId, uint8_t eventType)
{
    int hashKey;
    EventNode* newNode;
    int oldHead;
    uint bucketIndex;

    hashKey = getEventId(eventId); // FUN_004dafd0, computes hash from eventId
    newNode = (EventNode*)allocateMemory(0x18); // FUN_009c8e50
    if (newNode != (EventNode*)0x0) {
        oldHead = *(int*)((int)owner + 4); // owner's event list head (at offset +4)
        newNode->owner = owner;
        newNode->eventId = eventId;
        newNode->hashKey = hashKey;
        newNode->eventType = eventType;
        newNode->ownerNext = (EventNode*)oldHead;
    }
    // Check global initialization flag
    if ((s_globalFlags & 1) == 0) {
        s_globalFlags |= 1;
        s_bucketCount = 0x4f; // 79 buckets
        s_hashTable = (EventNode**)0x0;
        s_totalEvents = 0;
        s_autoResize = '\0';
        s_hashTable = (EventNode**)allocateLargeMemory(0x13c); // FUN_009c8e80 (79 * 4 = 0x13c)
        memset(s_hashTable, 0, s_bucketCount * 4);
        atexit(&shutdownEventManager); // LAB_00d50b90
    }
    // Insert into global hash table
    if (newNode != (EventNode*)0x0) {
        bucketIndex = (uint)(newNode->hashKey) % s_bucketCount;
    } else {
        bucketIndex = 0; // fallback (should not happen as newNode is allocated)
    }
    // Auto-resize if needed (s_autoResize flag non-zero and count >= 2*bucketCount)
    if ((s_autoResize != '\0') && (s_bucketCount * 2 <= s_totalEvents)) {
        resizeHashTable(&s_hashTable); // FUN_0049cc30
        bucketIndex = (uint)(newNode->hashKey) % s_bucketCount;
    }
    // Link into bucket's chain (head insertion)
    newNode->hashNext = s_hashTable[bucketIndex];
    s_hashTable[bucketIndex] = newNode;
    s_totalEvents++;
    // Update owner's event list head
    *(int*)((int)owner + 4) = (int)newNode;
    return;
}