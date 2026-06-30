// FUNC_NAME: NetBuffer::getCurrentData
int __fastcall NetBuffer::getCurrentData(int* thisPtr)
{
    // thisPtr points to a NetBuffer object
    // thisPtr[0] is m_buffer (pointer to buffer block)
    // thisPtr[1] is m_current (pointer to current packet slot)
    // Buffer block has an end pointer at offset +4

    if (thisPtr[0] == 0) {
        // Assertion: buffer must exist
        FUN_00b97aea(); // likely __assert or handle error
    }

    int* bufferBlock = (int*)thisPtr[0];
    int* currentSlot = (int*)thisPtr[1];

    if (currentSlot == (int*)(bufferBlock[1])) {
        // Assertion: current pointer must not be at end
        FUN_00b97aea();
    }

    // Return pointer to data starting at offset 12 within the current slot
    return (int)(currentSlot + 3); // 3 ints = 12 bytes offset
}