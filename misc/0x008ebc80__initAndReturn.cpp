// FUNC_NAME: initAndReturn
// Function at 0x008ebc80 - Wrapper that calls an initialization routine and returns the input pointer (likely for method chaining or constructor trampoline).

void* __fastcall initAndReturn(void* object) {
    // Call internal initialization routine (address 0x008ea480), which takes no arguments.
    internalInit();
    return object;
}