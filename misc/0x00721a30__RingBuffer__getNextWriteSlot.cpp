// FUNC_NAME: RingBuffer::getNextWriteSlot
// Address: 0x00721a30
// Purpose: Advances the write pointer in a ring buffer with overwrite-on-full behavior.
//          Returns pointer to the previous write slot (element size = 36 bytes).

struct RingBuffer {
    int capacity;     // +0x00: maximum number of elements
    int head;         // +0x04: current write index (next slot to write into after return)
    int tail;         // +0x08: current read index (next slot to read from)
    char* data;       // +0x0C: base pointer to the ring buffer data (each element = 0x24 bytes)
};

void* __thiscall RingBuffer::getNextWriteSlot(void) {
    int oldHead = this->head;                // Save previous write index
    int newHead = oldHead + 1;               // Advance write index

    // Wrap head if it exceeds capacity
    if (newHead >= this->capacity) {
        newHead = 0;
    }
    this->head = newHead;

    // If the new head caught up to or passed the tail, advance tail to discard old data
    if (newHead <= this->tail) {
        this->tail++;
        if (this->tail >= this->capacity) {
            this->tail = 0;
        }
    }

    // Return pointer to the element at the old head (caller will write there)
    return this->data + (oldHead * 0x24);
}