// FUNC_NAME: applyGlobalMask
// Function address: 0x00414bc0
// Role: Applies a global bitmask (DAT_00e44680) to three consecutive 32-bit values.
// The original binary fastcall signature is: void __fastcall applyGlobalMask(uint32_t* src)
// where src is passed in ECX, and the destination address is pre-loaded in EAX by the caller.
// For clarity in reconstruction, we expose both parameters.

extern uint32_t DAT_00e44680;  // global mask, +0x0

void __fastcall applyGlobalMask(uint32_t* dest, uint32_t* src) {
    uint32_t mask = DAT_00e44680;
    dest[0] = src[0] & mask;
    dest[1] = src[1] & mask;
    dest[2] = src[2] & mask;
}