// FUNC_NAME: Array8::reserve
// Function address: 0x00617d50
// Role: Reserves capacity for an array of 8-byte elements (typical EA container pattern)

void Array8::reserve(uint32_t newCapacity)
{
    // Check if we need to grow
    if (capacity < newCapacity) {
        // Allocate new block (element size = 8 bytes)
        uint8_t* newData = static_cast<uint8_t*>(memoryAllocate(newCapacity * 8));

        // Copy existing elements if any
        if (data != nullptr) {
            uint32_t idx = 0;
            uint8_t* dst = newData;
            if (count != 0) {
                do {
                    // Copy a pair of 32-bit values (8 bytes per element)
                    if (dst != nullptr) {  // Safety check from decompilation
                        *reinterpret_cast<uint32_t*>(dst) = *reinterpret_cast<uint32_t*>(data + idx * 8);
                        *reinterpret_cast<uint32_t*>(dst + 4) = *reinterpret_cast<uint32_t*>(data + idx * 8 + 4);
                    }
                    idx++;
                    dst += 8;
                } while (idx < count);
            }
            memoryFree(data);
        }

        // Update pointer and capacity
        data = newData;
        capacity = newCapacity;
    }
}