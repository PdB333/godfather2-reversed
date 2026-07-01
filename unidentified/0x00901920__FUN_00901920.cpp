// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(void *this)
{
    // Call base class constructor at 0x004c1550
    FUN_004c1550(this);
    // Call member initialization at 0x00903a50
    FUN_00903a50(this);
    return;
}