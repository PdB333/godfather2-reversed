// FUNC_NAME: NetConnection::buildPacket
// Function address: 0x005e10f0
// Builds a packet header in a newly allocated buffer (size 0x18 = 24 bytes).
// Uses an internal buffer in the object if available, otherwise a stack scratch buffer.
// Copies header fields from the source data (passed via ESI) and fills in control fields.

void __thiscall NetConnection::buildPacket(uint32_t param_2) {
    uint32_t* allocatedPacket; // puVar1
    uint32_t* internalBuffer = *(uint32_t**)(this + 8); // +0x08: internal buffer pointer
    uint32_t stackBuffer[3];   // local_c, local_8, local_4

    if (internalBuffer == nullptr) {
        stackBuffer[0] = 0;
        stackBuffer[1] = 0;
        stackBuffer[2] = 0;
        internalBuffer = stackBuffer; // use stack scratch buffer
    }

    // Call virtual function at offset +0x04 (vtable) to allocate 0x18 bytes.
    // The function likely is “allocatePacketBuffer” (size, bufferHint).
    allocatedPacket = (uint32_t*)((*(code**) (*(this+4)))[0])(0x18, internalBuffer);

    if (allocatedPacket != nullptr) {
        // Set packet fields:
        allocatedPacket[0] = stackBuffer[2];       // +0x00: first word (always 0 in practice)
        allocatedPacket[1] = _ReturnAddress();      // +0x04: return address (for debugging/tracing)
        allocatedPacket[2] = param_2;               // +0x08: sequence number or parameter
        allocatedPacket[3] = *(_ESI);               // +0x0C: first word from source (preserved ESI value)
        allocatedPacket[4] = *(_ESI + 1);           // +0x10: second word from source
        *(uint8_t*)(allocatedPacket + 5) = 0;       // +0x14: zero byte
        *(uint8_t*)((int)allocatedPacket + 0x15) = 0; // +0x15: zero byte
    }
    // Note: The function does not return or handle allocation failure beyond the null check.
}