// FUNC_NAME: NetSession::constructor
#include <cstdint>

// +0x00: vtable pointer
// +0x4C: session state flags (0x13)
// +0x50: connection count or timer (0x14)
// +0x54: some counter/index (0x15)
// +0x58: packet window index? (0x16)
// +0x5C: reliable send sequence (0x17)
// +0x60: last received ACK (0x18)
// +0x64: game instance pointer or global timestamp (0x19) - from DAT_00d5780c

// This function initializes a NetSession object, calling a base constructor
// and then zeroing out session tracking fields, setting the game instance pointer.
undefined4* NetSession::constructor(undefined4* thisPtr)
{
    // Call the base class constructor (likely Framework::Object or similar)
    FUN_008334a0();

    // Set main vtable pointer (PTR_FUN_00d7343c)
    thisPtr[0] = &PTR_FUN_00d7343c;

    // Reset session state fields to 0
    thisPtr[0x13] = 0; // +0x4C: session flags
    thisPtr[0x14] = 0; // +0x50: some counter
    thisPtr[0x15] = 0; // +0x54: another counter
    thisPtr[0x16] = 0; // +0x58: packet sequence or index
    thisPtr[0x17] = 0; // +0x5C: reliable send sequence
    thisPtr[0x18] = 0; // +0x60: last ACK

    // Store the global game instance/data handle
    thisPtr[0x19] = _DAT_00d5780c; // +0x64: game instance or global state pointer

    return thisPtr;
}