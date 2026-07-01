// FUNC_NAME: SomeClass::getSomePointer_Offset48
int __fastcall getSomePointer_Offset48(int this)
{
    // Check if the pointer at +0x170 is non-null
    if (*(int *)(this + 0x170) != 0) {
        // Return the pointer minus 0x48 bytes
        return *(int *)(this + 0x170) - 0x48;
    }
    return 0;
}