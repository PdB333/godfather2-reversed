// FUNC_NAME: DynamicArray::removeAt
// Address: 0x004e18a0
// Removes an element at a given index from a fixed-size (0x18 bytes) dynamic array.
// Uses __fastcall: this in ECX, index in EAX (custom convention).
// The struct at this has:
//   +0x00: void* data (pointer to array elements)
//   +0x04: int count (number of elements)

void __fastcall DynamicArray::removeAt(int index)
{
    // Only shift if index is not the last element
    if (index < count - 1)
    {
        // Shift elements left by one (each element is 0x18 = 24 bytes)
        int offset = index * 0x18;
        do {
            uint64_t* src = (uint64_t*)((char*)data + offset + 0x18);
            uint64_t* dst = (uint64_t*)((char*)data + offset);
            // Copy three 8-byte chunks
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];  // Equivalent to memmove 0x18 bytes
            index++;
            offset += 0x18;
        } while (index < count - 1);
    }
    // Decrease element count
    count--;
}