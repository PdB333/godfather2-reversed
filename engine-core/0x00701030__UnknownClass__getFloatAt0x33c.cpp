// FUNC_NAME: UnknownClass::getFloatAt0x33c
// Address: 0x00701030
// Returns a float at offset 0x33C from the object, promoted to extended precision.
// This is likely a property getter for a physics or game state value (e.g., speed, health, distance).
long double __fastcall getFloatAt0x33c(void* thisPtr) {
    // +0x33C is assumed to be a 4-byte float member
    return (long double)(*(float*)((unsigned char*)thisPtr + 0x33C));
}