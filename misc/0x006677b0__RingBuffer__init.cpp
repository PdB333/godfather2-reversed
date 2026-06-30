// FUNC_NAME: RingBuffer::init
struct RingBuffer {
    int32_t head;        // +0x00: index of first element
    int32_t elementSize; // +0x04: size of each element (e.g., 0x40 = 64 bytes)
    int32_t tail;        // +0x08: index of last element
    void* buffer;        // +0x0C: allocated data (count * elementSize bytes)
};

int32 __thiscall RingBuffer::init(RingBuffer* this) {
    // Allocate storage for 'count' elements (count = 4 hardcoded, elementSize = 0x40)
    void* buf = calloc(4, 0x40); // 4 * 64 = 256 bytes
    this->buffer = buf;
    if (buf == nullptr) {
        return 0xFFFFFFFE; // -2
    }
    this->head = 0;
    this->elementSize = 0x40;
    this->tail = 0;
    return 0;
}