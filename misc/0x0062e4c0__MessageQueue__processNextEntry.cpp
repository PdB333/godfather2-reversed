// FUNC_NAME: MessageQueue::processNextEntry

#include <cstdint>

// Assumed structures for the message queue buffer
// Each entry: 8 bytes: type (uint32) at offset 0, dataPtr (uint32) at offset 4
// Buffer structure at 'this':
// +0x08: current write pointer (end of used entries)
// +0x0c: current read pointer (next entry to process)
// +0x10: pointer to some state (used for overflow check etc.)

// Forward declarations (stubs)
static int32_t __thiscall validateEntryType(void* thisPtr); // FUN_00633990
static void __cdecl assertFail(const char* msg); // FUN_00627360
static void __cdecl logString(const char* msg); // FUN_00627ac0
static int32_t __thiscall processMessage(void* thisPtr, uint32_t data); // FUN_00629280

extern const char* s_string_00e2a8ac; // debug string

int32_t __thiscall MessageQueue::processNextEntry(void* thisPtr) {
    int32_t* readPtr = *reinterpret_cast<int32_t**>(static_cast<char*>(thisPtr) + 0x0c);
    int32_t* endPtr  = *reinterpret_cast<int32_t**>(static_cast<char*>(thisPtr) + 0x08);
    int32_t dataOffset = 0;
    uint32_t dataValue = 0;

    // First: read the entry's data pointer (offset 4 of entry) and validate
    if (readPtr < endPtr && readPtr != nullptr) {
        if (*readPtr == 4) {
            dataOffset = readPtr[1] + 0x10;
        } else {
            int32_t valResult = validateEntryType(thisPtr);
            if (valResult != 0) {
                dataOffset = readPtr[1] + 0x10;
            } else {
                dataOffset = 0;
            }
            // Check for buffer overflow condition
            uint32_t writeCount = *reinterpret_cast<uint32_t*>(*reinterpret_cast<int32_t*>(static_cast<char*>(thisPtr) + 0x10) + 0x20);
            uint32_t readCount  = *reinterpret_cast<uint32_t*>(*reinterpret_cast<int32_t*>(static_cast<char*>(thisPtr) + 0x10) + 0x24);
            if (writeCount <= readCount) {
                assertFail("Overflow condition");
            }
        }
        if (dataOffset == 0) {
            // Invalid data offset, jump to error handling
            goto errorLabel;
        }
    } else {
errorLabel:
        logString(s_string_00e2a8ac);
    }

    // Second: retrieve the data value from the entry
    readPtr = *reinterpret_cast<int32_t**>(static_cast<char*>(thisPtr) + 0x0c);
    if (readPtr < endPtr && readPtr != nullptr) {
        if (*readPtr == 4) {
            dataValue = *reinterpret_cast<uint32_t*>(readPtr[1] + 0x0c);
        } else {
            int32_t valResult = validateEntryType(thisPtr);
            if (valResult != 0) {
                dataValue = *reinterpret_cast<uint32_t*>(readPtr[1] + 0x0c);
            } else {
                dataValue = 0;
            }
        }
    } else {
        dataValue = 0;
    }

    // Third: process the next entry (the one after the current read pointer)
    int32_t currentReadAddr = *reinterpret_cast<int32_t*>(static_cast<char*>(thisPtr) + 0x0c); // address of current entry
    int32_t* nextEntry = reinterpret_cast<int32_t*>(currentReadAddr + 8); // next entry's type field
    if (nextEntry < endPtr && nextEntry != nullptr && *nextEntry > 0) {
        if (nextEntry < endPtr && nextEntry != nullptr) {
            if (*nextEntry == 4) {
                dataOffset = *reinterpret_cast<int32_t*>(currentReadAddr + 0x0c) + 0x10; // note: same as readPtr[1] + 0x10
            } else {
                int32_t valResult = validateEntryType(thisPtr);
                if (valResult != 0) {
                    dataOffset = *reinterpret_cast<int32_t*>(currentReadAddr + 0x0c) + 0x10;
                } else {
                    dataOffset = 0;
                }
                // Overflow check again
                uint32_t writeCount = *reinterpret_cast<uint32_t*>(*reinterpret_cast<int32_t*>(static_cast<char*>(thisPtr) + 0x10) + 0x20);
                uint32_t readCount  = *reinterpret_cast<uint32_t*>(*reinterpret_cast<int32_t*>(static_cast<char*>(thisPtr) + 0x10) + 0x24);
                if (writeCount <= readCount) {
                    assertFail("Overflow condition");
                }
            }
            if (dataOffset != 0) {
                goto continueProcessing;
            }
        }
        logString(s_string_00e2a8ac);
    }
    // If we reach here, no valid next entry? The code after this is just the end.
    // But the original code jumps to LAB_0062e5c9 after the if block, so we need to handle that.

continueProcessing:
    int32_t result = processMessage(thisPtr, dataValue);
    if (result == 0) {
        return 1; // no message processed
    }

    // Dequeue the current entry: remove it and shift the rest
    // Write pointer is at param_1+0x08
    int32_t* writePtr = *reinterpret_cast<int32_t**>(static_cast<char*>(thisPtr) + 0x08);
    *writePtr = 0; // clear the entry (first word)
    *reinterpret_cast<int32_t*>(static_cast<char*>(thisPtr) + 0x08) = reinterpret_cast<int32_t>(writePtr) + 8; // advance write pointer by 8

    int32_t* newWritePtr = *reinterpret_cast<int32_t**>(static_cast<char*>(thisPtr) + 0x08);
    // Shift entries backward to fill the gap
    int32_t* shiftSrc = newWritePtr;
    for (int32_t* shiftDst = newWritePtr; newWritePtr - 4 < shiftDst; shiftDst -= 2) {
        *shiftDst = shiftDst[-2];
        shiftDst[1] = shiftDst[-1];
    }
    int32_t* shiftEnd = *reinterpret_cast<int32_t**>(static_cast<char*>(thisPtr) + 0x08);
    newWritePtr[-4] = *shiftEnd;
    newWritePtr[-3] = shiftEnd[1];

    return 2; // message processed
}