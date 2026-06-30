// FUNC_NAME: PacketSlotManager::processSlotQueue
int PacketSlotManager::processSlotQueue(int param_2, char threshold) {
    ushort slotBitmask;
    int slotPtr;
    int result;
    byte currentIndex;
    byte stepSize;
    byte loopCount;
    uint tempIndex;
    uint tempVar;

    result = 0;
    if (this != nullptr) {
        int* otherObj = *(int**)(this + 8); // +0x08: pointer to some object with flags
        currentIndex = *(byte*)(this + 0x6e); // +0x6e: current index in circular buffer
        stepSize = ((*(byte*)(otherObj + 8) & 1) != 0) + 1; // stride: 1 or 2 based on flag
        // tempIndex is a 3-byte local used for index arithmetic
        tempIndex = currentIndex;
        if (*(byte*)(this + 0x6f) != 0) { // +0x6f: max number of slots
            do {
                slotPtr = *(int*)(this + 0xc + currentIndex * 4); // +0x0c: primary slot array
                if (slotPtr == 0) {
                    // Primary slot empty; if stride==2, check secondary array
                    if ((1 < stepSize) && (*(int*)(this + 0x10 + currentIndex * 4) != 0)) {
                        cleanupSlot(); // FUN_005f16b0
                        *(int*)(this + 0x10 + currentIndex * 4) = 0; // clear secondary slot
                        // Update bitmask (hash-like operation)
                        slotBitmask = *(ushort*)(this + 0x6c);
                        *(ushort*)(this + 0x6c) = (byte)(((char)(slotBitmask >> 3) - 1) * 8 ^ (byte)slotBitmask) & 0x78 ^ slotBitmask;
                    }
                    break;
                }
                // Check slot's internal field at +0x18 (sequence number or priority)
                int slotField = *(int*)(slotPtr + 0x18);
                if ((slotField < (int)(uint)(threshold != 0)) || (slotField == 0)) {
                    cleanupSlot(); // FUN_005f16b0
                    tempVar = currentIndex;
                    *(int*)(this + 0xc + tempVar * 4) = 0; // clear primary slot
                    slotBitmask = *(ushort*)(this + 0x6c);
                    *(ushort*)(this + 0x6c) = (byte)(((char)(slotBitmask >> 3) - 1) * 8 ^ (byte)slotBitmask) & 0x78 ^ slotBitmask;
                    if ((1 < stepSize) && (*(int*)(this + 0x10 + tempVar * 4) != 0)) {
                        cleanupSlot(); // FUN_005f16b0
                        *(int*)(this + 0x10 + tempVar * 4) = 0;
                        // Update bitmask again
                        slotBitmask = *(ushort*)(this + 0x6c);
                        *(ushort*)(this + 0x6c) = (byte)(((char)(slotBitmask >> 3) - 1) * 8 ^ (byte)slotBitmask) & 0x78 ^ slotBitmask;
                    }
                    break;
                }
                currentIndex += stepSize;
                tempIndex = currentIndex;
                if (*(byte*)(this + 0x6f) <= currentIndex) {
                    tempIndex = 0; // wrap around
                    currentIndex = 0;
                }
                // loopCount is a byte counter to prevent infinite loop
                loopCount += stepSize;
            } while (loopCount < *(byte*)(this + 0x6f));
        }
        if (loopCount < *(byte*)(this + 0x6f)) {
            // Not all slots examined; try to allocate new slots
            currentIndex = 0;
            if (stepSize != 0) {
                do {
                    int newSlot = allocateSlot(); // FUN_005f10d0
                    if (newSlot == 0) {
                        if (currentIndex != 0) {
                            // Clean up the last allocated slot
                            int lastSlot = *(int*)(this + 0xc + tempIndex * 4);
                            freeMemory(*(short*)(lastSlot + 8), *(int*)(lastSlot + 0x18)); // FUN_005dbc10
                            (**(code**)(*DAT_01223510 + 0x20))(*(short*)(lastSlot + 8)); // vtable call
                            freeMemory(*(short*)(lastSlot + 8), *(int*)(lastSlot + 0x18));
                            if ((*(byte*)(lastSlot + 0x10) & 0x40) == 0) {
                                anotherCleanup(); // FUN_005f1660
                            }
                            *(int*)(lastSlot + 0x24) = 0;
                            *(int*)(lastSlot + 0x28) = 0;
                            *(int*)(lastSlot + 0x2c) = 0;
                            *(int*)(this + 0xc + tempIndex * 4) = 0;
                        }
                        goto cleanup_done;
                    }
                    // Store new slot in primary array at offset (currentIndex + tempIndex)
                    *(int*)(this + 0xc + ((uint)currentIndex + tempIndex) * 4) = newSlot;
                    byte bitmaskByte = (byte)*(ushort*)(this + 0x6c);
                    currentIndex++;
                    *(ushort*)(this + 0x6c) = (byte)((bitmaskByte & 0xf8) + 8 ^ bitmaskByte) & 0x78 ^ *(ushort*)(this + 0x6c);
                } while (currentIndex < stepSize);
            }
            // Update current index
            result = this + 0xc + tempIndex * 4;
            *(byte*)(this + 0x6e) = tempIndex + stepSize;
            if (*(byte*)(this + 0x6f) <= (byte)(tempIndex + stepSize)) {
                *(byte*)(this + 0x6e) = 0; // wrap around
            }
            // Apply additional flags from otherObj
            if ((*(byte*)(otherObj + 8) & 1) != 0) {
                *(ushort*)(this + 0x6c) ^= 4;
            }
            if ((*(byte*)(otherObj + 8) & 0x40) != 0) {
                *(ushort*)(this + 0x6c) |= 0x100;
                return result;
            }
        } else {
cleanup_done:
            result = 0;
        }
    }
    return result;
}