// FUNC_NAME: getFieldC
// Function at 0x0043ff50: returns the 4-byte value at offset 0xC from the object (likely a member getter)
int __thiscall getFieldC(void* this_ptr) {
    return *(int*)((char*)this_ptr + 0xC);
}