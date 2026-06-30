// FUNC_NAME: DebugGuard::initialize
// Function at 0x006a9190: Initializes a debug guard structure with sentinel values
// then clears them, leaving only a token from FUN_0042b400 in field_0x10.

#include <cstdint>

struct DebugGuard {
    uint32_t field_0;   // +0x00
    uint32_t field_4;   // +0x04
    uint32_t field_8;   // +0x08
    uint32_t field_C;   // +0x0C
    uint32_t field_10;  // +0x10
    uint32_t field_14;  // +0x14
};

// __fastcall actually used (ECX = this), but converted to __thiscall for clarity
DebugGuard* __thiscall DebugGuard::initialize(DebugGuard* this) {
    // Debug sentinel values to detect uninitialized use
    this->field_0 = 0xBADBADBA;
    this->field_4 = 0xBEEFBEEF;
    this->field_8 = 0xEAC15A55;
    this->field_C = 0x91100911;

    // Get a system token (likely a timestamp, process ID, or sequence number)
    uint32_t token = FUN_0042b400();   // Callee at 0x0042b400

    this->field_10 = token;
    this->field_14 = 0;

    // Clear the sentinel markers – the structure is now effectively zeroed
    // except for field_10 which retains the acquired token.
    this->field_C = 0;
    this->field_8 = 0;
    this->field_4 = 0;
    this->field_0 = 0;

    return this;
}