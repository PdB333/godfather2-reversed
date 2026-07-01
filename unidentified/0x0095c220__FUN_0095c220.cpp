// FUNC_NAME: SomeClass::initFromDefault
void __fastcall SomeClass::initFromDefault(undefined4 *this)
{
    undefined4 *defaultData;
    int count;

    // Get pointer to default data (static/global)
    defaultData = (undefined4 *)getDefaultDataPointer();
    // Copy 28 dwords (112 bytes) from default data into this object
    for (count = 0x1c; count != 0; count--) {
        *this = *defaultData;
        defaultData++;
        this++;
    }
}