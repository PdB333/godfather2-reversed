// FUNC_NAME: testFlagAndReturnMask
// Function at 0x006b1c70: Calls a virtual method (vtable+0x10) to test a flag mask and returns the mask if set, otherwise 0.
// The virtual method likely has signature: bool __thiscall checkFlag(uint flagMask, int* outValue);
uint __thiscall testFlagAndReturnMask(int* thisPtr, uint flagMask)
{
    int outValue;          // +0x00
    char isSet;

    outValue = 0;
    isSet = (*(char(__thiscall**)(int*, uint, int*))(*(int*)thisPtr + 0x10))(thisPtr, flagMask, &outValue);
    // If flag is set, return the mask; otherwise return 0.
    return -(uint)(isSet != '\0') & flagMask;
}