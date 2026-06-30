// FUNC_NAME: TNLConnection::readAndDispatchMessage

void TNLConnection::readAndDispatchMessage(void* thisPointer, void (*callback)(uint32_t, uint64_t, uint64_t, uint32_t, uint32_t))
{
    // +0x18 holds a pointer to the current read position (pointer to uint8_t*)
    uint8_t** readPosPtr = reinterpret_cast<uint8_t**>(static_cast<uint8_t*>(thisPointer) + 0x18);
    uint8_t* currentPos = *readPosPtr;

    // Read the first 4-byte value (e.g., message type)
    uint32_t messageType = *reinterpret_cast<uint32_t*>(currentPos);

    // Align the current position to the next 4-byte boundary after skipping 7 bytes?
    // This is likely aligning after reading the 4-byte type plus optional padding.
    uint8_t* alignedPos = reinterpret_cast<uint8_t*>(
        (reinterpret_cast<uint32_t>(currentPos) + 7) & 0xFFFFFFFC
    );

    // Treat the aligned position as an array of 8-byte values
    uint64_t* data64 = reinterpret_cast<uint64_t*>(alignedPos);

    // Read two 64-bit arguments
    uint64_t arg1 = data64[0];
    uint64_t arg2 = data64[1];

    // Read third 64-bit value and split into two 32-bit parts
    uint64_t arg3 = data64[2];
    uint32_t arg3_low = static_cast<uint32_t>(arg3);
    uint32_t arg3_high = static_cast<uint32_t>(arg3 >> 32);

    // Update the read position to after the three 64-bit values
    *readPosPtr = reinterpret_cast<uint8_t*>(data64 + 3);

    // Dispatch to the provided callback
    callback(messageType, arg1, arg2, arg3_low, arg3_high);
}