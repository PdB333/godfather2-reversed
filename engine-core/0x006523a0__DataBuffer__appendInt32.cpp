// FUNC_NAME: DataBuffer::appendInt32
// Address: 0x006523a0
// Role: Append a 4-byte value to a growable data buffer. Uses fast path if space available, otherwise grows the buffer.
// The buffer structure (accessed via this+0x14) has the following layout (offsets from buffer base):
// +0x00: base pointer (start of allocated memory)
// +0x04: current write pointer
// +0x08: end of allocated memory (used for fast capacity check)
// +0x0C: capacity (in number of int32 elements)

void DataBuffer::appendInt32(uint32 value)
{
    int* bufferPtr = *(int**)(this + 0x14); // pointer to internal buffer struct

    // Fast path: if there is room in the current allocation
    if ((uint)bufferPtr[1] < (uint)bufferPtr[2]) { // current < end
        *(uint32*)bufferPtr[1] = value;
        bufferPtr[1] += 4; // advance write pointer
        return;
    }

    // Slow path: no immediate space; check if we need to grow
    int elementsUsed = (bufferPtr[1] - bufferPtr[0]) >> 2; // (current - base) / 4
    if (bufferPtr[3] <= elementsUsed) {
        // Capacity exhausted – grow the buffer
        growBuffer(); // calls FUN_00b97aea
    }

    uint32* writePtr = *(uint32**)(*(int*)(this + 0x14) + 4); // reload current write pointer after grow
    if (writePtr != nullptr) {
        *writePtr = value;
    }

    // Advance write pointer and update end pointer (may need to be reinterpreted)
    bufferPtr[1] += 4;
    bufferPtr[2] = bufferPtr[1]; // set end to current (possibly to track new allocation end)
}