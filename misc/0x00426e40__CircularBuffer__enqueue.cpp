// FUNC_NAME: CircularBuffer::enqueue
// Function address: 0x00426e40
// Role: Insert a 32-bit value into a circular buffer (ring buffer) with overwrite-on-full behavior.
// Structure layout (offsets relative to this):
//   +0x00: buffer (uint32_t*) - pointer to the circular buffer array
//   +0x04: capacity (int) - number of slots in the buffer
//   +0x08: start (int) - index of the oldest element (read pointer), updated by the consumer
//   +0x0C: count (int) - number of elements that have been enqueued (may exceed capacity on overwrite)

struct CircularBuffer {
    uint32_t* buffer;   // +0x00
    int capacity;       // +0x04
    int start;          // +0x08
    int count;          // +0x0C

    void __thiscall enqueue(const uint32_t* value);
};

void __thiscall CircularBuffer::enqueue(const uint32_t* value) {
    // Compute write index = (start + old_count) % capacity
    int writeIndex = start + count;
    count++; // Increment total count (may exceed capacity)
    if (writeIndex >= capacity) {
        writeIndex -= capacity; // Wrap around
    }
    // Write the value into the buffer
    buffer[writeIndex] = *value;
}