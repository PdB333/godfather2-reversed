// FUNC_NAME: MessageQueue::addMessage
// Function address: 0x0063de40
// Adds a new 12-byte message element (param_2) to the queue.
// Internal structure at this+0x1c is a pointer to a QueueStruct:
//   +0x00: pointer to DataStruct (actual storage metadata)
//   +0x30: current element count (queueStruct[0xc])
// DataStruct layout:
//   +0x18: pointer to allocated buffer (dataStruct[6])
//   +0x38: capacity in elements (dataStruct[14])
// Element size: 12 bytes (0xC)
// If capacity is insufficient, calls growArray (FUN_00627930) using the allocator at this+0x20.

void __thiscall MessageQueue::addMessage(void *this, int messageData) {
    // Pointer to queue metadata structure (e.g., QueueStruct*)
    int *queueStruct = *(int **)((char *)this + 0x1c);
    // Pointer to data storage metadata (e.g., DataStruct*)
    int *dataStruct = (int *)*queueStruct;
    int capacity = dataStruct[0x38 / 4];   // capacity at +0x38
    int count = queueStruct[0x30 / 4];      // count at +0x30

    // Check if capacity is sufficient for one more element
    if (capacity < count + 1) {
        // Reallocate buffer: arguments: allocator (this+0x20), old buffer (dataStruct+0x18),
        // address of capacity (dataStruct+0x38), element size 0xC, some constant tag
        void *newBuffer = FUN_00627930(
            *(void **)((char *)this + 0x20),          // allocator instance
            *(void **)((char *)dataStruct + 0x18),    // old buffer
            (int *)((char *)dataStruct + 0x38),        // capacity pointer (to update)
            0xC,                                       // element size in bytes
            &DAT_00e2f044);                            // memory tag identifier
        // Update the buffer pointer
        *(void **)((char *)dataStruct + 0x18) = newBuffer;
    }
    // Write the new message into the buffer at index 'count' (each element 12 bytes)
    int *buffer = *(int **)((char *)dataStruct + 0x18);
    buffer[count * (0xC / 4)] = messageData;   // store first 4 bytes of the 12-byte slot
    // Increment the element count
    queueStruct[0x30 / 4] = count + 1;
}