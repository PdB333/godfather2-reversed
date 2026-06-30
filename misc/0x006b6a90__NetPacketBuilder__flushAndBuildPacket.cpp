// FUNC_NAME: NetPacketBuilder::flushAndBuildPacket
int __thiscall NetPacketBuilder::flushAndBuildPacket(void *thisPtr, int baseAddr, PacketHeader *header)
{
    uint oldSlotCount;
    uint currentSlotCount;
    int freeSlotCount;
    int slotCapacity;
    int iVar5;
    int iVar6;

    oldSlotCount = *(uint *)(thisPtr + 0x78);   // +0x78: m_slotCount
    currentSlotCount = oldSlotCount;

    // First loop: drain pending slots; when the last one is freed, release associated resources
    while (currentSlotCount != 0) {
        *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) - 1;
        if (*(int *)(thisPtr + 0x78) == 0) {
            slotCapacity = *(int *)(thisPtr + 0xac);   // +0xac: m_slotCapacity
            while (slotCapacity = slotCapacity - 1, slotCapacity >= 0) {
                freeSlot(slotCapacity);                 // FUN_006b56a0
            }
        }
        currentSlotCount = *(uint *)(thisPtr + 0x78);
    }

    // Clear data buffer state and release the user data buffer
    *(int *)(thisPtr + 0x88) = 0;     // +0x88: m_dataBufferPos
    MemFree(*(void **)(thisPtr + 0x84)); // +0x84: m_dataBuffer
    *(void **)(thisPtr + 0x84) = 0;
    *(int *)(thisPtr + 0x8c) = 0;     // +0x8c: m_dataBufferSize? (set to 0)
    *(int *)(thisPtr + 0xa0) = 0;     // +0xa0: m_headerBufferPos
    MemFree(*(void **)(thisPtr + 0x9c)); // +0x9c: m_headerBuffer
    *(void **)(thisPtr + 0x9c) = 0;
    *(int *)(thisPtr + 0xa4) = 0;     // +0xa4: m_headerBufferSize? (set to 0)

    // Compute offset to start of packet data within the base address
    int headerSize = getPacketHeaderSize(baseAddr, header, header); // FUN_006b6990 (param3 passed twice, likely unused)
    iVar5 = headerSize + baseAddr;

    // Copy header data from the header structure into the data buffer
    // Source: header + 0x38 (size of header data)
    // Destination: pointer to data buffer (m_dataBuffer)
    int bytesCopied1 = copyDataToBuffer(iVar5, *(int *)((int)header + 0x38), (void **)(thisPtr + 0x84)); // FUN_006b47b0

    // Copy additional data from header + 0x3c into the header buffer
    iVar6 = iVar5 + bytesCopied1;
    int bytesCopied2 = copyDataToBuffer(iVar6, *(int *)((int)header + 0x3c), (void **)(thisPtr + 0x9c)); // FUN_006b47b0

    // Restore the slot count back to the original value and allocate new slots as needed
    currentSlotCount = *(uint *)(thisPtr + 0x78);
    while (currentSlotCount < oldSlotCount) {
        *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) + 1;
        if (*(int *)(thisPtr + 0x78) == 1) {
            int freeCapacity = *(int *)(thisPtr + 0x68) - *(int *)(thisPtr + 0xac); // +0x68: m_totalCapacity, +0xac: m_slotCapacity
            while (freeCapacity > 0) {
                allocateSlot();   // FUN_006b4b50
                freeCapacity--;
            }
        }
        currentSlotCount = *(uint *)(thisPtr + 0x78);
    }

    // Finalize the packet and flush it
    finalizePacket(*(void **)(thisPtr + 0x16c), 0); // +0x16c: m_packetHandle
    flushPacket();   // FUN_006b2f70

    // Return total bytes written (sum of copied header/data minus base offset)
    return (iVar5 + bytesCopied2) - baseAddr;
}