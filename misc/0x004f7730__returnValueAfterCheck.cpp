// FUNC_NAME: returnValueAfterCheck
// Function at 0x004f7730: returns the input value if a virtual check passes, otherwise 0.
// Uses vtable pointer at +0x00, virtual function at offset +0x10.
uint returnValueAfterCheck(void* thisPtr, uint value)
{
    int unused = 0; // ignored out-parameter from virtual call
    // Virtual function at vtable+0x10: bool check(uint value, int* out)
    typedef bool (*CheckFunc)(uint, int*);
    CheckFunc check = (CheckFunc)(*(void***)thisPtr)[4]; // index 4 (offset 0x10 / 4)
    bool isValid = check(value, &unused);
    return -(uint)(isValid) & value; // if isValid, return value, else 0
}