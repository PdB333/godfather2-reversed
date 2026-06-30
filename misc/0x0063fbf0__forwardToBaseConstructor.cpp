// FUNC_NAME: forwardToBaseConstructor
// Function at 0x0063fbf0 - Thin wrapper that forwards to initialization function at 0x0063fad0.
// Likely a derived class constructor calling the base class constructor.

void __fastcall forwardToBaseConstructor(void* thisPtr)
{
    FUN_0063fad0(thisPtr);  // Delegate to actual base initialization
}