// FUNC_NAME: SomeClass::getSomeOffset
int __fastcall SomeClass::getSomeOffset(int this)
{
    // Returns the value at offset 0x58 plus a constant 0x2b20
    // This likely retrieves a pointer to a sub-object or data block
    return *(int *)(this + 0x58) + 0x2b20;
}