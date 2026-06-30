// FUNC_NAME: UnknownClass::setTripleValues
void __thiscall UnknownClass::setTripleValues(uint64_t value1, uint64_t value2, uint64_t value3)
{
    // Store three 8-byte values at offsets +0xD8, +0xE0, +0xE8
    // These could represent a 3D vector of doubles, two 32-bit ints each, or pointers.
    *(uint64_t*)(this + 0xD8) = value1;
    *(uint64_t*)(this + 0xE0) = value2;
    *(uint64_t*)(this + 0xE8) = value3;
}