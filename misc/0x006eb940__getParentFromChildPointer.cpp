// FUNC_NAME: getParentFromChildPointer
int __thiscall getParentFromChildPointer(void)
{
    // +0x1c: Pointer to a child object embedded within its parent at offset 0x48
    int* childPtr = *(int**)((char*)this + 0x1c);
    if (childPtr != nullptr) {
        // Subtract 0x48 to get the parent object base address
        return (int)childPtr - 0x48;
    }
    return 0;
}