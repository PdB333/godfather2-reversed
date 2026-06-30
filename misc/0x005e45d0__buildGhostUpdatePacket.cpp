// FUNC_NAME: buildGhostUpdatePacket
void buildGhostUpdatePacket(int outputBuffer)
{
    // Global ghost manager pointer
    uint8_t* ghostMgr = (uint8_t*)DAT_01223504;
    uint8_t numChannels = ghostMgr[0x1d];                 // Number of ghost channels to process
    uint8_t channelIdx = 0;
    uint8_t* activeFlagBase = ghostMgr + 0x18;            // Array of active flags per slot
    uint8_t activeCount = ghostMgr[0x1c];                 // Number of active slots

    while (channelIdx < numChannels)
    {
        if (activeCount != 0)
        {
            uint8_t activeMatched = 0;
            uint8_t slotIdx = 0;
            while (slotIdx < activeCount)
            {
                uint8_t currentMatched = activeMatched;
                if (activeFlagBase[slotIdx] != 0)
                {
                    currentMatched = activeMatched + 1;
                    if (channelIdx == activeMatched)
                    {
                        // Compute encoded slot index (XOR obfuscation)
                        uint32_t encodedSlot = slotIdx ^ 0xad103100;
                        // Pointer to output entry (each 0x30 bytes)
                        uint32_t* entry = (uint32_t*)(outputBuffer + channelIdx * 0x30);

                        // Store encoded slot at offset 0x28
                        entry[10] = encodedSlot;

                        // Recompute original slot from encoded
                        uint32_t decodedSlot = encodedSlot ^ 0xad103100;

                        // Pointer to source object data
                        uint8_t* objectPtr;
                        if (decodedSlot < activeCount)
                        {
                            objectPtr = *(uint8_t**)(ghostMgr + 4 + decodedSlot * 4);
                            if (objectPtr != 0)
                            {
                                // Copy transform/state block 1 (16 bytes from offset 0x40)
                                entry[0] = *(uint32_t*)(objectPtr + 0x40);
                                entry[1] = *(uint32_t*)(objectPtr + 0x44);
                                entry[2] = *(uint32_t*)(objectPtr + 0x48);
                                entry[3] = *(uint32_t*)(objectPtr + 0x4c);
                            }
                        }
                        if (decodedSlot < activeCount && (uint8_t)encodedSlot < activeCount)
                        {
                            objectPtr = *(uint8_t**)(ghostMgr + 4 + (uint8_t)encodedSlot * 4);
                            if (objectPtr != 0)
                            {
                                // Copy transform/state block 2 (16 bytes from offset 0x50)
                                entry[4] = *(uint32_t*)(objectPtr + 0x50);
                                entry[5] = *(uint32_t*)(objectPtr + 0x54);
                                entry[6] = *(uint32_t*)(objectPtr + 0x58);
                                entry[7] = *(uint32_t*)(objectPtr + 0x5c);
                            }
                        }
                        // Store object pointer and additional field
                        uint8_t* objPtr2 = 0;
                        if (decodedSlot < activeCount)
                        {
                            objPtr2 = *(uint8_t**)(ghostMgr + 4 + decodedSlot * 4);
                            entry[9] = *(uint32_t*)(objPtr2 + 0x60); // e.g., network ID or timestamp
                        }
                        entry[8] = (uint32_t)objPtr2; // raw pointer

                        break; // Move to next channel
                    }
                    activeMatched = currentMatched;
                }
                slotIdx++;
            }
        }
        channelIdx++;
    }
}