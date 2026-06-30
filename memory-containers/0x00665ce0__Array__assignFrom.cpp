// FUNC_NAME: Array::assignFrom
// Function address: 0x00665ce0
// Copies the contents of another Array into this one, handling resizing if necessary.
// Structure layout (x86, 12 bytes header + data pointer):
//   +0x00 int m_count       // number of elements
//   +0x04 int m_capacity    // allocated capacity
//   +0x08 int m_field8      // unknown (preserved during copy)
//   +0x0C int* m_data       // pointer to element array

int Array::assignFrom(const Array& src) {
    // Self-assignment guard
    if (this == &src) {
        return 0;
    }

    // If current capacity is insufficient, try to resize
    if (m_capacity < src.m_count) {
        int result = resize(src.m_count); // FUN_00667740
        if (result != 0) {
            return result;
        }
    }

    // Copy elements from source to destination
    int* destData = m_data;
    int* srcData = src.m_data;
    int i;
    for (i = 0; i < src.m_count; i++) {
        *destData = *srcData;
        destData++;
        srcData++;
    }

    // Zero fill remaining elements if our capacity is larger
    for (; i < m_capacity; i++) {
        *destData = 0;
        destData++;
    }

    // Copy count and the unknown field
    m_count = src.m_count;
    m_field8 = src.m_field8;

    return 0;
}