// FUNC_NAME: BitSet32::testMask
// Function at 0x00713340: Tests if a specific bit (given by mask) is set.
// Returns the mask if set, 0 otherwise. Delegates to a virtual method at vtable offset 0x10.
uint BitSet32::testMask(uint mask)
{
    int dummy = 0; // unused output from virtual call
    // Virtual function at vtable+0x10: char __thiscall checkBit(uint mask, int* outDummy)
    char result = ((char (__thiscall*)(BitSet32*, uint, int*))(*reinterpret_cast<int*>(this) + 0x10))(this, mask, &dummy);
    // If result is non-zero, return mask; else 0
    return (result != 0) ? mask : 0;
}