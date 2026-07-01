// FUNC_NAME: SomeClass::resetArrayToZero
void __fastcall SomeClass::resetArrayToZero(int thisPtr)
{
    // Clear four array elements at offsets +0x40, +0x70, +0xA0, +0xD0 (each element is 0x30 bytes)
    *(int*)(thisPtr + 0x40) = 0;  // Element 0
    *(int*)(thisPtr + 0x70) = 0;  // Element 1
    *(int*)(thisPtr + 0xA0) = 0;  // Element 2
    *(int*)(thisPtr + 0xD0) = 0;  // Element 3
}