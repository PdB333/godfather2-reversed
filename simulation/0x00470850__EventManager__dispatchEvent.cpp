// FUNC_NAME: EventManager::dispatchEvent
// Address: 0x00470850
// Role: Dispatches an event by ID with 128-bit data payload via a handler function.
void EventManager::dispatchEvent(uint eventId, const uint64_t eventData[2]) {
    // Hash table lookup: use eventId to find a bucket via modulus
    uint* hashTable = *(uint**)(*(int*)(DAT_01223398 + 8) + 4); // pointer to bucket array
    uint bucketCount = *(uint*)(*(int*)(DAT_01223398 + 8) + 8); // number of buckets
    uint bucketIndex = eventId % bucketCount;
    uint* node = (uint*)*(hashTable + bucketIndex); // each bucket has a linked list

    // Traverse the linked list to find a matching node (key at offset 0, next at offset 8)
    while (node != nullptr && *node != eventId) {
        node = (uint*)node[2]; // next node (offset 8)
    }

    // After lookup, prepare argument array for handler invocation
    // gEventHandlerObject is a global singleton (likely this pointer for EventManager)
    void* args[4];
    args[0] = (void*)&PTR_LAB_00e32aa0; // pointer to the event handler object (gEventHandlerObject)
    args[1] = (void*)eventData[0];       // first 64-bit data
    args[2] = (void*)eventData[1];       // second 64-bit data
    // args[3] remains uninitialized (not used)

    // Call the event dispatch function with the handler function and arguments
    invokeWithArgs((void*)FUN_0049eb20, args); // FUN_0049eb20 is the handler function
}