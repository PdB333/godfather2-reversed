//FUNC_NAME: CircularBuffer::push
// Function address: 0x005d2b50
// Adds a 12-byte triple (two 32-bit values + one 32-bit value) to a circular buffer.
// The buffer is stored as an array of 12-byte elements.
// Members:
//   +0x48: buffer (pointer to element array)
//   +0x4c: capacity (max number of elements)
//   +0x50: startIndex (index of oldest element)
//   +0x54: count (number of elements currently in buffer)

void __thiscall CircularBuffer::push(uint32_t param1, uint32_t param2, uint32_t param3)
{
    int count = *(int *)(this + 0x54);
    int capacity = *(int *)(this + 0x4c);
    int startIndex = *(int *)(this + 0x50);
    int bufferPtr = *(int *)(this + 0x48);

    if (count < capacity)
    {
        int writeIndex = startIndex + count;
        if (writeIndex >= capacity)
        {
            writeIndex -= capacity;
        }

        // Each element is 12 bytes: first 8 bytes are a 64-bit value (param2:param1), last 4 bytes are param3
        uint64_t *element = (uint64_t *)(bufferPtr + writeIndex * 12);
        *element = ((uint64_t)param2 << 32) | param1;
        *(uint32_t *)(element + 1) = param3; // element+1 advances by 8 bytes, so this writes at offset 8

        *(int *)(this + 0x54) = count + 1;
    }
}