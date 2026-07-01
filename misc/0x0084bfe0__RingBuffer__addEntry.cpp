// FUNC_NAME: RingBuffer::addEntry
// This function adds an entry to a circular ring buffer with element size 0x28.
// struct RingBuffer layout:
//  +0x00: capacity (max elements)
//  +0x04: writeIndex (next insertion index)
//  +0x08: readIndex (oldest element index)
//  +0x0C: buffer (base pointer to element array)
void __thiscall RingBuffer::addEntry(void* this_ptr, int source) {
    int* ringBuf = (int*)this_ptr;
    int capacity = ringBuf[0];         // +0x00
    int& writeIndex = ringBuf[1];      // +0x04 (reference for modification)
    int& readIndex = ringBuf[2];       // +0x08
    int bufferBase = ringBuf[3];       // +0x0C (cast to char* for arithmetic)

    int newWrite = writeIndex + 1;
    writeIndex = newWrite;
    if (capacity <= newWrite) {
        writeIndex = 0;                // wrap around
    }

    // If write catches up to read, advance read (discard oldest entry)
    if (writeIndex <= readIndex) {
        readIndex = readIndex + 1;
    }
    if (capacity <= readIndex) {
        readIndex = 0;                 // wrap read index if needed
    }

    // Preprocess the source entry (unknown function)
    FUN_00714330(source);

    // Copy the 4-byte value at offset 0x24 from source into the buffer entry
    // Each entry is 0x28 bytes; the copy goes to offset 0x24 inside the entry
    *(int*)(bufferBase + writeIndex * 0x28 + 0x24) = *(int*)(source + 0x24);
}