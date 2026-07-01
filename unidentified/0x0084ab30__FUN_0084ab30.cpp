// FUNC_NAME: SomeObject::exchangeByteAtOffset4
unsigned char __thiscall SomeObject::exchangeByteAtOffset4(int this, unsigned char newValue)
{
    // Reads and returns the byte at +0x04, then writes newValue there.
    unsigned char oldValue = *(unsigned char *)(this + 4);
    *(unsigned char *)(this + 4) = newValue;
    return oldValue;
}