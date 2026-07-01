// FUNC_NAME: Component::getParentObject
int __fastcall Component::getParentObject(int thisPtr)
{
    // Check if the pointer at offset +0x10c is non-null
    // This pointer points to a sub-object embedded within a parent at offset 0x48
    // Subtracting 0x48 yields the parent object's base address
    if (*(int*)(thisPtr + 0x10c) != 0) {
        return *(int*)(thisPtr + 0x10c) - 0x48;
    }
    return 0;
}