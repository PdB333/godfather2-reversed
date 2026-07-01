//FUNC_NAME: SomeClass::setFlagAndLog
void __thiscall SomeClass::setFlagAndLog(int this)
{
    // Set bit 2 (value 4) at offset +0x74 (likely a flags field)
    *(uint *)(this + 0x74) |= 4;

    // Call debug/log function with parameters: level=0xf, category=1, subcategory=0
    // The last two parameters (local_c, local_4) are likely unused or for return values
    FUN_0079fb90(0xf, 1, 0, 0, 0);
}