// FUNC_NAME: GrowingArray::allocateNextSlot
// Function address: 0x00949aa0
// Role: Returns a pointer to the next available element slot in a dynamic array (0x30-byte elements) and increments the size.
// Structure offsets:
//   +0x00: m_data (pointer to element array)
//   +0x04: m_size (current number of elements)
//   +0x08: m_capacity (allocated element capacity)

class GrowingArray {
public:
    char *m_data;      // +0x00
    int m_size;        // +0x04
    int m_capacity;    // +0x08

    // FUN_00941a80 – reallocates internal array to new capacity (unknown signature)
    void reallocate(int newCapacity);
};

char *__fastcall allocateNextSlot(GrowingArray *this) {
    if (this->m_size == this->m_capacity) {
        int newCapacity;
        if (this->m_capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = this->m_capacity * 2;
        }
        this->reallocate(newCapacity);
    }
    int index = this->m_size;
    this->m_size = index + 1;
    return &this->m_data[index * 0x30];
}