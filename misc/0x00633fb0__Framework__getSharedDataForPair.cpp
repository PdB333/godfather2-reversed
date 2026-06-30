// FUNC_NAME: Framework::getSharedDataForPair
// Address: 0x00633fb0
// This function ensures that two objects (this and other) have initialized a shared resource
// (likely a stream or queue) by checking a flag at offset +0x6 (bit 0x10).
// It returns a pointer to the shared resource if both are ready, otherwise null.

#include <cstdint>

// Forward declarations of helper functions
// Retrieves a new shared data handle, returns a 64-bit value containing resource pointer and a related object pointer.
uint64_t getSharedDataHandle();   // FUN_00637f90
// Checks if the shared data is valid for the given object.
bool isSharedDataValid();         // FUN_00636800

int* __fastcall getSharedDataForPair(void* self, void* other)
{
    uint8_t flagByte;
    int* sharedPtr;
    int* secondSharedPtr;
    bool isFirstReady, isSecondReady;
    uint64_t handleData;

    // Handle the 'other' object (param_2 in EDX)
    flagByte = *(uint8_t*)((uintptr_t)other + 6);
    if ((flagByte & 0x10) == 0) {
        // Call a function that returns a handle (resource pointer + related object)
        handleData = getSharedDataHandle();
        other = (void*)(uintptr_t)(handleData >> 32); // High part overwrites 'other' pointer
        sharedPtr = (int*)(uintptr_t)handleData;      // Low part is the resource pointer
        if (*sharedPtr == 0) {
            // Resource not yet initialized: set the flag on 'other'
            *(uint8_t*)((uintptr_t)other + 6) = flagByte | 0x10;
            sharedPtr = nullptr;
        }
    } else {
        sharedPtr = nullptr;
    }

    if (sharedPtr == nullptr) {
        return nullptr;
    }

    // If the two objects are the same, return the resource immediately (no need to check second)
    if (other == self) {
        return sharedPtr;
    }

    // Now handle the 'self' object (param_1 in ECX)
    flagByte = *(uint8_t*)((uintptr_t)self + 6);
    if ((flagByte & 0x10) == 0) {
        secondSharedPtr = (int*)getSharedDataHandle();
        if (*secondSharedPtr != 0) {
            // Resource exists for self, skip setting flag
            goto CHECK_SECOND;
        }
        // Set flag on self
        *(uint8_t*)((uintptr_t)self + 6) = flagByte | 0x10;
    }
    secondSharedPtr = nullptr;

CHECK_SECOND:
    if (secondSharedPtr == nullptr) {
        return nullptr;
    }

    // Final validation: the resource must be considered valid by the engine
    if (!isSharedDataValid()) {
        return nullptr;
    }

    // Return the resource pointer obtained from the 'other' object
    return sharedPtr;
}