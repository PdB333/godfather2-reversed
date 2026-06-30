// FUNC_NAME: SomeClass::setPointer
void __thiscall SomeClass::setPointer(SomeClass* this, void* param_2)
{
    // Calls FUN_006bf340 with param_2 and a pointer to a member at offset 0x28 from this
    // The member at +0x28 is likely a void* or some object pointer
    FUN_006bf340(param_2, reinterpret_cast<uint8_t*>(this) + 0x28);
    return;
}