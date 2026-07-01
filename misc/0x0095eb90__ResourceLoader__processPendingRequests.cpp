// FUNC_NAME: ResourceLoader::processPendingRequests
// Function address: 0x0095eb90
// Processes a batch of up to 16 pending resource load requests, starting from a priority-determined offset.
// The global arrays manage a reallocatable buffer of request descriptors (0x10 bytes each).
void ResourceLoader::processPendingRequests(char isHighPriority)
{
    int requestIndex;
    uint slot;
    int requestData[3]; // Holds request identifier or callback info (e.g., resource ID, type)
    void (*completionCallback)(int) = nullptr; // Callback for completed request (unset here, likely set elsewhere)

    // Global state for request queue
    extern int gRequestCount;          // DAT_0113082c - number of active requests
    extern int gRequestCapacity;       // DAT_01130830 - allocated capacity (number of 0x10-byte slots)
    extern int* gRequestArray;         // DAT_01130828 - pointer to array of request descriptors (each 0x10 bytes)
    extern int gRequestBatchStart[2];  // DAT_00d8ccf4 - starting slots for normal (index 0) and high priority (index 1)

    // Initialization (probably acquires a mutex or critical section)
    lockResourceQueue();

    requestData[0] = 0;
    requestData[1] = 0;
    requestData[2] = 0;

    // Choose starting slot based on priority
    slot = gRequestBatchStart[isHighPriority ? 1 : 0];

    // Process up to 0x10 (16) consecutive slots
    while (slot < 0x11)
    {
        // Retrieve the pending request at 'slot' into requestData; third parameter '1' likely means "remove from queue"
        getNextPendingRequest(slot, requestData, 1);

        // If the queue count reached capacity, double the capacity (or allocate if zero)
        if (gRequestCount == gRequestCapacity)
        {
            int newCapacity = (gRequestCapacity == 0) ? 1 : (gRequestCapacity * 2);
            reallocateRequestQueue(newCapacity);
        }

        // Calculate byte offset for the new slot (each descriptor is 0x10 bytes)
        requestIndex = gRequestCount * 0x10;

        // Advance the request count
        gRequestCount = gRequestCount + 1;

        // If the descriptor at the newly allocated slot exists (non-null based on first field), process it
        if (requestIndex + reinterpret_cast<int>(gRequestArray) != 0) // Check if slot is valid (dereference at that offset)
        {
            processRequestDescriptor(requestData);
        }

        slot = slot + 1;
    }

    // If a request was fetched, call the completion callback (callback is null here, possibly set by other code)
    if (requestData[0] != 0)
    {
        if (completionCallback != nullptr)
        {
            completionCallback(requestData[0]);
        }
    }

    // Release lock
    unlockResourceQueue();
}