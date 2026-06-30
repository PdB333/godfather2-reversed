// FUNC_NAME: SomeClass::releaseMembers
// Function address: 0x005ea6e0
// Role: Cleanup/destructor helper that releases two owned objects at offsets +0xc4 and +0xd0

void __thiscall SomeClass::releaseMembers(void)
{
    // Release first owned object at +0xd0
    if (*(int *)(this + 0xd0) != 0) {
        releasePointer(*(int *)(this + 0xd0));
    }
    // Release second owned object at +0xc4
    if (*(int *)(this + 0xc4) != 0) {
        releasePointer(*(int *)(this + 0xc4));
    }
}