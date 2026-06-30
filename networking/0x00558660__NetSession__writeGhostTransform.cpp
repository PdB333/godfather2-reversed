// FUNC_NAME: NetSession::writeGhostTransform
void __thiscall NetSession::writeGhostTransform(void *thisPtr, uint32_t connectionId, const Vector3D *transformData) {
    // local buffer for bitstream (176 bytes)
    uint8_t bitStreamBuffer[176];

    // Initialize bitstream writer
    FUN_009f9620(); // BitStream::startWrite (or reset)
    FUN_009f4860(bitStreamBuffer); // BitStream::setWriteBuffer(buffer)

    // Set version/type fields (6 and 2)
    bitStreamBuffer[0x14] = 6;  // local_20
    bitStreamBuffer[0x17] = 2;  // local_1d

    // Get TLS for current thread (unused but caller expects side effect)
    TlsGetValue(*(DWORD*)0x01139810);

    // Allocate a packet of 0x200 bytes with tag 0x2d
    int32_t packetPtr = (int32_t)FUN_00aa2680(0x200, 0x2d); // Likely MemAlloc
    *(uint16_t*)(packetPtr + 4) = 0x200; // Set packet size

    // Write something from the bitstream into the packet (returns size?)
    int32_t writtenSize = FUN_009f4640(bitStreamBuffer); // BitStream::writeToPacket

    // Get a free ghost update structure from the object pool
    uint32_t ghostUpdatePtr = FUN_00559d40(); // e.g., getGhostUpdateBuffer
    if (ghostUpdatePtr != 0) {
        // Zero out the structure fields (offsets +0x40 to +0x68)
        *(uint32_t*)(ghostUpdatePtr + 0x48) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x4C) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x50) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x54) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x58) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x5C) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x40) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x44) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x60) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x64) = 0;
        *(uint32_t*)(ghostUpdatePtr + 0x68) = 0;
    }

    // Build packet header using the first DWORD of this and connection ID
    uint32_t headerData = *(uint32_t*)thisPtr;
    FUN_00556c80(connectionId, headerData, 1); // buildPacketHeader

    // Store the ghost update pointer into the packet with tag bits
    *(uint32_t*)(packetPtr + 0x2C) = (ghostUpdatePtr >> 2) | 0xC0000000;

    // Compute checksum or CRC
    FUN_0043b490();

    // Send the packet with message ID 0x2001 (GhostUpdate)
    FUN_009f01f0(0x2001, headerData, 0);

    // Copy transform data into the ghost update structure
    *(uint64_t*)(ghostUpdatePtr + 0x4C) = ((uint64_t*)transformData)[0]; // x (double or 2 floats?)
    *(uint64_t*)(ghostUpdatePtr + 0x54) = ((uint64_t*)transformData)[1]; // y
    *(uint32_t*)(ghostUpdatePtr + 0x5C) = *(uint32_t*)((uint8_t*)transformData + 16); // z (float?)

    // Send another packet with ID 0x2002 (maybe reliable ack?)
    FUN_009f01f0(0x2002, thisPtr, 0);

    // Finalize bitstream
    FUN_009f01a0(); // BitStream::endWrite
}