// FUNC_NAME: SomeClass::getSlot
// Calculates pointer to an array element with 20-byte stride, starting at offset 0x28 from 'this'.
// param_1: this pointer (base of class)
// param_2: index into the array (0-based)
// Returns: address of element at given index
int __thiscall SomeClass::getSlot(int this, int index)
{
    // Offset = this + 40 + index * 20
    return this + (index * 5 + 10) * 4;
}