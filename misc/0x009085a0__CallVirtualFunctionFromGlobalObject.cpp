// FUNC_NAME: CallVirtualFunctionFromGlobalObject
// Address: 0x009085a0
// Calls the 5th virtual function (offset 0x14) on a global object pointed to by DAT_012234e0.
// The global object is likely a singleton instance of some engine class.
void CallVirtualFunctionFromGlobalObject(uint32_t param1, uint32_t param2, uint32_t param3)
{
    // DAT_012234e0 is a global pointer to an object with a vtable pointer at offset 0.
    // The vtable pointer points to a table of function pointers.
    // Offset 0x14 in the vtable corresponds to the 5th virtual function (0-indexed: index 5).
    void (*func)(uint32_t, uint32_t, uint32_t) = *(void (**)(uint32_t, uint32_t, uint32_t))(*(uint32_t*)DAT_012234e0 + 0x14);
    func(param1, param2, param3);
}