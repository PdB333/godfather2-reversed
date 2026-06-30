// FUNC_NAME: SomeClass::getField0x9c
// Function at 0x00704720: returns a 32-bit value from offset 0x9c of the object (this pointer in ECX).
unsigned int __fastcall SomeClass::getField0x9c(int this)
{
    return *(unsigned int *)(this + 0x9c); // +0x9c: presumably a pointer or ID stored in the object
}