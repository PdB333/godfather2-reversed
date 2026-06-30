// FUNC_NAME: DelegateClass::forwardCall
// Function at 0x00613280 is a thin wrapper that forwards the call to the actual implementation at 0x00614910.
// It likely acts as a virtual function thunk or a debug helper.
void __fastcall DelegateClass::forwardCall(DelegateClass* thisPtr)
{
    // Forward to the real implementation (address 0x00614910)
    realMethod(thisPtr);
}