// FUNC_NAME: StreamObject::release
// Function address: 0x007ffd80
// Clears state flags at +0x504, invoking a callback if the "complete" flag (bit 1) was not already set and the release is with success.
void __thiscall StreamObject::release(int success)
{
    uint32 oldFlags = *(uint32 *)(this + 0x504);          // +0x504: state flags (bit0 = busy, bit1 = complete)
    *(uint32 *)(this + 0x504) = oldFlags & 0xfffffffd;   // Clear bit 1 (complete flag)

    // If the complete flag was not set and we are releasing with success, fire callback.
    if (((oldFlags >> 1) & 1) == 0 && success != 0) {
        streamReleaseCallback(0);                         // FUN_007251a0
    }

    *(uint32 *)(this + 0x504) = *(uint32 *)(this + 0x504) & 0xfffffffe; // Clear bit 0 (busy flag)
}