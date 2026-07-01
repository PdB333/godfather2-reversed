// FUNC_NAME: getSubObjectBasePointer
int __thiscall getSubObjectBasePointer(void* this_ptr) {
    // Check if the pointer at offset +0x31C is non-null
    if (*(int*)((char*)this_ptr + 0x31C) != 0) {
        // Subtract 0x48 to get the base of the containing structure
        return *(int*)((char*)this_ptr + 0x31C) - 0x48;
    }
    return 0;
}