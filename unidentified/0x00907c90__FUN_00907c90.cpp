//FUNC_NAME: UnknownClass::forwardToBaseWithDefaultZero
// Address: 0x00907c90
// Role: Wrapper that adds a default zero parameter to the base function at 0x005661c0
// The zero likely represents a flag (e.g., bForce, bUseDefault) or a null pointer.

void __thiscall UnknownClass::forwardToBaseWithDefaultZero(int param1, int param2, int param3, int param4, int param5, int param6) {
    // Forward to implementation with default zero parameter
    baseFunction(param1, param2, param3, param4, param5, param6, 0);
}