// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(byte flag)
{
    // Call base class constructor
    ParentClass::ParentClass();

    // If the low bit of flag is set, initialize a 0x74-byte sub-object or buffer
    if (flag & 1)
    {
        // FUN_0043b960 likely performs placement new or memset for a member of size 0x74
        initializeExtraData(this, 0x74);
    }
}