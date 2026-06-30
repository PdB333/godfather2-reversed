// FUNC_NAME: EARSGrowableArray::reserve
void EARSGrowableArray::reserve(uint newCapacity)
{
    // Structure layout:
    // +0x00: int* m_data       (pointer to element array)
    // +0x04: int m_size        (current number of elements)
    // +0x08: int m_capacity    (allocated number of elements)
    uint* thisInts = reinterpret_cast<uint*>(this);
    int* dataPtr = reinterpret_cast<int*>(thisInts[0]); // m_data
    int size = static_cast<int>(thisInts[1]);           // m_size
    int capacity = static_cast<int>(thisInts[2]);       // m_capacity

    if ((uint)capacity >= newCapacity) {
        // Already enough capacity, nothing to do
        return;
    }

    // Allocate new buffer: each element is 0x24 (36) bytes
    byte* newData = reinterpret_cast<byte*>(::operator new(newCapacity * 0x24));
    if (newData == nullptr) {
        // Handle allocation failure if needed (original code doesn't check)
        return;
    }

    if (dataPtr != nullptr && size > 0) {
        // Copy existing elements: each element is 36 bytes (5 * 8 + 4)
        byte* src = reinterpret_cast<byte*>(dataPtr);
        byte* dst = newData;
        for (int i = 0; i < size; ++i) {
            // Copy first 4 quadwords (32 bytes)
            *reinterpret_cast<uint64_t*>(dst) = *reinterpret_cast<uint64_t*>(src);
            *reinterpret_cast<uint64_t*>(dst + 8) = *reinterpret_cast<uint64_t*>(src + 8);
            *reinterpret_cast<uint64_t*>(dst + 16) = *reinterpret_cast<uint64_t*>(src + 16);
            *reinterpret_cast<uint64_t*>(dst + 24) = *reinterpret_cast<uint64_t*>(src + 24);
            // Copy the last 4-byte word
            *reinterpret_cast<int*>(dst + 32) = *reinterpret_cast<int*>(src + 32);
            src += 0x24;
            dst += 0x24;
        }
    }

    // Free old buffer
    if (dataPtr != nullptr) {
        ::operator delete(dataPtr);
    }

    // Update pointer and capacity
    thisInts[0] = reinterpret_cast<uint>(newData);
    thisInts[2] = newCapacity;
}