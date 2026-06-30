// FUNC_NAME: BaseObject::getAfterProcess
// Function address: 0x004d4b00
// Calls an initialization/processing function (0x004d4a90) and returns the 32-bit value stored at offset +0x4 (likely a pointer or handle).
// Used as a common accessor pattern across multiple callers.

#include <cstdint>

uint32_t BaseObject::getAfterProcess(uint32_t param) {
    // Call initialization/processing function with this and param
    FUN_004d4a90(this, param);  // +0x4 offset is read after this call
    return *(uint32_t*)((uint8_t*)this + 4);
}