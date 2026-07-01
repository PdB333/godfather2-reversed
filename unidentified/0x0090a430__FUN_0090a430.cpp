// FUNC_NAME: SomeClass::releaseSubObject
void __thiscall SomeClass::releaseSubObject(SomeClass* this)
{
    // Check if sub-object pointer at +0x8 is non-null
    if (this->m_subObject != nullptr)
    {
        // Release the sub-object (likely a reference count decrement or deletion)
        FUN_004daf90((int*)(this + 8));
    }
}