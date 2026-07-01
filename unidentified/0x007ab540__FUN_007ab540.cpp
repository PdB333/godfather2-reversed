// FUNC_NAME: SomeClass::setSomeGlobalValue
void __fastcall SomeClass::setSomeGlobalValue(int this)
{
    // Write a global value (DAT_01205224) into the object's data at offset +0x60, then +0x0C
    // This likely sets a field like "someGlobalSetting" or "globalTimer" in a sub-structure
    *(int*)(*(int*)(this + 0x60) + 0xC) = DAT_01205224;
    return;
}