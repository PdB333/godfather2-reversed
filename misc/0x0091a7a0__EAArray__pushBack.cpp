// FUNC_NAME: EAArray::pushBack

struct EAArray {
    uint32_t* data;     // +0x70
    int size;           // +0x74
    int capacity;       // +0x78

    void pushBack(uint32_t value);
    void resize(int newCapacity); // defined elsewhere, reallocates data
};

void EAArray::pushBack(uint32_t value) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size] = value;
    size++;
}