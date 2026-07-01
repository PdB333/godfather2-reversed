// FUNC_NAME: DynamicArray::pushBack
// Address: 0x008540e0
// Role: Append a 48-byte (0x30) element to a dynamically growing array.
//       The array structure: +0x00 = base pointer, +0x04 = element count,
//       +0x08 = capacity (bits 0-29) with flags in high bits.

#include <cstring>

class DynamicArray {
    int* m_pBuffer;          // +0x00
    int  m_count;            // +0x04
    int  m_capacityAndFlags; // +0x08 (capacity = m_capacityAndFlags & 0x3FFFFFFF)

public:
    void __thiscall pushBack(const void* elementData); // 0x008540e0
};

// Grow function (address 0x00aa4190) – likely expands the buffer for elementSize bytes.
extern void grow(DynamicArray* array, int elementSize);

void __thiscall DynamicArray::pushBack(const void* elementData) {
    int count = m_count;
    int capacity = m_capacityAndFlags & 0x3FFFFFFF;

    // If full, grow array by one element of size 0x30
    if (count == capacity) {
        grow(this, 0x30);
    }

    // Write new element at index 'count'
    int newIndex = count;
    m_count = newIndex + 1;

    char* dest = reinterpret_cast<char*>(m_pBuffer) + newIndex * 0x30;
    const char* src = reinterpret_cast<const char*>(elementData);

    // Copy element structure (0x30 bytes as per element size):
    // - 8 ints (offsets 0x00 – 0x1C)
    // - 1 byte at offset 0x20
    // - 1 int  at offset 0x24
    // Remaining bytes (0x28-0x2F) are not explicitly set here; assumed zeroed or unused.
    *reinterpret_cast<int*>(dest + 0x00) = *reinterpret_cast<const int*>(src + 0x00);
    *reinterpret_cast<int*>(dest + 0x04) = *reinterpret_cast<const int*>(src + 0x04);
    *reinterpret_cast<int*>(dest + 0x08) = *reinterpret_cast<const int*>(src + 0x08);
    *reinterpret_cast<int*>(dest + 0x0C) = *reinterpret_cast<const int*>(src + 0x0C);
    *reinterpret_cast<int*>(dest + 0x10) = *reinterpret_cast<const int*>(src + 0x10);
    *reinterpret_cast<int*>(dest + 0x14) = *reinterpret_cast<const int*>(src + 0x14);
    *reinterpret_cast<int*>(dest + 0x18) = *reinterpret_cast<const int*>(src + 0x18);
    *reinterpret_cast<int*>(dest + 0x1C) = *reinterpret_cast<const int*>(src + 0x1C);
    *reinterpret_cast<char*>(dest + 0x20) = *reinterpret_cast<const char*>(src + 0x20);
    *reinterpret_cast<int*>(dest + 0x24) = *reinterpret_cast<const int*>(src + 0x24);
}