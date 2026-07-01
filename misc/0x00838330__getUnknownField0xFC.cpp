// FUNC_NAME: getUnknownField0xFC
// Function at 0x00838330: Simple getter returning the uint32 value at offset 0xFC from the object pointer.
uint32_t __fastcall getUnknownField0xFC(int thisPtr) {
    return *(uint32_t*)(thisPtr + 0xFC);  // +0xFC: likely a pointer, ID, or flag field
}