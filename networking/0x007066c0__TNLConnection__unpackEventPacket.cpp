// FUNC_NAME: TNLConnection::unpackEventPacket

#include <cstdint>

// Reconstructed from Ghidra decompile at 0x007066c0
// This function processes a received network packet, unpacking event data from a 64-bit mask
// into a 35-byte flag array, then iterates over 11 event slots (structures at this+0x18)
// to deserialize and dispatch events.

uint32_t __thiscall TNLConnection::unpackEventPacket(void* this_ptr, int param_2, uint32_t* packetData, int packetSize, bool isFromServer)
{
    uint32_t maskLow;
    uint32_t maskHigh;
    uint32_t currentMask;
    uint32_t unknownVal;
    uint32_t count;
    int* slotBase;
    uint32_t* dataPtr;
    uint8_t* flagPtr;
    uint32_t slotIndex;
    uint32_t tempCount;
    uint32_t timestamp;
    int32_t eventTime;
    bool flagVar;
    uint32_t* localPtr;
    uint8_t eventFlagArray[35]; // actually at this+0x118
    uint32_t localVar20;
    uint32_t localVar1c;
    int32_t localVar18;
    uint32_t localVar10;
    int32_t localVar8;

    // Validate packet header
    if ((packetSize == 0) || (*(uint32_t*)((uint8_t*)this_ptr + 0xf0) == 0)) {
        return 0xFFFFFF00; // error code
    }

    // Get some reference value (maybe timestamp)
    localVar8 = *(uint32_t*)(*(uint32_t*)((uint8_t*)this_ptr + 0xf0) + 0x74c); // ???
    localVar10 = 0xb; // default slot limit? might be 11

    if ((isFromServer) && (localVar8 != 0)) {
        localVar8 -= 0x48;
        if (localVar8 != 0) {
            localVar10 = *(uint32_t*)(localVar8 + 0x2114); // FUN_00704860 call, but simplified
        }
    }

    // Unpack 64-bit mask into 35-byte flag array at this+0x118
    maskLow = packetData[0];
    maskHigh = packetData[1];
    flagPtr = (uint8_t*)this_ptr + 0x118;
    for (int bitIndex = 0; bitIndex < 35; bitIndex++) {
        *flagPtr = 0;
        if (bitIndex < 32) {
            if (maskLow & (1 << bitIndex)) *flagPtr = 1;
        } else {
            if (maskHigh & (1 << (bitIndex - 32))) *flagPtr = 1;
        }
        flagPtr++;
    }

    // Store the highest bit as a flag
    *(uint8_t*)((uint8_t*)this_ptr + 0xf4) = (uint8_t)(maskHigh >> 31);

    // Process each of the 11 event slots (index 0 to 10)
    slotBase = (int32_t*)((uint8_t*)this_ptr + 0x18);
    dataPtr = packetData + 2;
    slotIndex = 0;

    do {
        count = *dataPtr;
        localPtr = dataPtr + 1;

        if (count == 0) {
            if (!isFromServer) {
                if ((*slotBase != 0) && (*slotBase != 0x48) && (*slotBase != 0)) {
                    // Free slot's associated data structure
                    FUN_004daf90(slotBase); // likely operator delete or destructor
                    *slotBase = 0;
                }
                // Update some mask based on slot[3]
                slotBase[2] = ~-(uint32_t)(slotBase[3] != 0) & slotBase[3];
            }
        } else {
            // Non-zero count means events are present
            if (*slotBase == 0) {
                localVar18 = 0;
            } else {
                localVar18 = *slotBase - 0x48;
            }

            flagVar = false;
            if (localVar18 != 0) {
                flagVar = *(uint8_t*)(localVar18 + 0x1a8) == 1; // some state flag
            }

            uint32_t* extraDataPtr = dataPtr + 9;
            localVar1c = 0;
            uint32_t* nextPtr = localPtr;

            if (slotIndex < 5) {
                timestamp = *extraDataPtr;
                localVar1c = dataPtr[10];
                extraDataPtr = dataPtr + 11;

                if (!isFromServer) {
                    // Server-side: skip if localVar18 != 0
                    localPtr = extraDataPtr;
                    extraDataPtr = localPtr;
                    if (localVar18 != 0) {
                        FUN_004088c0(localVar18 + 0x3c); // likely timer reset
                    }
                } else if (localVar18 != 0) {
                    // Client-side with existing slot
                    if (flagVar) {
                        uint32_t limit = *(uint32_t*)(localVar18 + 0x510);
                        int32_t timeOffset = FUN_007013c0(); // get current time
                        localVar1c = localVar1c + timeOffset;
                        if (timestamp < limit) goto LAB_0070693f; // early exit
                    }
                    goto LAB_00706882; // common cleanup
                }

                // Common cleanup after event dump
                localPtr = extraDataPtr;
LAB_00706882:
                // Cleanup existing slot
                if ((*slotBase != 0) && (*slotBase != 0x48) && (*slotBase != 0)) {
                    FUN_004daf90(slotBase);
                    *slotBase = 0;
                }
                slotBase[2] = ~-(uint32_t)(slotBase[3] != 0) & slotBase[3];

                // Process each event within this slot
                if (count != 0) {
                    int32_t eventHandle;
                    do {
                        eventHandle = FUN_007065d0(localPtr, dataPtr + 5, &localVar8, slotIndex);
                        count--;
                    } while (count != 0);

                    if (eventHandle != 0) {
                        if (slotIndex < 5) {
                            FUN_00704ab0(eventHandle, localVar1c); // attach event to some list
                        }
                        // Special case: if the slot matches the expected slot for server-side, call a function
                        if ((localVar10 != 0xb) && (slotIndex == localVar10)) {
                            (*(void (**)(int32_t))(**(int32_t**)((uint8_t*)this_ptr + 0xf0) + 600))(eventHandle);
                        }
                    }
                }
            } else {
                // For slot indices >= 5
                if (!isFromServer) goto LAB_00706882;
LAB_0070693f:
                localPtr = extraDataPtr;
                if (flagVar) {
                    int32_t timeOffset = FUN_007013c0();
                    FUN_00701ff0(localVar1c - timeOffset); // set timer
                } else {
                    // Process events without timer adjustment
                    while (count != 0) {
                        FUN_007065d0(localPtr, dataPtr + 5, &localVar8, slotIndex);
                        count--;
                    }
                }
            }
        }

        slotIndex++;
        slotBase += 5; // each slot is 5 ints (20 bytes)
        dataPtr = localPtr; // advance data pointer

        if (slotIndex > 10) {
            // After processing 11 slots, check for additional data
            uint32_t remainingCount = *localPtr;
            if (remainingCount != 0) {
                // If there is a buffer allocated, free it first
                if (*(int32_t*)((uint8_t*)this_ptr + 0x140) != 0) {
                    FUN_009c8f10(*(int32_t*)((uint8_t*)this_ptr + 0x140));
                    *(uint32_t*)((uint8_t*)this_ptr + 0x140) = 0;
                    *(uint32_t*)((uint8_t*)this_ptr + 0x13c) = 0;
                }
                // Allocate new buffer and copy data
                *(uint32_t*)((uint8_t*)this_ptr + 0x13c) = remainingCount;
                void* newBuffer = (void*)FUN_009c8e80(remainingCount);
                *(uint32_t*)((uint8_t*)this_ptr + 0x140) = (uint32_t)newBuffer;
                if (newBuffer != nullptr) {
                    for (uint32_t i = 0; i < remainingCount; i++) {
                        ((uint8_t*)newBuffer)[i] = ((uint8_t*)localPtr)[i + 4];
                    }
                }
            }
            return 0x100; // success
        }
    } while (true);
}