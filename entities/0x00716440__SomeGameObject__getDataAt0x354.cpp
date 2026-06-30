// FUNC_NAME: SomeGameObject::getDataAt0x354
unsigned int __fastcall getDataAt0x354(unsigned int thisPtr)
{
    // Returns the pointer stored at offset 0x354, likely a component or target reference
    return *(unsigned int*)(thisPtr + 0x354);
}